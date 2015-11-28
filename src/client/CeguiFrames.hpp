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

#ifndef VSE_CEGUIFRAMES_HPP
#define VSE_CEGUIFRAMES_HPP

#include "CEGUI/CEGUI.h"

namespace vse {

class CeguiFrames {
private:
    CEGUI::Window* mCeguiWindow;
    
    CEGUI::Window* mConsoleWindow;
    CEGUI::Window* mInventoryWindow;
    CEGUI::Window* mPauseWindow;
    
public:
    static CeguiFrames& getSingleton();
    
    CeguiFrames();
    ~CeguiFrames();
    
    void loadAllLayouts(CEGUI::Window* ceguiWindow);
    
    CEGUI::Window* getConsoleWindow();
    CEGUI::Window* getInventoryWindow();
    CEGUI::Window* getPauseWindow();
};

}

#endif // VSE_CEGUIFRAMES_HPP
