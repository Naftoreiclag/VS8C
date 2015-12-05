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
    ~BulletDebugDrawer();
    
    Ogre::SceneManager* mSmgr;
    Ogre::ManualObject* mLines;
    
    void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
    void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
    void reportErrorWarning(const char* warningString);
    void draw3dText(const btVector3& location, const char* textString);
    void setDebugMode(int debugMode);
    int getDebugMode() const;
    
    void onTick();
};

}

#endif // VSE_BULLETDEBUGDRAWER_HPP
