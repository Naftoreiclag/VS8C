#ifndef VSE_BULLETDEBUGDRAWER_HPP
#define VSE_BULLETDEBUGDRAWER_HPP

#include "btBulletDynamicsCommon.h"

#include "OgreManualObject.h"
#include "OgreSceneManager.h"

namespace vse {

class BulletDebugDrawer : public btIDebugDraw {
private:
    int mDebugMode;
public:
    BulletDebugDrawer(Ogre::SceneManager* smgr);
    virtual ~BulletDebugDrawer();
    
    Ogre::SceneManager* mSmgr;
    Ogre::ManualObject* mLines;
    
    virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
    virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
    virtual void reportErrorWarning(const char* warningString);
    virtual void draw3dText(const btVector3& location, const char* textString);
    virtual void setDebugMode(int debugMode);
    virtual int getDebugMode() const;
    
    void onTick();
};

}

#endif // VSE_BULLETDEBUGDRAWER_HPP
