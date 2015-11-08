#include "RayDebugDrawer.hpp"

#include <string>

#include "OgreManualObject.h"
#include "OgreTextureUnitState.h"
#include "OgreColourValue.h"

#include "Vec3f.hpp"

namespace vse {

RayDebugDrawer::RayDebugDrawer(Ogre::SceneManager* smgr)
: mSmgr(smgr) {
    std::string matName = "Ray Debug Material";
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getDefaultSettings()->clone(matName);
    material->setReceiveShadows(false);
    material->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    material->setDepthBias(0.1, 0);
    Ogre::TextureUnitState* texUnit = material->getTechnique(0)->getPass(0)->createTextureUnitState();
    texUnit->setColourOperationEx(Ogre::LBX_SOURCE1, Ogre::LBS_DIFFUSE);
    material->getTechnique(0)->setLightingEnabled(false);
    
    mLines = new Ogre::ManualObject("Ray Debug Lines");
    mLines->setDynamic(true);
    mLines->begin(matName, Ogre::RenderOperation::OT_LINE_LIST);
    mLines->position(Vec3f(0, 0, 0));
    mLines->colour(Ogre::ColourValue::White);
    mLines->position(Vec3f(0, 0, 0));
    mLines->colour(Ogre::ColourValue::White);
    
    mSmgr->getRootSceneNode()->attachObject(mLines);
}

RayDebugDrawer::~RayDebugDrawer() {
    delete mLines;
}

void RayDebugDrawer::addRay(Vec3f start, Vec3f end, int16_t id, float lifetime) {
    Ray ray;
    ray.start = start;
    ray.end = end;
    ray.id = id;
    ray.deathTimer = lifetime;
    
    mRays.push_back(ray);
}

void RayDebugDrawer::onTick(float tps) {
    mLines->end();
    mLines->beginUpdate(0);
    
    std::vector<Ray>::iterator iter = mRays.begin();
    while(iter != mRays.end()) {
        Ray& ray = *iter;
        Ogre::ColourValue ogreColor(1, 1, 0);
        ogreColor.saturate();
        
        mLines->position(ray.start);
        mLines->colour(ogreColor);
        mLines->position(ray.end);
        mLines->colour(ogreColor);
        
        // Death is calculated after rendering to ensure each ray renders for at least 1 frame
        ray.deathTimer -= tps;
        if(ray.deathTimer <= 0) {
            iter = mRays.erase(iter);
        }
        else {
            ++ iter;
        }
    }
}



}

