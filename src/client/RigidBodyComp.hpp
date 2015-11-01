#ifndef SKE_PHYSICSCOMP_HPP
#define SKE_PHYSICSCOMP_HPP

#include "btBulletDynamicsCommon.h"

#include "NRES.hpp"

#include "Quate.hpp"
#include "Vec3f.hpp"

namespace vse {

class RigidBodyComp : public nres::Component {
public:
    Quate mRotation;
    Vec3f mLocation;
    Vec3f mVelocityLinear;
    const float mMass;
    
    bool mOnPhysUpdate;
    
    Vec3f mInitialLoc;
    Vec3f mOffset;
    
    void setAngularFactor(float factor);
    void setAngularVelocity(Vec3f angVel);
    void applyForce(Vec3f force, Vec3f relLoc = Vec3f(0, 0, 0));
    void applyImpulse(Vec3f impulse, Vec3f relLoc = Vec3f(0, 0, 0));
    
public:
    static const nres::ComponentID componentID;
    RigidBodyComp(btCollisionShape* collisionShape, const float& mass = 1, const Vec3f& initialPos = Vec3f(0, 0, 0), const Vec3f& bodyOffset = Vec3f(0, 0, 0));
    virtual ~RigidBodyComp();
    
    btCollisionShape* mCollisionShape; // For deletion
    btRigidBody* mRigidBody;
    btMotionState* mMotionState;
public:
    virtual const nres::ComponentID& getID() const;

};

}

#endif // SKE_PHYSICSCOMP_HPP
