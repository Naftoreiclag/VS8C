/*
   Copyright 2015 James Fong

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

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
