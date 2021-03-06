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

#include "Overworld.hpp"

#include <iostream>
#include <fstream>
#include <stdint.h>

#include "OgreMath.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"
#include "SDL.h"

#include "AnimateSignal.hpp"
#include "EntSignal.hpp"
#include "GameLayerMachine.hpp"
#include "LegSpringComp.hpp"
#include "LocalPlayerComp.hpp"
#include "LocationSignal.hpp"
#include "MathUtils.hpp"
#include "PauseScreen.hpp"
#include "RigidBodyComp.hpp"
#include "RigidBodySys.hpp"
#include "SceneNodeComp.hpp"
#include "SerializationUtil.hpp"
#include "Vec3f.hpp"
#include "WalkSignal.hpp"

namespace vse {
    
void Overworld::onEntityExists(nres::Entity* entity) {}
void Overworld::onEntityDestroyed(nres::Entity* entity) {}

void Overworld::onEntityBroadcast(nres::Entity* entity, const EntSignal* data) {
    switch(data->getType()) {
        case EntSignal::Type::LOCATION: {
            LocationSignal* signal = (LocationSignal*) data;
            
            mCamLocNode->setPosition(signal->mLocationUpdate + Vec3f(0, 0.75, 0));
            
            break;
        }
        default: {
            break;
        }
    }
}

Overworld::Overworld() {}
Overworld::~Overworld() {}

void Overworld::onBegin(PotatoCake* potatoCake) {
    mGameLayerMachine = potatoCake->mGameLayerMachine;
    mOgreRoot = potatoCake->mOgreRoot;
    mOgreWindow = potatoCake->mOgreWindow;
    
    SDL_SetRelativeMouseMode(SDL_TRUE);
    
    mSmgr = mOgreRoot->createSceneManager(Ogre::ST_GENERIC);
    mRootNode = mSmgr->getRootSceneNode();
    
    mCam = mSmgr->createCamera("Camera");
    mCam->setNearClipDistance(0.1f);
    
    mCamLocNode = mRootNode->createChildSceneNode("CameraNode");
    mCamYawNode = mCamLocNode->createChildSceneNode();
    mCamPitchNode = mCamYawNode->createChildSceneNode();
    mCamRollNode = mCamPitchNode->createChildSceneNode();
    mCamRollNode->attachObject(mCam);
    
    mCamPitch = Ogre::Degree(0);
    mCamYaw = Ogre::Degree(0);
    mCamRoll = Ogre::Degree(0);
    
    mDollyScale = 5.f;
    mDollyMax = 10.f;
    mDollyMin = 0.f;
    
    mDollyAngle = Ogre::Degree(10);
    mDollyXCoeff = Ogre::Math::Sin(mDollyAngle);
    mDollyZCoeff = Ogre::Math::Cos(mDollyAngle);
    
    updateCamDolly();
    
    mCam->setAspectRatio(Ogre::Real(1280) / Ogre::Real(720));
    
    mSmgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    /*
    mSmgr->setShadowTextureSize(1024);
    mSmgr->setShadowTextureFSAA(2);
    mSmgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE); // SHADOWTYPE_TEXTURE_ADDITIVE
    */
    mSmgr->setSkyBox(true, "PlaceholderSky");
    
    Ogre::Viewport* viewport = mOgreWindow->addViewport(mCam);
    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    
    Ogre::SceneNode* groundNode = mSmgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Entity* groundEnt = mSmgr->createEntity("Ground", "ground.mesh");
    groundEnt->setCastShadows(false);
    groundNode->attachObject(groundEnt);
    
    Ogre::Light* light = mSmgr->createLight("Light");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(-1, -1, -1);
    
    mBroadphase = new btDbvtBroadphase();
    mCollisionConfiguration = new btDefaultCollisionConfiguration();
    mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
    mSolver = new btSequentialImpulseConstraintSolver();
    mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver, mCollisionConfiguration);
    mBtDebugDrawer = new BulletDebugDrawer(mSmgr);
    mRayDebugDrawer = new RayDebugDrawer(mSmgr);
    mDynamicsWorld->setDebugDrawer(mBtDebugDrawer);
    mDynamicsWorld->setGravity(btVector3(0, -9.8067, 0));
    
    btStaticPlaneShape* planeShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
    mPlaneRigid = new btRigidBody(0, 0, planeShape);
    mDynamicsWorld->addRigidBody(mPlaneRigid);
    
    mRigidBodySys = new RigidBodySys(mDynamicsWorld);
    mWorld.attachSystem(mRigidBodySys);
    
    mLegSpringSys = new LegSpringSys(mDynamicsWorld);
    mWorld.attachSystem(mLegSpringSys);
    
    mSceneNodeSys = new SceneNodeSys(mSmgr);
    mWorld.attachSystem(mSceneNodeSys);
    
    mLocalPlayer = mWorld.newEntity();
    btVector3 size(1, 1, 1);
    mLocalPlayer->add(new RigidBodyComp(new btCapsuleShape(0.3, 0.7), 1, Vec3f(0, 1, 0), Vec3f(0, 1, 0)));
    mLocalPlayer->add(new SceneNodeComp("Guy.mesh", Vec3f(0, 0, 0)));
    mLocalPlayer->add(new LocalPlayerComp());
    mLocalPlayer->add(new LegSpringComp(
        Vec3f(0, 1, 0), // Leg start
        Vec3f(0, 0, 0), // Leg end
        80, // Stiffness
        10, // Damping
        30, // Acceleration
        20, // Deceleration
        1 // Max step up speed
    ));
    mLocalPlayer->addListener(this);
    mLocalPlayer->publish();
}

void Overworld::onEnd() {
    delete mDynamicsWorld;
    delete mSolver;
    delete mDispatcher;
    delete mCollisionConfiguration;
    delete mBroadphase;
    delete mBtDebugDrawer;
    
    delete mRayDebugDrawer;
    delete mSceneNodeSys;
    delete mRigidBodySys;
    delete mLegSpringSys;
}
void Overworld::onAddedAbove(const GameLayer* layer) {
    
}
void Overworld::onRemovedAbove(const GameLayer* layer) {
    SDL_SetRelativeMouseMode(SDL_TRUE);
}
bool Overworld::filterKeys(Uint8* keyStates) {
    return true;
}
void Overworld::onTick(float tps, const Uint8* keyStates) {
    
    mSceneNodeSys->onTick(tps);
    
    mDynamicsWorld->stepSimulation(tps, 5);
    mRigidBodySys->onTick();
    mLegSpringSys->onTick();
    
    /*
    mRayDebugDrawer->onTick(tps);
    mBtDebugDrawer->onTick();
    mDynamicsWorld->debugDrawWorld();
    */
    
    Vec3f moveVec;
    if(keyStates[SDL_GetScancodeFromKey(SDLK_w)]) {
        moveVec.z = -1;
    }
    if(keyStates[SDL_GetScancodeFromKey(SDLK_a)]) {
        moveVec.x = -1;
    }
    if(keyStates[SDL_GetScancodeFromKey(SDLK_s)]) {
        moveVec.z = 1;
    }
    if(keyStates[SDL_GetScancodeFromKey(SDLK_d)]) {
        moveVec.x = 1;
    }
    if(keyStates[SDL_GetScancodeFromKey(SDLK_g)]) {
        mLocalPlayer->broadcast(new AnimateSignal("walk"));
    }
    if(keyStates[SDL_GetScancodeFromKey(SDLK_h)]) {
        mLocalPlayer->broadcast(new AnimateSignal("idle"));
    }
    if(keyStates[SDL_GetScancodeFromKey(SDLK_f)]) {
        Vec3f absStart = mCamRollNode->convertLocalToWorldPosition(Vec3f(0, 0, 0));
        Vec3f camDir = mCamYawNode->getOrientation() * mCamPitchNode->getOrientation() * Vec3f(0, 0, -1);
        camDir *= 10;
        Vec3f absEnd = absStart + camDir;
        btCollisionWorld::AllHitsRayResultCallback rayCallback(absStart, absEnd);
        mDynamicsWorld->rayTest(absStart, absEnd, rayCallback);
        
        // mRayDebugDrawer->addRay(absStart, absEnd, 1);
        
        if(rayCallback.hasHit()) {
            Vec3f hit;
            nres::Entity* entityHit = nullptr;
            if(rayCallback.hasHit()) {
                btScalar closestHitFraction(1337);
                for(int i = rayCallback.m_collisionObjects.size() - 1; i >= 0; -- i) {

                    // If this result is closer than the closest valid result
                    if(rayCallback.m_hitFractions.at(i) <= closestHitFraction) {
                        // Get the object colliding with
                        const btCollisionObject* other = rayCallback.m_collisionObjects.at(i);
                        
                        if(other == mPlaneRigid) {
                            continue;
                        }
                        
                        void* userPtr = other->getUserPointer();
                        
                        if(userPtr) {
                            nres::Entity* entity = static_cast<nres::Entity*>(userPtr);
                            
                            if(entity) {
                                entityHit = entity;
                                closestHitFraction = rayCallback.m_hitFractions.at(i);
                                hit = rayCallback.m_hitPointWorld.at(i);
                            }
                        }
                    }
                }
            }
            
            if(entityHit) {
                entityHit->destroy();
            }
        }
    }
    
    if(!moveVec.isZero()) {
        Vec3f transl = mCamYawNode->getOrientation() * mCamPitchNode->getOrientation() * moveVec;
        transl = MathUtils::onPlane(transl, Vec3f(0, 1, 0));
        transl.normalize();
        transl *= 1.5;
        if(!transl.isNan()) {
            mLocalPlayer->broadcast(new WalkSignal(transl));
        }
    }
}


bool Overworld::onKeyPress(const SDL_KeyboardEvent& event, bool repeat) {
    switch(event.keysym.sym) {
        case SDLK_w: {
            break;
        }
        case SDLK_a: {
            break;
        }
        case SDLK_s: {
            break;
        }
        case SDLK_d: {
            break;
        }
        case SDLK_BACKQUOTE: {
            //setConsoleVisibility(true);
            break;
        }
        case SDLK_ESCAPE: {
            mGameLayerMachine->addAbove(new PauseScreen(), this);
            break;
        }
        case SDLK_q: {
            if(!repeat) {
                nres::Entity* testCube = mWorld.newEntity();
                testCube->add(new RigidBodyComp(new btSphereShape(1)));
                testCube->add(new SceneNodeComp("Lennox.mesh"));
                testCube->publish();
            }
            break;
        }
        default: {
            break;
        }
    }
    
    return true;
}
bool Overworld::onKeyRelease(const SDL_KeyboardEvent& event) {
    return true;
}

bool Overworld::onTextInput(const SDL_TextInputEvent& event) {
    return true;
}
bool Overworld::onMouseMove(const SDL_MouseMotionEvent& event) {
    
    float x = event.x;
    float y = event.y;
    float dx = event.xrel;
    float dy = event.yrel;
    
    Ogre::Radian dYaw = Ogre::Radian(dx / 200);
    Ogre::Radian dPitch = Ogre::Radian(dy / 200);
    
    mCamPitch -= dPitch;
    mCamYaw -= dYaw;
    
    if(mCamPitch > Ogre::Degree(90)) {
        mCamPitch = Ogre::Degree(90);
    }
    else if(mCamPitch < Ogre::Degree(-90)) {
        mCamPitch = Ogre::Degree(-90);
    }
    
    
    
    updateCamDolly();
    
    return true;
}

void Overworld::updateCamDolly() {
    mCamYawNode->resetOrientation();
    mCamYawNode->yaw(mCamYaw);
    mCamPitchNode->resetOrientation();
    mCamPitchNode->pitch(mCamPitch);

    mCamPitchNode->setPosition(mDollyXCoeff * mDollyScale, 0, 0);
    mCamRollNode->setPosition(0, 0, mDollyZCoeff * mDollyScale);
}


bool Overworld::onMousePress(const SDL_MouseButtonEvent& event) {
    return true;
}
bool Overworld::onMouseRelease(const SDL_MouseButtonEvent& event) {
    
    return true;
}

bool Overworld::onMouseWheel(const SDL_MouseWheelEvent& event) {
    
    float delta = -event.y;
    delta *= 0.5f;
    
    mDollyScale += delta;
    
    if(mDollyScale < mDollyMin) {
        mDollyScale = mDollyMin;
    }
    if(mDollyScale > mDollyMax) {
        mDollyScale = mDollyMax;
    }
    
    updateCamDolly();
    
    return true;
}




void Overworld::saveGame() {
    std::ofstream fileSave("save.json");
    Json::Value jsonSave;
    SerializationUtil::serializeEntities(mWorld, jsonSave["entities"]);
    fileSave << jsonSave;
    fileSave.close();
}

}

