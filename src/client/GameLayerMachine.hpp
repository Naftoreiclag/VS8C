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

#ifndef VSE_GAMELAYERMACHINE_HPP
#define VSE_GAMELAYERMACHINE_HPP

#include <vector>

#include "GameLayer.hpp"

namespace vse {

class GameLayerMachine {
public:
    GameLayerMachine(
        Ogre::Root* ogreRoot, 
        Ogre::RenderWindow* ogreWindow, 
        SDL_Window* sdlWindow, 
        CEGUI::OgreRenderer* ceguiRenderer,
        CEGUI::Window* ceguiWindow);
    ~GameLayerMachine();
    
    Ogre::Root* mOgreRoot;
    Ogre::RenderWindow* mOgreWindow;
    SDL_Window* mSdlWindow;
    CEGUI::OgreRenderer* mCeguiRenderer;
    CEGUI::Window* mCeguiWindow;

private:
    std::vector<GameLayer*> mLayers;
public:
    void setBase(GameLayer* gm);
    void addAbove(GameLayer* caller, GameLayer* gm);
    void remove(GameLayer* gm);
    void removeAll();
    
    // Ticks
    void onTick(float tps);
    
    // Key handling
    void onKeyPress(const SDL_KeyboardEvent& event, bool repeat);
    void onKeyRelease(const SDL_KeyboardEvent& event);
    void onTextInput(const SDL_TextInputEvent& event);
    
    // Mouse handling
    void onMouseMove(const SDL_MouseMotionEvent& event);
    void onMousePress(const SDL_MouseButtonEvent& event);
    void onMouseRelease(const SDL_MouseButtonEvent& event);
    void onMouseWheel(const SDL_MouseWheelEvent& event);
};

}

#endif // VSE_GAMELAYERMACHINE_HPP
