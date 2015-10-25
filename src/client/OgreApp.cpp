#include "OgreApp.hpp"

#include "OgreRenderWindow.h"
#include "OgreConfigFile.h"
#include "OgreWindowEventUtilities.h"
#include "SDL.h"
#include "SFML/System.hpp"

#include "VseApp.hpp"

namespace vse
{

OgreApp& OgreApp::getSingleton() {
    static OgreApp instance;
    return instance;
}
    
OgreApp::OgreApp() {
}

OgreApp::~OgreApp() {
}

void OgreApp::run() {
    mOgreRoot = new Ogre::Root("plugins.cfg");
    
    if(mOgreRoot->restoreConfig() || mOgreRoot->showConfigDialog()) {
        mOgreRoot->initialise(false);

        mSdlWindow = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_RESIZABLE);

        SDL_SysWMinfo sdlWindowInfo;
        SDL_VERSION(&sdlWindowInfo.version);
        SDL_GetWindowWMInfo(mSdlWindow, &sdlWindowInfo);
        
        Ogre::NameValuePairList ogreParams;
        ogreParams["FSAA"] = "4";
        
        #if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        ogreParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(sdlWindowInfo.info.win.window));
        #elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
        ogreParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(sdlWindowInfo.info.cocoa.window));
        #elif OGRE_PLATFORM == OGRE_PLATFORM_LINUX
        ogreParams["parentWindowHandle"] = Ogre::StringConverter::toString(size_t(sdlWindowInfo.info.x11.window));
        #endif
        mOgreWindow = mOgreRoot->createRenderWindow("secret message for uubor haxurs", 1280, 720, false, &ogreParams);
    }
    else {
        return;
    }
    
    {
        Ogre::ConfigFile resCfg;
        resCfg.load("resources.cfg");
        Ogre::ConfigFile::SectionIterator sectionIterator = resCfg.getSectionIterator();
        
        while(sectionIterator.hasMoreElements()) {
            Ogre::String sectionName = sectionIterator.peekNextKey();
            Ogre::ConfigFile::SettingsMultiMap* sectionData = sectionIterator.getNext();
            Ogre::ConfigFile::SettingsMultiMap::iterator dataIterator;
            for(dataIterator = sectionData->begin(); dataIterator != sectionData->end(); ++ dataIterator) {
                Ogre::ResourceGroupManager::getSingleton().addResourceLocation(dataIterator->second, dataIterator->first, sectionName);
            }
        }
    }
    
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    
    VseApp& garnetApp = VseApp::getSingleton();
    garnetApp.initialize(mOgreRoot, mOgreWindow, mSdlWindow);
    
    sf::Clock tpsTimer;
    
    bool running = true;
    while(running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT: {
                    garnetApp.onClose();
                    mOgreRoot->queueEndRendering();
                    running = false;
                    break;
                }
                case SDL_KEYDOWN: {
                    // Do not listen to when the key is being rapid-fire pressed
                    if(!event.key.repeat) {
                        garnetApp.onKeyPress(event.key);
                    }
                    break;
                }
                case SDL_KEYUP: {
                    garnetApp.onKeyRelease(event.key);
                    break;
                }
                case SDL_MOUSEMOTION: {
                    garnetApp.onMouseMove(event.motion);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    garnetApp.onMousePress(event.button);
                    break;
                }
                case SDL_MOUSEBUTTONUP: {
                    garnetApp.onMouseRelease(event.button);
                    break;
                }
                default : {
                    break;
                }
            }
        }
        
        float tps = tpsTimer.getElapsedTime().asSeconds();
        tpsTimer.restart();
        garnetApp.onTick(tps);
        
        Ogre::WindowEventUtilities::messagePump();
        
        if(!mOgreRoot->renderOneFrame()) {
            break;
        }
    }
}


}

