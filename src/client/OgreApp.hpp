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

#ifndef GRT_OGREAPP_HPP
#define GRT_OGREAPP_HPP

#include <string>

#include "CEGUI/CEGUI.h"
#include "CEGUI/RendererModules/Ogre/Renderer.h"
#include "OgreRoot.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreRenderWindow.h"
#include "SDL_syswm.h"

namespace vse {

class OgreApp {
public:
    OgreApp();
    virtual ~OgreApp();
public:
    static OgreApp& getSingleton();
    void run();
public:
    // It's alive... alive!
    Ogre::RenderWindow* mOgreWindow;
    SDL_Window* mSdlWindow;
    CEGUI::Window* mCeguiWindow;
    
    Ogre::Root* mOgreRoot;
    CEGUI::OgreRenderer* mCeguiRenderer;

};

}

#endif // GRT_OGREAPP_HPP
