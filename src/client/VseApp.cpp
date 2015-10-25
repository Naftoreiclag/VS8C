#include "VseApp.hpp"

#include <stdint.h>
#include <iostream>

#include "OgreEntity.h"
#include "SDL.h"

#include "BoxSys.hpp"
#include "BoxComp.hpp"

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

void VseApp::initialize(Ogre::Root* ogreRoot, Ogre::RenderWindow* ogreWindow, SDL_Window* sdlWindow) {
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
    mCam->setNearClipDistance(5);
    
    mCamLocNode = mRootNode->createChildSceneNode("CameraNode");
    mCamYawNode = mCamLocNode->createChildSceneNode();
    mCamPitchNode = mCamYawNode->createChildSceneNode();
    mCamRollNode = mCamPitchNode->createChildSceneNode();
    mCamRollNode->attachObject(mCam);
    
    mCam->setAspectRatio(Ogre::Real(1280) / Ogre::Real(720));
    
    Ogre::Viewport* viewport = ogreWindow->addViewport(mCam);
    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    
    Ogre::SceneNode* headNode = mSmgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Entity* ogreHead = mSmgr->createEntity("Head", "Cube.mesh");
    headNode->attachObject(ogreHead);
    headNode->setPosition(0, 0, -80);
    
    Ogre::SceneNode* groundNode = mSmgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Entity* groundEnt = mSmgr->createEntity("Ground", "ground.mesh");
    groundNode->attachObject(groundEnt);
    
    mSmgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    
    mSmgr->setSkyBox(true, "Test");
    
    Ogre::Light* light = mSmgr->createLight("Light");
    light->setPosition(20,80,50);
    
    mWorld.attachSystem(&mBoxSys);
    mTestCube = mWorld.newEntity();
    mTestCube->add(new BoxComp());
    mTestCube->publish();
}

void VseApp::onClose() {
}
void VseApp::onTick(float tps) {
    
    mBoxSys.tick(tps);
    
    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
    
    Ogre::Vector3 moveVec;
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
        mCamLocNode->translate(mCamYawNode->getOrientation() * mCamPitchNode->getOrientation() * moveVec, Ogre::SceneNode::TS_LOCAL);
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

