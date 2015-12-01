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

#include "CeguiFrames.hpp"

namespace vse {

DeveloperConsole::DeveloperConsole() { }
DeveloperConsole::~DeveloperConsole() { }

void DeveloperConsole::onBegin(PotatoCake* potatoCake) {
    mConsoleWindow = CeguiFrames::getSingleton().getConsoleWindow();
    mSubmitButtonConnection = mConsoleWindow->getChild("Submit")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DeveloperConsole::onConsoleSubmitClicked, this));
    mEditBoxConnection = mConsoleWindow->getChild("Editbox")->subscribeEvent(CEGUI::Editbox::EventTextAccepted, CEGUI::Event::Subscriber(&DeveloperConsole::onConsoleEditboxTextAccepted, this));
    mCloseWindowConnection = mConsoleWindow->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&DeveloperConsole::onConsoleCloseClicked, this));
    this->deactivate();
}
void DeveloperConsole::onEnd() {
    mSubmitButtonConnection->disconnect();
    mEditBoxConnection->disconnect();
    mCloseWindowConnection->disconnect();
    this->deactivate();
}

void DeveloperConsole::onTick(float tps, const Uint8* keyStates) {
}
bool DeveloperConsole::filterKeys(Uint8* keyStates) {
    keyStates[SDL_GetScancodeFromKey(SDLK_BACKQUOTE)] = false;
    
    return false;
}
void DeveloperConsole::onAddedAbove(const GameLayer* layer) {
}
void DeveloperConsole::onRemovedAbove(const GameLayer* layer) {
}

void DeveloperConsole::activate() {
    mActive = true;
    mConsoleWindow->setVisible(true);
    CEGUI::Window* editbox = mConsoleWindow->getChild("Editbox");
    mConsoleWindow->moveToFront();
}

void DeveloperConsole::deactivate() {
    mActive = false;
    mConsoleWindow->setVisible(false);
}

bool DeveloperConsole::onKeyPress(const SDL_KeyboardEvent& event, bool repeat) {
    switch(event.keysym.sym) {
        case SDLK_BACKQUOTE: {
            this->activate();
            return true;
            break; // why
        }
        case SDLK_ESCAPE: {
            if(mActive) {
                this->deactivate();
                return true;
            }
            break;
        }
        default: {
            break;
        }
    }
    return false;
}

bool DeveloperConsole::onConsoleSubmitClicked(const CEGUI::EventArgs& args) {
    CEGUI::Window* editbox = mConsoleWindow->getChild("Editbox");
    CEGUI::String text = editbox->getText();
    onConsoleTextSubmitted(text);
    editbox->setText("");
}
bool DeveloperConsole::onConsoleEditboxTextAccepted(const CEGUI::EventArgs& args) {
    CEGUI::Window* editbox = mConsoleWindow->getChild("Editbox");
    CEGUI::String text = editbox->getText();
    onConsoleTextSubmitted(text);
    editbox->setText("");
}
bool DeveloperConsole::onConsoleTextSubmitted(const CEGUI::String& text) {
    this->outputConsoleText(">" + text);
    if(text == "save") {
        this->outputConsoleText("game saved");
    }
    else {
        this->outputConsoleText("unknown command", CEGUI::Colour(1.f, 0.f, 0.f));
    }
}
void DeveloperConsole::outputConsoleText(const CEGUI::String& text, CEGUI::Colour color) {
    CEGUI::Listbox* listbox = static_cast<CEGUI::Listbox*>(mConsoleWindow->getChild("History"));
    
    CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(text);
    item->setTextColours(color);
    listbox->addItem(item);
    listbox->ensureItemIsVisible(item);
}
bool DeveloperConsole::onConsoleCloseClicked(const CEGUI::EventArgs& args) {
    this->deactivate();
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

