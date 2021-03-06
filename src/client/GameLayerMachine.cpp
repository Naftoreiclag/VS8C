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

#include "GameLayerMachine.hpp"

#include <algorithm>

#include "GameLayer.hpp"

namespace vse {

Uint8* GameLayerMachine::sRelaxedKeyStates = nullptr;
int GameLayerMachine::sNumKeyStates = 0;
    
GameLayerMachine::GameLayerMachine(
    PotatoCake* potatoCake)
: mPotatoCake(potatoCake) {
    if(!sRelaxedKeyStates) {
        SDL_GetKeyboardState(&sNumKeyStates);
        
        sRelaxedKeyStates = new Uint8[sNumKeyStates];
        
        for(int i = 0; i < sNumKeyStates; ++ i) {
            sRelaxedKeyStates[i] = SDL_FALSE;
        }
    }
    
    mFilteredKeyStates = new Uint8[sNumKeyStates];
}

GameLayerMachine::~GameLayerMachine() {}

void GameLayerMachine::addBottom(GameLayer* addMe) {
    mLayers.insert(mLayers.begin(), addMe);
    addMe->onBegin(mPotatoCake);
}
void GameLayerMachine::addAbove(GameLayer* addMe, GameLayer* caller) {
    // Find where the caller is located
    std::vector<GameLayer*>::iterator location = mLayers.end();
    for(std::vector<GameLayer*>::iterator iter = mLayers.begin(); iter != mLayers.end(); ++ iter) {
        GameLayer* layer = *iter;
        
        if(layer == caller) {
            location = iter;
            break;
        }
    }
    
    // The caller is valid
    assert(location != mLayers.end());
    
    // Insert the new game layer into the next location ("One layer above")
    ++ location;
    mLayers.insert(location, addMe); // Inserting here is safe
    addMe->onBegin(mPotatoCake);
    
    // Inform all layers "below" this one that a new layer was added above them (this should logically include the caller)
    for(std::vector<GameLayer*>::iterator iter = mLayers.begin(); iter != mLayers.end(); ++ iter) {
        GameLayer* layer = *iter;
        
        if(layer == addMe) {
            break;
        }
        else {
            layer->onAddedAbove(addMe);
        }
    }
}
void GameLayerMachine::remove(GameLayer* removeMe) {
    // Find the layer to remove
    std::vector<GameLayer*>::iterator location = mLayers.end();
    for(std::vector<GameLayer*>::iterator iter = mLayers.begin(); iter != mLayers.end(); ++ iter) {
        GameLayer* layer = *iter;
        
        if(layer == removeMe) {
            location = iter;
            break;
        }
    }
    
    // This layer was found
    assert(location != mLayers.end());
    
    // Inform layer that it is going to be removed
    removeMe->onEnd();
    
    // Inform all layers "below" this one that a layer above them was removed
    for(std::vector<GameLayer*>::iterator iter = mLayers.begin(); iter != location; ++ iter) {
        GameLayer* layer = *iter;
        
        layer->onRemovedAbove(removeMe);
    }
    
    // Remove layer
    mLayers.erase(location);
}
void GameLayerMachine::removeAll() {
    std::vector<GameLayer*>::reverse_iterator iter = mLayers.rbegin();
    while(iter != mLayers.rend()) {
        GameLayer* layer = *iter;
        this->remove(layer);
        ++ iter;
    }
}

// Ticks
void GameLayerMachine::onTick(float tps, const Uint8* keys) {
    bool allKeysFiltered = false;
    for(int i = 0; i < sNumKeyStates; ++ i) {
        mFilteredKeyStates[i] = keys[i];
    }
    std::vector<GameLayer*>::reverse_iterator iter = mLayers.rbegin();
    while(iter != mLayers.rend()) {
        GameLayer* layer = *iter;
        
        if(allKeysFiltered) {
            layer->onTick(tps, sRelaxedKeyStates);
            
            ++ iter;
        }
        else {
            layer->onTick(tps, mFilteredKeyStates);
            
            // Only filter keys if there are layers below this one
            if(++ iter != mLayers.rend()) {
                if(layer->filterKeys(mFilteredKeyStates)) {
                    allKeysFiltered = true;
                }
            }
        }
    }
}

// Key handling
void GameLayerMachine::onKeyPress(const SDL_KeyboardEvent& event, bool repeat) {
    for(std::vector<GameLayer*>::reverse_iterator iter = mLayers.rbegin(); iter != mLayers.rend(); ++ iter) {
        GameLayer* layer = *iter;
        
        // Blocking
        if(layer->onKeyPress(event, repeat)) {
            break;
        }
    }
}
void GameLayerMachine::onKeyRelease(const SDL_KeyboardEvent& event) {
    for(std::vector<GameLayer*>::reverse_iterator iter = mLayers.rbegin(); iter != mLayers.rend(); ++ iter) {
        GameLayer* layer = *iter;
        
        // Blocking
        if(layer->onKeyRelease(event)) {
            break;
        }
    }
}
void GameLayerMachine::onTextInput(const SDL_TextInputEvent& event) {
    for(std::vector<GameLayer*>::reverse_iterator iter = mLayers.rbegin(); iter != mLayers.rend(); ++ iter) {
        GameLayer* layer = *iter;
        
        // Blocking
        if(layer->onTextInput(event)) {
            break;
        }
    }
}

// Mouse handling
void GameLayerMachine::onMouseMove(const SDL_MouseMotionEvent& event) {
    for(std::vector<GameLayer*>::reverse_iterator iter = mLayers.rbegin(); iter != mLayers.rend(); ++ iter) {
        GameLayer* layer = *iter;
        
        // Blocking
        if(layer->onMouseMove(event)) {
            break;
        }
    }
}
void GameLayerMachine::onMousePress(const SDL_MouseButtonEvent& event) {
    for(std::vector<GameLayer*>::reverse_iterator iter = mLayers.rbegin(); iter != mLayers.rend(); ++ iter) {
        GameLayer* layer = *iter;
        
        // Blocking
        if(layer->onMousePress(event)) {
            break;
        }
    }
}
void GameLayerMachine::onMouseRelease(const SDL_MouseButtonEvent& event) {
    for(std::vector<GameLayer*>::reverse_iterator iter = mLayers.rbegin(); iter != mLayers.rend(); ++ iter) {
        GameLayer* layer = *iter;
        
        // Blocking
        if(layer->onMouseRelease(event)) {
            break;
        }
    }
}
void GameLayerMachine::onMouseWheel(const SDL_MouseWheelEvent& event) {
    for(std::vector<GameLayer*>::reverse_iterator iter = mLayers.rbegin(); iter != mLayers.rend(); ++ iter) {
        GameLayer* layer = *iter;
        
        // Blocking
        if(layer->onMouseWheel(event)) {
            break;
        }
    }
}


const Uint8* GameLayerMachine::getRelaxedKeyStates() {
    return sRelaxedKeyStates;
}

}
