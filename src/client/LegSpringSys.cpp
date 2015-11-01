#include "LegSpringSys.hpp"

#include <algorithm>

#include "MathUtils.hpp"
#include "RigidBodyComp.hpp"
#include "LegSpringComp.hpp"

namespace vse
{

LegSpringSys::LegSpringSys(btDiscreteDynamicsWorld* const dynamicsWorld)
: mDynamicsWorld(dynamicsWorld) {
    mRequiredComponents.push_back(LegSpringComp::componentID);
    mRequiredComponents.push_back(RigidBodyComp::componentID);
}

LegSpringSys::~LegSpringSys() {
}


void LegSpringSys::onEntityExists(nres::Entity* entity) {
    mTrackedEntities.push_back(entity);
}
void LegSpringSys::onEntityDestroyed(nres::Entity* entity) {
    mTrackedEntities.erase(std::remove(mTrackedEntities.begin(), mTrackedEntities.end(), entity), mTrackedEntities.end());
}
void LegSpringSys::onEntityBroadcast(nres::Entity* entity, const EntSignal* data) {
    
}

const std::vector<nres::ComponentID>& LegSpringSys::getRequiredComponents() {
    return mRequiredComponents;
}

void LegSpringSys::onTick(float tps) {
    for(std::vector<nres::Entity*>::iterator it = mTrackedEntities.begin(); it != mTrackedEntities.end(); ++ it) {
        nres::Entity* entity = *it;
        LegSpringComp* legSpring = (LegSpringComp*) entity->getComponent(LegSpringComp::componentID);
        RigidBodyComp* rigidBody = (RigidBodyComp*) entity->getComponent(RigidBodyComp::componentID);
        
        rigidBody->rigidBody->setAngularFactor(0);
        rigidBody->rigidBody->setAngularVelocity(btVector3(0, 0, 0));
        
        // Perform sweep test to determine what the legs are "standing on"
        Vec3f absStart = rigidBody->mLocation + legSpring->mStartOffset;
        Vec3f absEnd = rigidBody->mLocation + legSpring->mEndOffset;
        btCollisionWorld::AllHitsRayResultCallback rayCallback(absStart, absEnd);
        mDynamicsWorld->rayTest(absStart, absEnd, rayCallback);
        
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
            legSpring->mGroundVelocity = groundBody->getLinearVelocity();
            
            // Walking
            if(legSpring->mNeedStep) {
                Vec3f walkAccel = MathUtils::onPlane((legSpring->mGroundVelocity - rigidBody->mLinVel) + legSpring->mTargetVelocityRelativeToGround, legSpring->mUpVector);
                if(!walkAccel.isZero()) {
                    walkAccel.normalize();
                    walkAccel *= legSpring->mFootAccel;
                    rigidBody->rigidBody->applyForce(walkAccel * rigidBody->mMass, Vec3f(0, 0, 0));
                }
                
                legSpring->mNeedStep = false;
            }
            
            // Not walking
            else {
                // Character's velocity relative to ground is too slow
                if((rigidBody->mLinVel - legSpring->mGroundVelocity).magSq() < legSpring->mMinVelocityRelativeToGround * legSpring->mMinVelocityRelativeToGround) {
                    // Apply impulse to set character velocity relative to ground to zero
                    Vec3f impulse = legSpring->mGroundVelocity - rigidBody->mLinVel;
                    rigidBody->rigidBody->applyImpulse(impulse * rigidBody->mMass, Vec3f(0, 0, 0));
                }
                
                // Gradually slow down
                else {
                    Vec3f gripAccel = MathUtils::onPlane(legSpring->mGroundVelocity - rigidBody->mLinVel, legSpring->mUpVector);
                    if(!gripAccel.isZero()) {
                        gripAccel.normalize();
                        gripAccel *= legSpring->mFootGrip;
                        
                        rigidBody->rigidBody->applyForce(gripAccel * rigidBody->mMass, Vec3f(0, 0, 0));
                    }
                }
            }

            // The new length of the virtual spring
            Vec3f newLength = hit - absStart;

            // Calculate and apply Hooke's law with damping
            legSpring->mSpringCompression = legSpring->mSpring - newLength; // how much the spring is "compressed"
            Vec3f energyLoss = legSpring->mSpringNormalized * rigidBody->mLinVel.dot(legSpring->mSpringNormalized); // get the body's velocity in terms of the springs' compression
            Vec3f hooke = // Hooke's law
            -(legSpring->mSpringCompression * legSpring->mSpringStiffness) // The force the spring exerts due to compression is compression multiplied by the spring's stiffness
            -(energyLoss * legSpring->mSpringDamping); // Reduce the force due to damping
            rigidBody->rigidBody->applyForce(hooke, Vec3f(0, 0, 0));
            
        
            legSpring->mTouchingGround = true;
        }
        else {
            legSpring->mTouchingGround = false;
        }
    }
}

}

