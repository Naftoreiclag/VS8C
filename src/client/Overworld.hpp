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

#ifndef GRT_GARNETAPP_HPP
#define GRT_GARNETAPP_HPP

#include "btBulletDynamicsCommon.h"
#include "CEGUI/CEGUI.h"
#include "CEGUI/RendererModules/Ogre/Renderer.h"
#include "OgreRoot.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreRenderWindow.h"
#include "SDL_events.h"

#include "GameLayer.hpp"
#include "NRES.hpp"
#include "RigidBodySys.hpp"
#include "SceneNodeSys.hpp"
#include "LegSpringSys.hpp"
#include "BulletDebugDrawer.hpp"
#include "RayDebugDrawer.hpp"

namespace vse {
    
class Overworld : public GameLayer, public nres::Listener  {
public:
    GameLayerMachine* mGameLayerMachine;
    
    btBroadphaseInterface* mBroadphase;
    btDefaultCollisionConfiguration* mCollisionConfiguration;
    btCollisionDispatcher* mDispatcher;
    btSequentialImpulseConstraintSolver* mSolver;
    
    btDiscreteDynamicsWorld* mDynamicsWorld;
    
    btRigidBody* mPlaneRigid;
    
    CEGUI::OgreRenderer* mCeguiRenderer;
    CEGUI::Window* mCeguiWindow;
    
    CEGUI::Window* mConsoleWindow;
    CEGUI::Window* mInventoryWindow;

    Ogre::Root* mOgreRoot;
    Ogre::Camera* mCam;
    Ogre::SceneManager* mSmgr;
    
    Ogre::RenderWindow* mOgreWindow;
    SDL_Window* mSdlWindow;
    
    Ogre::SceneNode* mRootNode;
    
    // Camera location
    Ogre::SceneNode* mCamLocNode;
    
    // Camera orientation producers
    Ogre::SceneNode* mCamPitchNode;
    Ogre::SceneNode* mCamYawNode;
    Ogre::SceneNode* mCamRollNode;
    
    // Determines orientation
    Ogre::Degree mCamPitch;
    Ogre::Degree mCamYaw;
    Ogre::Degree mCamRoll;
    
    float mDollyScale;
    float mDollyMax;
    float mDollyMin;
    
    Ogre::Degree mDollyAngle;
    float mDollyXCoeff;
    float mDollyZCoeff;
    
    
    void updateCamDolly();
    
    nres::World mWorld;
    SceneNodeSys* mSceneNodeSys;
    RigidBodySys* mRigidBodySys;
    LegSpringSys* mLegSpringSys;
    BulletDebugDrawer* mBtDebugDrawer;
    RayDebugDrawer* mRayDebugDrawer;
    
    nres::Entity* mLocalPlayer;
    
    void onBegin(PotatoCake* potatoCake);
    void onEnd();
    
    // Ticks
    void onTick(float tps, const Uint8* keyStates);
    
    // Layering
    bool filterKeys(Uint8* keyStates);
    void onAddedAbove(const GameLayer* layer);
    void onRemovedAbove(const GameLayer* layer);
    
    // Key handling
    bool onKeyPress(const SDL_KeyboardEvent& event, bool repeat);
    bool onKeyRelease(const SDL_KeyboardEvent& event);
    bool onTextInput(const SDL_TextInputEvent& event);
    
    // Mouse handling
    bool onMouseMove(const SDL_MouseMotionEvent& event);
    bool onMousePress(const SDL_MouseButtonEvent& event);
    bool onMouseRelease(const SDL_MouseButtonEvent& event);
    bool onMouseWheel(const SDL_MouseWheelEvent& event);
    
    void onEntityExists(nres::Entity* entity);
    void onEntityDestroyed(nres::Entity* entity);
    void onEntityBroadcast(nres::Entity* entity, const EntSignal* data);
    
    // Console
    bool onConsoleSubmitClicked(const CEGUI::EventArgs& args);
    bool onConsoleEditboxTextAccepted(const CEGUI::EventArgs& args);
    bool onConsoleTextSubmitted(const CEGUI::String& text);
    bool onConsoleCloseClicked(const CEGUI::EventArgs& args);
    void outputConsoleText(const CEGUI::String& text, CEGUI::Colour color = CEGUI::Colour(1.f, 1.f, 1.f));
    void setConsoleVisibility(bool visible);
    
    //
    void saveGame();
    
    Overworld();
    ~Overworld();
};

}

#endif // GRT_GARNETAPP_HPP
