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

#ifndef VSE_DEVELOPERCONSOLE_HPP
#define VSE_DEVELOPERCONSOLE_HPP

#include "GameLayer.hpp"

namespace vse {

class DeveloperConsole : public GameLayer {
public:
    DeveloperConsole();
    ~DeveloperConsole();

private:
    bool mActive;
    void activate();
    void deactivate();

public:
    PotatoCake* mPotatoCake;    
    CEGUI::Window* mConsoleWindow;
    
    CEGUI::Event::Connection mSubmitButtonConnection;
    CEGUI::Event::Connection mEditBoxConnection;
    CEGUI::Event::Connection mCloseWindowConnection;
    
    // Lifecycle
    void onBegin(PotatoCake* potatoCake);
    void onEnd();
    
    // Layering
    bool filterKeys(Uint8* keyStates);
    
    // Key handling
    bool onKeyPress(const SDL_KeyboardEvent& event, bool repeat);

    bool onConsoleSubmitClicked(const CEGUI::EventArgs& args);
    bool onConsoleEditboxTextAccepted(const CEGUI::EventArgs& args);
    bool onConsoleTextSubmitted(const CEGUI::String& text);
    bool onConsoleCloseClicked(const CEGUI::EventArgs& args);
    void outputConsoleText(const CEGUI::String& text, CEGUI::Colour color = CEGUI::Colour(1.f, 1.f, 1.f));
};

}

#endif // VSE_DEVELOPERCONSOLE_HPP
