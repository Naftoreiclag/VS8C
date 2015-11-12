#include "OgreApp.hpp"

#include "OgreRenderWindow.h"
#include "OgreConfigFile.h"
#include "OgreWindowEventUtilities.h"
#include "SDL.h"
#include "SFML/System.hpp"

#include "StaticStrings.hpp"
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

        std::string& windowTitle = StaticStrings::getSingleton().windowTitle;
        mSdlWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_RESIZABLE);

        SDL_SysWMinfo sdlWindowInfo;
        SDL_VERSION(&sdlWindowInfo.version);
        SDL_GetWindowWMInfo(mSdlWindow, &sdlWindowInfo);
        
        Ogre::NameValuePairList ogreParams;
        ogreParams["FSAA"] = "0";
        
        #if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        ogreParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(sdlWindowInfo.info.win.window));
        #elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
        ogreParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(sdlWindowInfo.info.cocoa.window));
        #elif OGRE_PLATFORM == OGRE_PLATFORM_LINUX
        ogreParams["parentWindowHandle"] = Ogre::StringConverter::toString(size_t(sdlWindowInfo.info.x11.window));
        #endif
        mOgreWindow = mOgreRoot->createRenderWindow(StaticStrings::getSingleton().renderTargetName, 1280, 720, false, &ogreParams);
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
    
    Ogre::RenderTarget* renderTarget = mOgreRoot->getRenderTarget(StaticStrings::getSingleton().renderTargetName);
    mCeguiRenderer = &CEGUI::OgreRenderer::bootstrapSystem(*renderTarget);
    
    CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    
    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
    //CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-10");
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
    
    mCeguiWindow = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", StaticStrings::getSingleton().ceguiRootName);
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mCeguiWindow);
    
    VseApp& garnetApp = VseApp::getSingleton();
    garnetApp.onAppBegin(mOgreRoot, mOgreWindow, mSdlWindow, mCeguiRenderer, mCeguiWindow);
    
    sf::Clock tpsTimer;
    
    bool appRunning = true;
    while(appRunning) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT: {
                    garnetApp.onAppEnd();
                    mOgreRoot->queueEndRendering();
                    appRunning = false;
                    break;
                }
                case SDL_KEYDOWN: {
                    garnetApp.onKeyPress(event.key, event.key.repeat);
                    break;
                }
                case SDL_KEYUP: {
                    garnetApp.onKeyRelease(event.key);
                    break;
                }
                case SDL_TEXTINPUT: {
                    garnetApp.onTextInput(event.text);
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
                case SDL_MOUSEWHEEL: {
                    garnetApp.onMouseWheel(event.wheel);
                    break;
                }
                default : {
                    break;
                }
            }
        }
        
        // It is possible that an event triggered the loop to end
        if(appRunning) {
            float tps = tpsTimer.getElapsedTime().asSeconds();
            tpsTimer.restart();
            garnetApp.onTick(tps);
            
            if(!mOgreRoot->renderOneFrame()) {
                appRunning = false;
            }
        }
        
        Ogre::WindowEventUtilities::messagePump();
        
    }
}


}

