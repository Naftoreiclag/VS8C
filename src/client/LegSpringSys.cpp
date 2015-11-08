#include "LegSpringSys.hpp"

#include <algorithm>

#include "MathUtils.hpp"
#include "RigidBodyComp.hpp"
#include "LegSpringComp.hpp"

#include "WalkSignal.hpp"

namespace vse
{

LegSpringSys::LegSpringSys(btDiscreteDynamicsWorld* dynamicsWorld, RayDebugDrawer* rayDebugDrawer)
: mDynamicsWorld(dynamicsWorld)
, mRayDebugDrawer(rayDebugDrawer) {
    mRequiredComponents.push_back(LegSpringComp::componentID);
    mRequiredComponents.push_back(RigidBodyComp::componentID);
}

LegSpringSys::~LegSpringSys() {
}


void LegSpringSys::onEntityExists(nres::Entity* entity) {
    RigidBodyComp* rigidBody = (RigidBodyComp*) entity->getComponent(RigidBodyComp::componentID);
    rigidBody->mRigidBody->setActivationState(DISABLE_DEACTIVATION);
    mTrackedEntities.push_back(entity);
}
void LegSpringSys::onEntityDestroyed(nres::Entity* entity) {
    mTrackedEntities.erase(std::remove(mTrackedEntities.begin(), mTrackedEntities.end(), entity), mTrackedEntities.end());
}
void LegSpringSys::onEntityBroadcast(nres::Entity* entity, const EntSignal* data) {
    switch(data->getType()) {
        case EntSignal::Type::REQ_WALK: {
            WalkSignal* signal = (WalkSignal*) data;
            
            LegSpringComp* comp = (LegSpringComp*) entity->getComponent(LegSpringComp::componentID);
            comp->mTargetVelLin = signal->requestedMovement;
            comp->mNeedStep = true;
            break;
        }
        default: {
            break;
        }
    }
}

const std::vector<nres::ComponentID>& LegSpringSys::getRequiredComponents() {
    return mRequiredComponents;
}

void LegSpringSys::onTick() {
    for(std::vector<nres::Entity*>::iterator it = mTrackedEntities.begin(); it != mTrackedEntities.end(); ++ it) {
        nres::Entity* entity = *it;
        LegSpringComp* legSpring = (LegSpringComp*) entity->getComponent(LegSpringComp::componentID);
        RigidBodyComp* rigidBody = (RigidBodyComp*) entity->getComponent(RigidBodyComp::componentID);
        
        // Do not rotate
        rigidBody->setAngularFactor(0);
        rigidBody->setAngularVelocity(btVector3(0, 0, 0));
        
        // Perform ray test to determine what the legs are "standing on"
        Vec3f absStart = rigidBody->mLocation + legSpring->mStart;
        Vec3f absEnd = rigidBody->mLocation + legSpring->mEnd;
        btCollisionWorld::AllHitsRayResultCallback rayCallback(absStart, absEnd);
        mDynamicsWorld->rayTest(absStart, absEnd, rayCallback);
        
        if(mRayDebugDrawer) {
            mRayDebugDrawer->addRay(absStart, absEnd, -1, 0.5f);
        }
        
        //
        Vec3f hit;
        const btRigidBody* groundBody = nullptr;
        if(rayCallback.hasHit()) {
            // We cannot rely on the order of rayCallback.m_collisionObjects, so we have to compare the distances manually
            btScalar closestHitFraction(1337); // All fractions are <= 1 so this is effectively infinite
            for(int i = rayCallback.m_collisionObjects.size() - 1; i >= 0; -- i) {

                // If this result is closer than the closest valid result
                if(rayCallback.m_hitFractions.at(i) <= closestHitFraction) {
                    // Get the object colliding with
                    const btCollisionObject* other = rayCallback.m_collisionObjects.at(i);

                    closestHitFraction = rayCallback.m_hitFractions.at(i);
                    hit = rayCallback.m_hitPointWorld.at(i);
                    groundBody = static_cast<const btRigidBody*>(other);
                }
            }
        }
        
        if(groundBody) {
            legSpring->mGroundBody = groundBody;
            legSpring->mGroundVelLin = groundBody->getLinearVelocity();
            
            // Walking
            if(legSpring->mNeedStep) {
                Vec3f walkAccel = MathUtils::onPlane(legSpring->mTargetVelLin - (rigidBody->mVelocityLinear - legSpring->mGroundVelLin), legSpring->mUpVector);
                if(!walkAccel.isZero()) {
                    walkAccel.normalize();
                    walkAccel *= legSpring->mAccel;
                    rigidBody->applyForce(walkAccel * rigidBody->mMass);
                }
                
                legSpring->mNeedStep = false;
            }
            
            // Not walking
            else {
                // Character's velocity relative to ground is too slow
                if((rigidBody->mVelocityLinear - legSpring->mGroundVelLin).magSq() < legSpring->mMinVelLin * legSpring->mMinVelLin) {
                    // Apply impulse to set character velocity relative to ground to zero
                    Vec3f impulse = legSpring->mGroundVelLin - rigidBody->mVelocityLinear;
                    rigidBody->applyImpulse(impulse * rigidBody->mMass);
                }
                
                // Gradually slow down
                else {
                    Vec3f gripAccel = MathUtils::onPlane(legSpring->mGroundVelLin - rigidBody->mVelocityLinear, legSpring->mUpVector);
                    if(!gripAccel.isZero()) {
                        gripAccel.normalize();
                        gripAccel *= legSpring->mDecel;
                        
                        rigidBody->applyForce(gripAccel * rigidBody->mMass);
                    }
                }
            }

            // The new length of the virtual spring
            Vec3f newLength = hit - absStart;

            // Calculate and apply Hooke's law with damping
            legSpring->mCompression = legSpring->mLength - newLength; // how much the spring is "compressed"
            Vec3f springVelocity = MathUtils::onAxis(rigidBody->mVelocityLinear, legSpring->mDirection); // get the body's velocity in terms of the springs' compression
            
            // Only apply spring forces under certain conditions
            if(legSpring->mMaxUpwardVelLin < 0 || // User set to always apply spring forces
                rigidBody->mVelocityLinear.dot(legSpring->mDirection) > 0 || // Body is traveling "down"
                springVelocity.magSq() < legSpring->mMaxUpwardVelLin * legSpring->mMaxUpwardVelLin) { // Body is traveling "up", but not too quickly
                    
                Vec3f hooke = // Hooke's law
                -(legSpring->mCompression * legSpring->mStiffness) // The force the spring exerts due to compression is compression multiplied by the spring's stiffness
                -(springVelocity * legSpring->mDamping); // Reduce the force due to damping
                rigidBody->applyForce(hooke);
            }
            
            legSpring->mTouchingGround = true;
        }
        else {
            legSpring->mTouchingGround = false;
        }
    }
}

}

