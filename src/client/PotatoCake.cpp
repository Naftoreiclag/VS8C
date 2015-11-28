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

#include "PotatoCake.hpp"

#include "OgreRenderWindow.h"
#include "OgreConfigFile.h"
#include "OgreWindowEventUtilities.h"
#include "SDL.h"
#include "SFML/System.hpp"

#include "CeguiInjector.hpp"
#include "CeguiFrames.hpp"
#include "Overworld.hpp"
#include "StaticStrings.hpp"

namespace vse
{

PotatoCake& PotatoCake::getSingleton() {
    static PotatoCake instance;
    return instance;
}
    
PotatoCake::PotatoCake() {
}

PotatoCake::~PotatoCake() {
}

void PotatoCake::run() {
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
    CeguiFrames::getSingleton().loadAllLayouts(mCeguiWindow);
    
    mGameLayerMachine = new GameLayerMachine(mOgreRoot, mOgreWindow, mSdlWindow, mCeguiRenderer, mCeguiWindow);
    
    mGameLayerMachine->addBottom(new CeguiInjector());
    mGameLayerMachine->addBottom(new Overworld());
    
    sf::Clock tpsTimer;
    
    bool appRunning = true;
    while(appRunning) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT: {
                    mGameLayerMachine->removeAll();
                    mOgreRoot->queueEndRendering();
                    appRunning = false;
                    break;
                }
                case SDL_TEXTINPUT: {
                    mGameLayerMachine->onTextInput(event.text);
                    break;
                }
                case SDL_KEYDOWN: {
                    mGameLayerMachine->onKeyPress(event.key, event.key.repeat);
                    break;
                }
                case SDL_KEYUP: {
                    mGameLayerMachine->onKeyRelease(event.key);
                    break;
                }
                case SDL_MOUSEMOTION: {
                    mGameLayerMachine->onMouseMove(event.motion);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    mGameLayerMachine->onMousePress(event.button);
                    break;
                }
                case SDL_MOUSEBUTTONUP: {
                    mGameLayerMachine->onMouseRelease(event.button);
                    break;
                }
                case SDL_MOUSEWHEEL: {
                    mGameLayerMachine->onMouseWheel(event.wheel);
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
            mGameLayerMachine->onTick(tps);
            
            if(!mOgreRoot->renderOneFrame()) {
                appRunning = false;
            }
        }
        
        Ogre::WindowEventUtilities::messagePump();
    }
}


}

