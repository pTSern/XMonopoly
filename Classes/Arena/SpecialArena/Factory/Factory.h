#pragma once

#include "map"
#include "string"
#include "functional"

#include "../SpecialArena.h"

class SpecialArena;
class SpecialArenaFactory
{
public:
    static SpecialArenaFactory* getInstance()
    {
        return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new (std::nothrow) SpecialArenaFactory();
    }

    bool registerType(const std::string& sTypeId, std::function<SpecialArena*(const std::string& sTitle, Coordinate &coord, Size rectSize, Point left)> pCreator);
    SpecialArena* create(const std::string& sTypeId, const std::string& sTitle, Coordinate &coord, Size rectSize, Point left);
private:
    static SpecialArenaFactory* sp_pInstance;
    std::map<std::string, std::function<SpecialArena*(const std::string& sTitle, Coordinate &coord, Size rectSize, Point left)>> p_mCreators;
};

template<class Type>
class SpecialArenaTypeRegister
{
public:
    SpecialArenaTypeRegister(std::string sClassName)
    {
        SpecialArenaFactory::getInstance()->registerType(sClassName, [](const std::string& sTitle, Coordinate &coord, Size rectSize, Point left)->SpecialArena* {CCLOG("VUA"); return Type::createWithProperties(sTitle, coord, rectSize, left);});
    }
};
