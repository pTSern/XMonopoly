#include "Factory.h"

SpecialArenaFactory* SpecialArenaFactory::sp_pInstance = nullptr;

bool SpecialArenaFactory::registerType(const std::string& sTypeId, std::function<SpecialArena*(const std::string& sTitle, Coordinate &coord, Size rectSize, Point left)> pCreator)
{
    auto it = p_mCreators.find(sTypeId);

    if(it != p_mCreators.end())
    {
        return false;
    }
    p_mCreators[sTypeId] = pCreator;
    return true;
}

SpecialArena* SpecialArenaFactory::create(const std::string &sTypeId, const std::string& sTitle, Coordinate &coord, Size rectSize, Point left)
{
    auto it = p_mCreators.find(sTypeId);

    if(it == p_mCreators.end())
    {
        return nullptr;
    }

    return it->second(sTitle, coord, rectSize, left);
}
