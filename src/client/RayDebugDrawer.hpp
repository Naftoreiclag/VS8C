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
