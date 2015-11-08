#ifndef VSE_RAYDEBUGDRAWER_HPP
#define VSE_RAYDEBUGDRAWER_HPP

#include <stdint.h>
#include <vector>

#include "OgreSceneManager.h"

#include "Vec3f.hpp"

namespace vse {

class RayDebugDrawer {
private:
    struct Ray {
        int16_t id;
        
        Vec3f start;
        Vec3f end;
        
        float deathTimer;
    };
public:
    RayDebugDrawer(Ogre::SceneManager* smgr);
    ~RayDebugDrawer();
    
    std::vector<Ray> mRays;
    
    Ogre::SceneManager* mSmgr;
    Ogre::ManualObject* mLines;
    
    void addRay(Vec3f start, Vec3f end, int16_t id = -1, float lifetime = 1);
    
    void onTick(float tps);
};

}

#endif // VSE_RAYDEBUGDRAWER_HPP
