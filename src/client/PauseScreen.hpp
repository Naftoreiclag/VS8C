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

#ifndef VSE_PAUSESCREEN_HPP
#define VSE_PAUSESCREEN_HPP

#include "GameLayer.hpp"

namespace vse {

class PauseScreen : public GameLayer {
public:
    PauseScreen();
    ~PauseScreen();

public:

    CEGUI::Window* mCeguiWindow;
    CEGUI::Window* mPauseWindow;
    
    // Lifecycle
    void onBegin(
        GameLayerMachine* glmachine,
        Ogre::Root* ogreRoot, 
        Ogre::RenderWindow* ogreWindow, 
        SDL_Window* sdlWindow, 
        CEGUI::OgreRenderer* ceguiRenderer,
        CEGUI::Window* ceguiWindow);
    void onEnd();
    
    // Ticks
    void onTick(float tps);
    
    // Layering
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
};

}

#endif // VSE_PAUSESCREEN_HPP
