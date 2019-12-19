
#pragma once

#include "RuntimeProtocol.h"

class RuntimeCCSImpl : public RuntimeProtocol
{
public:
    static RuntimeCCSImpl *create();
    
    void onStartDebuger(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse);
    void onReload(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse);
    void startScript(const std::string& file);
    
private:
    void loadCSDProject(const std::string& file);
    void loadCSBProject(const std::string& file);
};
