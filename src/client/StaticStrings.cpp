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

