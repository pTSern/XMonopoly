#include "ArenaFactory.h"

ArenaFactory* ArenaFactory::sp_pInstance = nullptr;

bool ArenaFactory::registerType(const std::string& sTypeId, std::function<Arena*()> pCreator)
{
    auto it = p_mCreators.find(sTypeId);

    if(it != p_mCreators.end())
    {
        return false;
    }
    p_mCreators[sTypeId] = pCreator;
    return true;
}

Arena* ArenaFactory::create(const std::string &sTypeId)
{
    auto it = p_mCreators.find(sTypeId);

    if(it != p_mCreators.end())
    {
        return nullptr;
    }

    return it->second();
}