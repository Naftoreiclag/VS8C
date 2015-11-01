#include "VseApp.hpp"

#include <stdint.h>
#include <iostream>

#include "OgreMath.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"
#include "SDL.h"

#include "RigidBodySys.hpp"
#include "RigidBodyComp.hpp"
#include "SceneNodeComp.hpp"
#include "LocalPlayerComp.hpp"
#include "LegSpringComp.hpp"
#include "WalkSignal.hpp"
#include "EntSignal.hpp"
#include "LocationSignal.hpp"

#include "Vec3f.hpp"

namespace vse {
    
void VseApp::onEntityExists(nres::Entity* entity) {}
void VseApp::onEntityDestroyed(nres::Entity* entity) {}

void VseApp::onEntityBroadcast(nres::Entity* entity, const EntSignal* data) {
    switch(data->getType()) {
        case EntSignal::Type::LOCATION: {
            LocationSignal* signal = (LocationSignal*) data;
            
            mCamLocNode->setPosition(signal->mLocationUpdate);
            
            break;
        }
        default: {
            break;
        }
    }
}
    
VseApp& VseApp::getSingleton() {
    static VseApp instance;
    return instance;
}

VseApp::VseApp() {}
VseApp::~VseApp() {}

void VseApp::onAppBegin(Ogre::Root* ogreRoot, Ogre::RenderWindow* ogreWindow, SDL_Window* sdlWindow) {
    mOgreRoot = ogreRoot;
    mOgreWindow = ogreWindow;
    mSdlWindow = sdlWindow;
    
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
    mSmgr->setShadowTextureSize(1024);
    mSmgr->setShadowTextureFSAA(2);
    mSmgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE); // SHADOWTYPE_TEXTURE_ADDITIVE
    mSmgr->setSkyBox(true, "Test");
    
    Ogre::Viewport* viewport = ogreWindow->addViewport(mCam);
    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    
    Ogre::SceneNode* groundNode = mSmgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Entity* groundEnt = mSmgr->createEntity("Ground", "ground.mesh");
    //groundEnt->getSubEntity(0)->getMaterial()->setReceiveShadows(true);
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
    mDynamicsWorld->setGravity(btVector3(0, -9.8067, 0));
    
	btStaticPlaneShape* planeShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	btRigidBody* planeRigid = new btRigidBody(0, 0, planeShape);
	mDynamicsWorld->addRigidBody(planeRigid);
    
    mRigidBodySys = new RigidBodySys(mDynamicsWorld);
    mWorld.attachSystem(mRigidBodySys);
    
    mLegSpringSys = new LegSpringSys(mDynamicsWorld);
    mWorld.attachSystem(mLegSpringSys);
    
    mSceneNodeSys = new SceneNodeSys(mSmgr);
    mWorld.attachSystem(mSceneNodeSys);
    
    mLocalPlayer = mWorld.newEntity();
    btVector3 size(1, 1, 1);
    mLocalPlayer->add(new RigidBodyComp(new btBoxShape(size)));
    mLocalPlayer->add(new SceneNodeComp("Cube.mesh"));
    mLocalPlayer->add(new LocalPlayerComp());
    mLocalPlayer->add(new LegSpringComp(
        Vec3f(0, 0, 0), // Leg start
        Vec3f(0, -3, 0), // Leg end
        80, // Stiffness
        10, // Damping
        30, // Acceleration
        20 // Deceleration
    ));
    mLocalPlayer->addListener(this);
    mLocalPlayer->publish();
    
}

void VseApp::onAppEnd() {
    delete mDynamicsWorld;
    delete mSolver;
    delete mDispatcher;
    delete mCollisionConfiguration;
    delete mBroadphase;
}
void VseApp::onTick(float tps) {
    
    mDynamicsWorld->stepSimulation(tps, 5);
    mRigidBodySys->onTick();
    mLegSpringSys->onTick();
    
    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
    
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
    
    if(!moveVec.isZero()) {
        Vec3f transl = mCamYawNode->getOrientation() * mCamPitchNode->getOrientation() * moveVec;
        transl.normalize();
        transl *= 5;
        mLocalPlayer->broadcast(new WalkSignal(transl));
    }
    
    if(keyStates[SDL_GetScancodeFromKey(SDLK_p)]) {
        //mLocalPlayer->broadcast(new LocalPlayerMoveSignal(Vec3f(0, 100, 0)));
    }
}


void VseApp::onKeyPress(const SDL_KeyboardEvent& event) {
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
        case SDLK_q: {
            nres::Entity* testCube = mWorld.newEntity();
            testCube->add(new RigidBodyComp(new btSphereShape(1)));
            testCube->add(new SceneNodeComp("Ball.mesh"));
            testCube->publish();
            break;
        }
        default: {
            break;
        }
    }
}
void VseApp::onKeyRelease(const SDL_KeyboardEvent& event) {
}
void VseApp::onMouseMove(const SDL_MouseMotionEvent& event) {
    
    float dx = -event.xrel;
    float dy = -event.yrel;
    Ogre::Radian dYaw = Ogre::Radian(dx / 200);
    Ogre::Radian dPitch = Ogre::Radian(dy / 200);
    
    mCamPitch += dPitch;
    mCamYaw += dYaw;
    
    if(mCamPitch > Ogre::Degree(90)) {
        mCamPitch = Ogre::Degree(90);
    }
    else if(mCamPitch < Ogre::Degree(-90)) {
        mCamPitch = Ogre::Degree(-90);
    }
    
    updateCamDolly();
}

void VseApp::updateCamDolly() {
    mCamYawNode->resetOrientation();
    mCamYawNode->yaw(mCamYaw);
    mCamPitchNode->resetOrientation();
    mCamPitchNode->pitch(mCamPitch);

    mCamPitchNode->setPosition(mDollyXCoeff * mDollyScale, 0, 0);
    mCamRollNode->setPosition(0, 0, mDollyZCoeff * mDollyScale);
}

void VseApp::onMousePress(const SDL_MouseButtonEvent& event) {
}
void VseApp::onMouseRelease(const SDL_MouseButtonEvent& event) {
    
}

void VseApp::onMouseWheel(const SDL_MouseWheelEvent& event) {
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
}
}

