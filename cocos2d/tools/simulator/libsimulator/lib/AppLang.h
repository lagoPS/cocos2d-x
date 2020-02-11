//
//  AppLang.h
//  Simulator
//

#pragma once

#include "cocos2d.h"
#include <map>

#include "json/rapidjson.h"
#include "json/document.h"
#include "DeviceEx.h"
#include "SimulatorExport.h"

class CC_LIBSIM_DLL AppLang
{
public:
    static AppLang* getInstance();

    std::string getString(const std::string &lang, const std::string& key);

protected:
    AppLang();
    void readLocalizationFile();

    bool _hasInit;
    std::string _localizationFileName;
    rapidjson::Document _docRootjson;
};

#define tr(key) AppLang::getInstance()->getString(player::DeviceEx::getInstance()->getCurrentUILangName(), key)