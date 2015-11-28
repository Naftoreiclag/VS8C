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

#include "CeguiFrames.hpp"

namespace vse {


CeguiFrames& CeguiFrames::getSingleton() {
    static CeguiFrames instance;
    return instance;
}

CeguiFrames::CeguiFrames() {
}

CeguiFrames::~CeguiFrames() {
}

CEGUI::Window* CeguiFrames::getConsoleWindow() { return mConsoleWindow; }
CEGUI::Window* CeguiFrames::getInventoryWindow() { return mInventoryWindow; }
CEGUI::Window* CeguiFrames::getPauseWindow() { return mPauseWindow; }

void CeguiFrames::loadAllLayouts(CEGUI::Window* ceguiWindow) {
    mCeguiWindow = ceguiWindow;
    
    mConsoleWindow = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("DeveloperConsole.layout");
    mCeguiWindow->addChild(mConsoleWindow);
    mConsoleWindow->setVisible(false);
    
    mInventoryWindow = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Inventory.layout");
    mCeguiWindow->addChild(mInventoryWindow);
    mInventoryWindow->setVisible(false);
        
    mPauseWindow = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("PauseMenu.layout");
    mCeguiWindow->addChild(mPauseWindow);
    mPauseWindow->setVisible(false);
}

}

