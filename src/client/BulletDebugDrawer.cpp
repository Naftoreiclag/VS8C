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

#include "BulletDebugDrawer.hpp"

#include <string>
#include "OgreTextureUnitState.h"
#include "OgreColourValue.h"

#include "Vec3f.hpp"

namespace vse {

BulletDebugDrawer::BulletDebugDrawer(Ogre::SceneManager* smgr)
: mSmgr(smgr)
, mDebugMode(btIDebugDraw::DBG_DrawWireframe) {
    
    std::string matName = "Bullet Debug Material";
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getDefaultSettings()->clone(matName);
    material->setReceiveShadows(false);
    material->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    material->setDepthBias(0.1, 0);
    Ogre::TextureUnitState* texUnit = material->getTechnique(0)->getPass(0)->createTextureUnitState();
    texUnit->setColourOperationEx(Ogre::LBX_SOURCE1, Ogre::LBS_DIFFUSE);
    material->getTechnique(0)->setLightingEnabled(false);
    
    mLines = new Ogre::ManualObject("Bullet Debug Lines");
    mLines->setDynamic(true);
    mLines->begin(matName, Ogre::RenderOperation::OT_LINE_LIST);
    mLines->position(Vec3f(0, 0, 0));
    mLines->colour(Ogre::ColourValue::White);
    mLines->position(Vec3f(0, 0, 0));
    mLines->colour(Ogre::ColourValue::White);
    
    mSmgr->getRootSceneNode()->attachObject(mLines);
}

BulletDebugDrawer::~BulletDebugDrawer() {
    delete mLines;
}

void BulletDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
    Ogre::ColourValue ogreColor(color.getX(), color.getY(), color.getZ());
    ogreColor.saturate();
    
    mLines->position(Vec3f(from));
    mLines->colour(ogreColor);
    mLines->position(Vec3f(to));
    mLines->colour(ogreColor);
}
void BulletDebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {}
void BulletDebugDrawer::reportErrorWarning(const char* warningString) {}
void BulletDebugDrawer::draw3dText(const btVector3& location, const char* textString) {}

void BulletDebugDrawer::onTick() {
    mLines->end();
    mLines->beginUpdate(0);
}

void BulletDebugDrawer::setDebugMode(int debugMode) {
    mDebugMode = debugMode;
}

int BulletDebugDrawer::getDebugMode() const {
    return mDebugMode;
}



}

