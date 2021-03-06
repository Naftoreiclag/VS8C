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

#include "CeguiUtil.hpp"

namespace vse {

namespace CeguiUtil {
    
CEGUI::Key::Scan toCeguiScancode(SDL_Scancode key) {
    switch(key) {
        case SDL_SCANCODE_0                      : return CEGUI::Key::Zero;
        case SDL_SCANCODE_1                      : return CEGUI::Key::One;
        case SDL_SCANCODE_2                      : return CEGUI::Key::Two;
        case SDL_SCANCODE_3                      : return CEGUI::Key::Three;
        case SDL_SCANCODE_4                      : return CEGUI::Key::Four;
        case SDL_SCANCODE_5                      : return CEGUI::Key::Five;
        case SDL_SCANCODE_6                      : return CEGUI::Key::Six;
        case SDL_SCANCODE_7                      : return CEGUI::Key::Seven;
        case SDL_SCANCODE_8                      : return CEGUI::Key::Eight;
        case SDL_SCANCODE_9                      : return CEGUI::Key::Nine;
        case SDL_SCANCODE_A                      : return CEGUI::Key::A;
        case SDL_SCANCODE_B                      : return CEGUI::Key::B;
        case SDL_SCANCODE_C                      : return CEGUI::Key::C;
        case SDL_SCANCODE_D                      : return CEGUI::Key::D;
        case SDL_SCANCODE_E                      : return CEGUI::Key::E;
        case SDL_SCANCODE_F                      : return CEGUI::Key::F;
        case SDL_SCANCODE_G                      : return CEGUI::Key::G;
        case SDL_SCANCODE_H                      : return CEGUI::Key::H;
        case SDL_SCANCODE_I                      : return CEGUI::Key::I;
        case SDL_SCANCODE_J                      : return CEGUI::Key::J;
        case SDL_SCANCODE_K                      : return CEGUI::Key::K;
        case SDL_SCANCODE_L                      : return CEGUI::Key::L;
        case SDL_SCANCODE_M                      : return CEGUI::Key::M;
        case SDL_SCANCODE_N                      : return CEGUI::Key::N;
        case SDL_SCANCODE_O                      : return CEGUI::Key::O;
        case SDL_SCANCODE_P                      : return CEGUI::Key::P;
        case SDL_SCANCODE_Q                      : return CEGUI::Key::Q;
        case SDL_SCANCODE_R                      : return CEGUI::Key::R;
        case SDL_SCANCODE_S                      : return CEGUI::Key::S;
        case SDL_SCANCODE_T                      : return CEGUI::Key::T;
        case SDL_SCANCODE_U                      : return CEGUI::Key::U;
        case SDL_SCANCODE_V                      : return CEGUI::Key::V;
        case SDL_SCANCODE_W                      : return CEGUI::Key::W;
        case SDL_SCANCODE_X                      : return CEGUI::Key::X;
        case SDL_SCANCODE_Y                      : return CEGUI::Key::Y;
        case SDL_SCANCODE_Z                      : return CEGUI::Key::Z;
        case SDL_SCANCODE_KP_0                   : return CEGUI::Key::Numpad0;
        case SDL_SCANCODE_KP_1                   : return CEGUI::Key::Numpad1;
        case SDL_SCANCODE_KP_2                   : return CEGUI::Key::Numpad2;
        case SDL_SCANCODE_KP_3                   : return CEGUI::Key::Numpad3;
        case SDL_SCANCODE_KP_4                   : return CEGUI::Key::Numpad4;
        case SDL_SCANCODE_KP_5                   : return CEGUI::Key::Numpad5;
        case SDL_SCANCODE_KP_6                   : return CEGUI::Key::Numpad6;
        case SDL_SCANCODE_KP_7                   : return CEGUI::Key::Numpad7;
        case SDL_SCANCODE_KP_8                   : return CEGUI::Key::Numpad8;
        case SDL_SCANCODE_KP_9                   : return CEGUI::Key::Numpad9;
        case SDL_SCANCODE_F1                     : return CEGUI::Key::F1;
        case SDL_SCANCODE_F2                     : return CEGUI::Key::F2;
        case SDL_SCANCODE_F3                     : return CEGUI::Key::F3;
        case SDL_SCANCODE_F4                     : return CEGUI::Key::F4;
        case SDL_SCANCODE_F5                     : return CEGUI::Key::F5;
        case SDL_SCANCODE_F6                     : return CEGUI::Key::F6;
        case SDL_SCANCODE_F7                     : return CEGUI::Key::F7;
        case SDL_SCANCODE_F8                     : return CEGUI::Key::F8;
        case SDL_SCANCODE_F9                     : return CEGUI::Key::F9;
        case SDL_SCANCODE_F10                    : return CEGUI::Key::F10;
        case SDL_SCANCODE_F11                    : return CEGUI::Key::F11;
        case SDL_SCANCODE_F12                    : return CEGUI::Key::F12;
        case SDL_SCANCODE_F13                    : return CEGUI::Key::F13;
        case SDL_SCANCODE_F14                    : return CEGUI::Key::F14;
        case SDL_SCANCODE_F15                    : return CEGUI::Key::F15;
        case SDL_SCANCODE_F16                    : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_F17                    : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_F18                    : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_F19                    : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_F20                    : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_F21                    : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_F22                    : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_F23                    : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_F24                    : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_AC_BACK                : return CEGUI::Key::WebBack;
        case SDL_SCANCODE_AC_BOOKMARKS           : return CEGUI::Key::WebFavorites;
        case SDL_SCANCODE_AC_FORWARD             : return CEGUI::Key::WebForward;
        case SDL_SCANCODE_AC_HOME                : return CEGUI::Key::WebHome;
        case SDL_SCANCODE_AC_REFRESH             : return CEGUI::Key::WebRefresh;
        case SDL_SCANCODE_AC_SEARCH              : return CEGUI::Key::WebSearch;
        case SDL_SCANCODE_AC_STOP                : return CEGUI::Key::WebStop;
        case SDL_SCANCODE_AGAIN                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_ALTERASE               : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_APOSTROPHE             : return CEGUI::Key::Apostrophe;
        case SDL_SCANCODE_APPLICATION            : return CEGUI::Key::AppMenu;
        case SDL_SCANCODE_AUDIOMUTE              : return CEGUI::Key::Mute;
        case SDL_SCANCODE_AUDIONEXT              : return CEGUI::Key::NextTrack;
        case SDL_SCANCODE_AUDIOPLAY              : return CEGUI::Key::PlayPause;
        case SDL_SCANCODE_AUDIOPREV              : return CEGUI::Key::PrevTrack;
        case SDL_SCANCODE_AUDIOSTOP              : return CEGUI::Key::MediaStop;
        case SDL_SCANCODE_BACKSLASH              : return CEGUI::Key::Backslash;
        case SDL_SCANCODE_BACKSPACE              : return CEGUI::Key::Backspace;
        case SDL_SCANCODE_BRIGHTNESSDOWN         : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_BRIGHTNESSUP           : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_CALCULATOR             : return CEGUI::Key::Calculator;
        case SDL_SCANCODE_CANCEL                 : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_CAPSLOCK               : return CEGUI::Key::Capital;
        case SDL_SCANCODE_CLEAR                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_CLEARAGAIN             : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_COMMA                  : return CEGUI::Key::Comma;
        case SDL_SCANCODE_COMPUTER               : return CEGUI::Key::MyComputer;
        case SDL_SCANCODE_COPY                   : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_CRSEL                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_CURRENCYSUBUNIT        : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_CURRENCYUNIT           : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_CUT                    : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_DECIMALSEPARATOR       : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_DELETE                 : return CEGUI::Key::Delete;
        case SDL_SCANCODE_DISPLAYSWITCH          : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_DOWN                   : return CEGUI::Key::ArrowDown;
        case SDL_SCANCODE_EJECT                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_END                    : return CEGUI::Key::End;
        case SDL_SCANCODE_EQUALS                 : return CEGUI::Key::Equals;
        case SDL_SCANCODE_ESCAPE                 : return CEGUI::Key::Escape;
        case SDL_SCANCODE_EXECUTE                : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_EXSEL                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_FIND                   : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_GRAVE                  : return CEGUI::Key::Grave;
        case SDL_SCANCODE_HELP                   : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_HOME                   : return CEGUI::Key::Home;
        case SDL_SCANCODE_INSERT                 : return CEGUI::Key::Insert;
        case SDL_SCANCODE_INTERNATIONAL1         : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_INTERNATIONAL2         : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_INTERNATIONAL3         : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_INTERNATIONAL4         : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_INTERNATIONAL5         : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_INTERNATIONAL6         : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_INTERNATIONAL7         : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_INTERNATIONAL8         : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_INTERNATIONAL9         : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KBDILLUMDOWN           : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KBDILLUMTOGGLE         : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KBDILLUMUP             : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_00                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_000                 : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_A                   : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_AMPERSAND           : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_AT                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_B                   : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_BACKSPACE           : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_BINARY              : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_C                   : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_CLEAR               : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_CLEARENTRY          : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_COLON               : return CEGUI::Key::Colon;
        case SDL_SCANCODE_KP_COMMA               : return CEGUI::Key::NumpadComma;
        case SDL_SCANCODE_KP_D                   : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_DBLAMPERSAND        : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_DBLVERTICALBAR      : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_DECIMAL             : return CEGUI::Key::Decimal;
        case SDL_SCANCODE_KP_DIVIDE              : return CEGUI::Key::Divide;
        case SDL_SCANCODE_KP_E                   : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_ENTER               : return CEGUI::Key::NumpadEnter;
        case SDL_SCANCODE_KP_EQUALS              : return CEGUI::Key::NumpadEquals;
        case SDL_SCANCODE_KP_EQUALSAS400         : return CEGUI::Key::NumpadEquals;
        case SDL_SCANCODE_KP_EXCLAM              : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_F                   : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_GREATER             : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_HASH                : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_HEXADECIMAL         : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_LEFTBRACE           : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_LEFTPAREN           : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_LESS                : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_MEMADD              : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_MEMCLEAR            : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_MEMDIVIDE           : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_MEMMULTIPLY         : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_MEMRECALL           : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_MEMSTORE            : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_MEMSUBTRACT         : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_MINUS               : return CEGUI::Key::Subtract;
        case SDL_SCANCODE_KP_MULTIPLY            : return CEGUI::Key::Multiply;
        case SDL_SCANCODE_KP_OCTAL               : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_PERCENT             : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_PERIOD              : return CEGUI::Key::Period;
        case SDL_SCANCODE_KP_PLUS                : return CEGUI::Key::Add;
        case SDL_SCANCODE_KP_PLUSMINUS           : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_POWER               : return CEGUI::Key::Power;
        case SDL_SCANCODE_KP_RIGHTBRACE          : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_RIGHTPAREN          : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_SPACE               : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_TAB                 : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_VERTICALBAR         : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_KP_XOR                 : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_LALT                   : return CEGUI::Key::LeftAlt;
        case SDL_SCANCODE_LANG1                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_LANG2                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_LANG3                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_LANG4                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_LANG5                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_LANG6                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_LANG7                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_LANG8                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_LANG9                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_LCTRL                  : return CEGUI::Key::LeftControl;
        case SDL_SCANCODE_LEFT                   : return CEGUI::Key::ArrowLeft;
        case SDL_SCANCODE_LEFTBRACKET            : return CEGUI::Key::LeftBracket;
        case SDL_SCANCODE_LGUI                   : return CEGUI::Key::LeftWindows;
        case SDL_SCANCODE_LSHIFT                 : return CEGUI::Key::LeftShift;
        case SDL_SCANCODE_MAIL                   : return CEGUI::Key::Mail;
        case SDL_SCANCODE_MEDIASELECT            : return CEGUI::Key::MediaSelect;
        case SDL_SCANCODE_MENU                   : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_MINUS                  : return CEGUI::Key::Minus;
        case SDL_SCANCODE_MODE                   : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_MUTE                   : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_NONUSBACKSLASH         : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_NONUSHASH              : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_NUMLOCKCLEAR           : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_OPER                   : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_OUT                    : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_PAGEDOWN               : return CEGUI::Key::PageDown;
        case SDL_SCANCODE_PAGEUP                 : return CEGUI::Key::PageUp;
        case SDL_SCANCODE_PASTE                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_PAUSE                  : return CEGUI::Key::Pause;
        case SDL_SCANCODE_PERIOD                 : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_POWER                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_PRINTSCREEN            : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_PRIOR                  : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_RALT                   : return CEGUI::Key::RightAlt;
        case SDL_SCANCODE_RCTRL                  : return CEGUI::Key::RightControl;
        case SDL_SCANCODE_RETURN                 : return CEGUI::Key::Return;
        case SDL_SCANCODE_RETURN2                : return CEGUI::Key::Return;
        case SDL_SCANCODE_RGUI                   : return CEGUI::Key::RightWindows;
        case SDL_SCANCODE_RIGHT                  : return CEGUI::Key::ArrowRight;
        case SDL_SCANCODE_RIGHTBRACKET           : return CEGUI::Key::RightBracket;
        case SDL_SCANCODE_RSHIFT                 : return CEGUI::Key::RightShift;
        case SDL_SCANCODE_SCROLLLOCK             : return CEGUI::Key::ScrollLock;
        case SDL_SCANCODE_SELECT                 : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_SEMICOLON              : return CEGUI::Key::Semicolon;
        case SDL_SCANCODE_SEPARATOR              : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_SLASH                  : return CEGUI::Key::Slash;
        case SDL_SCANCODE_SLEEP                  : return CEGUI::Key::Sleep;
        case SDL_SCANCODE_SPACE                  : return CEGUI::Key::Space;
        case SDL_SCANCODE_STOP                   : return CEGUI::Key::Stop;
        case SDL_SCANCODE_SYSREQ                 : return CEGUI::Key::SysRq;
        case SDL_SCANCODE_TAB                    : return CEGUI::Key::Tab;
        case SDL_SCANCODE_THOUSANDSSEPARATOR     : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_UNDO                   : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_UNKNOWN                : return CEGUI::Key::Unknown;
        case SDL_SCANCODE_UP                     : return CEGUI::Key::ArrowUp;
        case SDL_SCANCODE_VOLUMEDOWN             : return CEGUI::Key::VolumeDown;
        case SDL_SCANCODE_VOLUMEUP               : return CEGUI::Key::VolumeUp;
        case SDL_SCANCODE_WWW                    : return CEGUI::Key::Unknown;
        default                                  : return CEGUI::Key::Unknown;
    }
}

}

}
