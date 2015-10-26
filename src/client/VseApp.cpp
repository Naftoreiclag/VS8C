#include "VseApp.hpp"

#include <stdint.h>
#include <iostream>

#include "OgreEntity.h"
#include "SDL.h"

#include "BoxSys.hpp"
#include "BoxComp.hpp"
#include "LocalPlayerComp.hpp"
#include "LocalPlayerMoveSignal.hpp"

#include "Vec3f.hpp"

namespace vse
{
    
VseApp& VseApp::getSingleton() {
    static VseApp instance;
    return instance;
}

VseApp::VseApp() {
}

VseApp::~VseApp() {
}

void VseApp::onAppBegin(Ogre::Root* ogreRoot, Ogre::RenderWindow* ogreWindow, SDL_Window* sdlWindow) {
    mOgreRoot = ogreRoot;
    mOgreWindow = ogreWindow;
    mSdlWindow = sdlWindow;
    
    SDL_SetRelativeMouseMode(SDL_TRUE);
    
    mCamPitch = Ogre::Degree(0);
    mCamYaw = Ogre::Degree(0);
    mCamRoll = Ogre::Degree(0);
    
    mSmgr = mOgreRoot->createSceneManager(Ogre::ST_GENERIC);
    mRootNode = mSmgr->getRootSceneNode();
    
    mCam = mSmgr->createCamera("Camera");
    mCam->setNearClipDistance(0.1f);
    
    mCamLocNode = mRootNode->createChildSceneNode("CameraNode");
    mCamYawNode = mCamLocNode->createChildSceneNode();
    mCamPitchNode = mCamYawNode->createChildSceneNode();
    mCamRollNode = mCamPitchNode->createChildSceneNode();
    mCamRollNode->attachObject(mCam);
    
    mCam->setAspectRatio(Ogre::Real(1280) / Ogre::Real(720));
    
    mSmgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    mSmgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    mSmgr->setSkyBox(true, "Test");
    
    Ogre::Viewport* viewport = ogreWindow->addViewport(mCam);
    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    
    Ogre::SceneNode* groundNode = mSmgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Entity* groundEnt = mSmgr->createEntity("Ground", "ground.mesh");
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
    
    mBoxSys = new BoxSys();
    mWorld.attachSystem(mBoxSys);
    
    mLocalPlayer = mWorld.newEntity();
    btVector3 size(1, 1, 1);
    mLocalPlayer->add(new BoxComp(new btBoxShape(size)));
    mLocalPlayer->add(new LocalPlayerComp());
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
    mBoxSys->onTick(tps);
    
    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
    
    Vec3f moveVec;
    float spd = tps * 5;
    bool moved = false;
    if(keyStates[SDL_GetScancodeFromKey(SDLK_w)]) {
        moveVec.z = -spd;
        moved = true;
    }
    if(keyStates[SDL_GetScancodeFromKey(SDLK_a)]) {
        moveVec.x = -spd;
        moved = true;
    }
    if(keyStates[SDL_GetScancodeFromKey(SDLK_s)]) {
        moveVec.z = spd;
        moved = true;
    }
    if(keyStates[SDL_GetScancodeFromKey(SDLK_d)]) {
        moveVec.x = spd;
        moved = true;
    }
    
    if(moved) {
        Vec3f transl = mCamYawNode->getOrientation() * mCamPitchNode->getOrientation() * moveVec;
        //mLocalPlayer->broadcast(new LocalPlayerMoveSignal(transl * 100));
        mCamLocNode->translate(transl, Ogre::SceneNode::TS_LOCAL);
    }
    
    if(keyStates[SDL_GetScancodeFromKey(SDLK_p)]) {
        mLocalPlayer->broadcast(new LocalPlayerMoveSignal(Vec3f(0, 100, 0)));
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
            btVector3 size(1, 1, 1);
            testCube->add(new BoxComp(new btBoxShape(size)));
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
    
    mCamYawNode->resetOrientation();
    mCamYawNode->yaw(mCamYaw);
    mCamPitchNode->resetOrientation();
    mCamPitchNode->pitch(mCamPitch);
    
}
void VseApp::onMousePress(const SDL_MouseButtonEvent& event) {
}
void VseApp::onMouseRelease(const SDL_MouseButtonEvent& event) {
    
}
}

