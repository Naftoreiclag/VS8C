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

#include "DeveloperConsole.hpp"

namespace vse {

DeveloperConsole::DeveloperConsole() {
}
DeveloperConsole::~DeveloperConsole() {
}

void DeveloperConsole::onBegin(PotatoCake* potatoCake) {
}
void DeveloperConsole::onEnd() {
}

void DeveloperConsole::onTick(float tps, const Uint8* keyStates) {
}
bool DeveloperConsole::filterKeys(Uint8* keyStates) {
    return false;
}
void DeveloperConsole::onAddedAbove(const GameLayer* layer) {
}
void DeveloperConsole::onRemovedAbove(const GameLayer* layer) {
}

bool DeveloperConsole::onKeyPress(const SDL_KeyboardEvent& event, bool repeat) {
    return false;
}

bool DeveloperConsole::onKeyRelease(const SDL_KeyboardEvent& event) {
    return false;
}
bool DeveloperConsole::onTextInput(const SDL_TextInputEvent& event) {
    return false;
}
bool DeveloperConsole::onMouseMove(const SDL_MouseMotionEvent& event) {
    return false;
}
bool DeveloperConsole::onMousePress(const SDL_MouseButtonEvent& event) {
    return false;
}
bool DeveloperConsole::onMouseRelease(const SDL_MouseButtonEvent& event) {
    return false;
}
bool DeveloperConsole::onMouseWheel(const SDL_MouseWheelEvent& event) {
    return false;
}

}

