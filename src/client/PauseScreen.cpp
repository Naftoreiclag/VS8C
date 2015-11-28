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
    Ogre::Root* ogreRoot, 
    Ogre::RenderWindow* ogreWindow, 
    SDL_Window* sdlWindow, 
    CEGUI::OgreRenderer* ceguiRenderer,
    CEGUI::Window* ceguiWindow) { }
void PauseScreen::onEnd() { }

// Ticks
void PauseScreen::onTick(float tps) { }

// Layering
void PauseScreen::onAddedAbove(const GameLayer* layer) { }
void PauseScreen::onRemovedAbove(const GameLayer* layer) { }

// Key handling
bool PauseScreen::onKeyPress(const SDL_KeyboardEvent& event, bool repeat) { return false; }
bool PauseScreen::onKeyRelease(const SDL_KeyboardEvent& event) { return false; }
bool PauseScreen::onTextInput(const SDL_TextInputEvent& event) { return false; }

// Mouse handling
bool PauseScreen::onMouseMove(const SDL_MouseMotionEvent& event) { return false; }
bool PauseScreen::onMousePress(const SDL_MouseButtonEvent& event) { return false; }
bool PauseScreen::onMouseRelease(const SDL_MouseButtonEvent& event) { return false; }
bool PauseScreen::onMouseWheel(const SDL_MouseWheelEvent& event) { return false; }

}
