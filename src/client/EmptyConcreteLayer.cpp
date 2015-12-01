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

#include "EmptyConcreteLayer.hpp"


namespace vse {

EmptyConcreteLayer::EmptyConcreteLayer() {
}
EmptyConcreteLayer::~EmptyConcreteLayer() {
}

void EmptyConcreteLayer::onBegin(PotatoCake* potatoCake) {
}
void EmptyConcreteLayer::onEnd() {
}

void EmptyConcreteLayer::onTick(float tps, const Uint8* keyStates) {
}
bool EmptyConcreteLayer::filterKeys(Uint8* keyStates) {
    return false;
}
void EmptyConcreteLayer::onAddedAbove(const GameLayer* layer) {
}
void EmptyConcreteLayer::onRemovedAbove(const GameLayer* layer) {
}

bool EmptyConcreteLayer::onKeyPress(const SDL_KeyboardEvent& event, bool repeat) {
    return false;
}

bool EmptyConcreteLayer::onKeyRelease(const SDL_KeyboardEvent& event) {
    return false;
}
bool EmptyConcreteLayer::onTextInput(const SDL_TextInputEvent& event) {
    return false;
}
bool EmptyConcreteLayer::onMouseMove(const SDL_MouseMotionEvent& event) {
    return false;
}
bool EmptyConcreteLayer::onMousePress(const SDL_MouseButtonEvent& event) {
    return false;
}
bool EmptyConcreteLayer::onMouseRelease(const SDL_MouseButtonEvent& event) {
    return false;
}
bool EmptyConcreteLayer::onMouseWheel(const SDL_MouseWheelEvent& event) {
    return false;
}

}
