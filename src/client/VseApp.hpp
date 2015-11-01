#ifndef GRT_GARNETAPP_HPP
#define GRT_GARNETAPP_HPP

#include "btBulletDynamicsCommon.h"
#include "OgreRoot.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreRenderWindow.h"
#include "SDL_events.h"

#include "NRES.hpp"
#include "RigidBodySys.hpp"
#include "SceneNodeSys.hpp"
#include "LegSpringSys.hpp"

namespace vse {
    
class VseApp : public nres::Listener {
public:
    static VseApp& getSingleton();
public:
    btBroadphaseInterface* mBroadphase;
    btDefaultCollisionConfiguration* mCollisionConfiguration;
    btCollisionDispatcher* mDispatcher;
    btSequentialImpulseConstraintSolver* mSolver;
    
    btDiscreteDynamicsWorld* mDynamicsWorld;

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
    
    nres::Entity* mLocalPlayer;
    
    
    void onAppBegin(Ogre::Root* ogreRoot, Ogre::RenderWindow* ogreWindow, SDL_Window* sdlWindow);
    
    // User wants to close application
    void onAppEnd();
    
    // Ticks
    void onTick(float tps);
    
    // Key handling
    void onKeyPress(const SDL_KeyboardEvent& event);
    void onKeyRelease(const SDL_KeyboardEvent& event);
    
    // Mouse handling
    void onMouseMove(const SDL_MouseMotionEvent& event);
    void onMousePress(const SDL_MouseButtonEvent& event);
    void onMouseRelease(const SDL_MouseButtonEvent& event);
    void onMouseWheel(const SDL_MouseWheelEvent& event);
    
    virtual void onEntityExists(nres::Entity* entity);
    virtual void onEntityDestroyed(nres::Entity* entity);
    virtual void onEntityBroadcast(nres::Entity* entity, const EntSignal* data);
    
    VseApp();
    ~VseApp();
};

}

#endif // GRT_GARNETAPP_HPP
