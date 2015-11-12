#ifndef VSE_CEGUIUTIL_HPP
#define VSE_CEGUIUTIL_HPP

#include "CEGUI/CEGUI.h"
#include "SDL_syswm.h"

namespace vse {

namespace CeguiUtil {
    CEGUI::Key::Scan toCeguiScancode(SDL_Scancode key);
}

}

#endif // VSE_CEGUIUTIL_HPP
