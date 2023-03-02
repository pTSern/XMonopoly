#pragma once

#include "map"
#include "string"
#include "functional"
#include "../TargetType.h"

class TargetTypeFactory
{
public:
    static TargetTypeFactory* getInstance()
    {
        return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new (std::nothrow) TargetTypeFactory();
    }
    bool registerType(const std::string& typeId, std::function<TargetType*()> creator);
    TargetType* create(const std::string& typeId);

private:
    static TargetTypeFactory* sp_pInstance;
    std::map<std::string, std::function<TargetType*()>> p_mCreator;
};

template<class T>
class TargetTypeRegister
{
public:
    TargetTypeRegister(std::string sClassName)
    {
        TargetTypeFactory::getInstance()->registerType(sClassName, []()->TargetType* {return T::create();});
    }
};