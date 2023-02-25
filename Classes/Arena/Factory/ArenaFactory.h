#pragma once

#include "map"
#include "string"
#include "functional"

class Arena;
class ArenaFactory
{
public:
    static ArenaFactory* getInstance()
    {
        return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new (std::nothrow) ArenaFactory();
    }

    bool registerType(const std::string& sTypeId, std::function<Arena*()> pCreator);
    Arena* create(const std::string& sTypeId);
private:
    static ArenaFactory* sp_pInstance;
    std::map<std::string, std::function<Arena*()>> p_mCreators;
};

template<class Type>
class ArenaTypeRegister
{
public:
    ArenaTypeRegister(std::string sClassName)
    {
        ArenaFactory::getInstance()->registerType(sClassName, []()->Arena* {return Type::create();});
    }
};