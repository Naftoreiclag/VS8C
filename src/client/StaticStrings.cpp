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

#include "StaticStrings.hpp"

#include <fstream>

#include "json/json.h"

namespace vse
{

StaticStrings::StaticStrings() {
    Json::Value jsonRoot;
    std::ifstream file("internal.json");
    Json::Reader reader;
    bool success = reader.parse(file, jsonRoot, false);
    file.close();
    
    if(success) {
        Json::Value& jsonCeguiRootName = jsonRoot["ceguiRootName"];
        Json::Value& jsonRenderTargetName = jsonRoot["renderTargetName"];
        Json::Value& jsonWindowTitle = jsonRoot["windowTitle"];
        
        if(jsonCeguiRootName.isString()) {
            ceguiRootName = jsonCeguiRootName.asString();
        }
        else {
            ceguiRootName = "CeguiRootWindow";
        }
        
        if(jsonRenderTargetName.isString()) {
            renderTargetName = jsonRenderTargetName.asString();
        }
        else {
            renderTargetName = "OgreRenderTarget";
        }
        
        if(jsonWindowTitle.isString()) {
            windowTitle = jsonWindowTitle.asString();
        }
        else {
            windowTitle = "Application";
        }
    }
}

StaticStrings::~StaticStrings()
{
}

StaticStrings& StaticStrings::getSingleton() {
    static StaticStrings instance;
    return instance;
}

}

