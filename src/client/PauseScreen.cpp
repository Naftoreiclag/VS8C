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

#include "PauseScreen.hpp"

#include <iostream>

#include "CeguiFrames.hpp"

namespace vse
{

PauseScreen::PauseScreen()
{
}

PauseScreen::~PauseScreen()
{
}

// Lifecycle
void PauseScreen::onBegin(
        GameLayerMachine* glmachine,
        Ogre::Root* ogreRoot, 
        Ogre::RenderWindow* ogreWindow, 
        SDL_Window* sdlWindow, 
        CEGUI::OgreRenderer* ceguiRenderer,
        CEGUI::Window* ceguiWindow) {
    
    mCeguiWindow = ceguiWindow;
    
    mPauseWindow = CeguiFrames::getSingleton().getPauseWindow();
    mPauseWindow->setVisible(true);
}
void PauseScreen::onEnd() {
    
    mPauseWindow->setVisible(false);
}

// Ticks
bool PauseScreen::onTick(float tps, const Uint8* keyStates) { return true; }

// Layering
void PauseScreen::onAddedAbove(const GameLayer* layer) { }
void PauseScreen::onRemovedAbove(const GameLayer* layer) { }

// Key handling
bool PauseScreen::onKeyPress(const SDL_KeyboardEvent& event, bool repeat) { return true; }
bool PauseScreen::onKeyRelease(const SDL_KeyboardEvent& event) { return true; }
bool PauseScreen::onTextInput(const SDL_TextInputEvent& event) { return true; }

// Mouse handling
bool PauseScreen::onMouseMove(const SDL_MouseMotionEvent& event) { return true; }
bool PauseScreen::onMousePress(const SDL_MouseButtonEvent& event) { return true; }
bool PauseScreen::onMouseRelease(const SDL_MouseButtonEvent& event) { return true; }
bool PauseScreen::onMouseWheel(const SDL_MouseWheelEvent& event) { return true; }

}
