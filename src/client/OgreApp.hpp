#ifndef GRT_OGREAPP_HPP
#define GRT_OGREAPP_HPP

#include "CEGUI/CEGUI.h"
#include "CEGUI/RendererModules/Ogre/Renderer.h"
#include "OgreRoot.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreRenderWindow.h"
#include "SDL_syswm.h"

namespace vse {

class OgreApp {
public:
    OgreApp();
    virtual ~OgreApp();
public:
    static OgreApp& getSingleton();
    void run();
public:
    Ogre::Root* mOgreRoot;
    Ogre::RenderWindow* mOgreWindow;
    SDL_Window* mSdlWindow;
    CEGUI::OgreRenderer* mCeguiRenderer;

};

}

#endif // GRT_OGREAPP_HPP
