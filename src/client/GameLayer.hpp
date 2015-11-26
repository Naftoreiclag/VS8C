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

#ifndef VSE_GAMELAYER_HPP
#define VSE_GAMELAYER_HPP

#include "btBulletDynamicsCommon.h"
#include "CEGUI/CEGUI.h"
#include "CEGUI/RendererModules/Ogre/Renderer.h"
#include "OgreRoot.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreRenderWindow.h"
#include "SDL_events.h"

namespace vse {

class GameLayer {
public:
    GameLayer();
    virtual ~GameLayer();
public:
    // Lifecycle
    virtual void onBegin(
        Ogre::Root* ogreRoot, 
        Ogre::RenderWindow* ogreWindow, 
        SDL_Window* sdlWindow, 
        CEGUI::OgreRenderer* ceguiRenderer,
        CEGUI::Window* ceguiWindow) = 0;
    virtual void onEnd() = 0;
    
    // Ticks
    virtual void onTick(float tps) = 0;
    
    // Layering
    virtual void onAddedAbove(const GameLayer* layer) = 0;
    virtual void onRemovedAbove(const GameLayer* layer) = 0;
    
    // Key handling
    virtual bool onKeyPress(const SDL_KeyboardEvent& event, bool repeat) = 0;
    virtual bool onKeyRelease(const SDL_KeyboardEvent& event) = 0;
    virtual bool onTextInput(const SDL_TextInputEvent& event) = 0;
    
    // Mouse handling
    virtual bool onMouseMove(const SDL_MouseMotionEvent& event) = 0;
    virtual bool onMousePress(const SDL_MouseButtonEvent& event) = 0;
    virtual bool onMouseRelease(const SDL_MouseButtonEvent& event) = 0;
    virtual bool onMouseWheel(const SDL_MouseWheelEvent& event) = 0;
};

}

#endif // VSE_GAMELAYER_HPP
