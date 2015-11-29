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

#include "CeguiInjector.hpp"

#include "CeguiUtil.hpp"

namespace vse {

CeguiInjector::CeguiInjector() { }
CeguiInjector::~CeguiInjector() { }

void CeguiInjector::onBegin(
        GameLayerMachine* glmachine,
        Ogre::Root* ogreRoot, 
        Ogre::RenderWindow* ogreWindow, 
        SDL_Window* sdlWindow, 
        CEGUI::OgreRenderer* ceguiRenderer,
        CEGUI::Window* ceguiWindow) { }
void CeguiInjector::onEnd() { }

bool CeguiInjector::onTick(float tps, const Uint8* keyStates) { return false; }
void CeguiInjector::onAddedAbove(const GameLayer* layer) { }
void CeguiInjector::onRemovedAbove(const GameLayer* layer) { }

bool CeguiInjector::onKeyPress(const SDL_KeyboardEvent& event, bool repeat) {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(CeguiUtil::toCeguiScancode(event.keysym.scancode));
    return false;
}

bool CeguiInjector::onKeyRelease(const SDL_KeyboardEvent& event) {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(CeguiUtil::toCeguiScancode(event.keysym.scancode));
    return false;
}
bool CeguiInjector::onTextInput(const SDL_TextInputEvent& event) {
    if(event.text != 0) {
        CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(CEGUI::String(event.text).at(0));
    }
    return false;
}
bool CeguiInjector::onMouseMove(const SDL_MouseMotionEvent& event) {
    float x = event.x;
    float y = event.y;
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(x, y);
    return false;
}
bool CeguiInjector::onMousePress(const SDL_MouseButtonEvent& event) {
    switch(event.button) {
        case SDL_BUTTON_LEFT: {
            CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::LeftButton);
            break;
        }
        case SDL_BUTTON_MIDDLE: {
            CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::MiddleButton);
            break;
        }
        case SDL_BUTTON_RIGHT: {
            CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::RightButton);
            break;
        }
    }
    
    return false;
}
bool CeguiInjector::onMouseRelease(const SDL_MouseButtonEvent& event) {
    switch(event.button) {
        case SDL_BUTTON_LEFT: {
            CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::LeftButton);
            break;
        }
        case SDL_BUTTON_MIDDLE: {
            CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::MiddleButton);
            break;
        }
        case SDL_BUTTON_RIGHT: {
            CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::RightButton);
            break;
        }
    }
    
    return false;
}
bool CeguiInjector::onMouseWheel(const SDL_MouseWheelEvent& event) {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseWheelChange(event.y);
    return false;
}


}

