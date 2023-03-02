#include "TargetTypeFactory.h"

TargetTypeFactory* TargetTypeFactory::sp_pInstance = nullptr;

bool TargetTypeFactory::registerType(const std::string& typeId, std::function<TargetType*()> creator)
{
    auto it = p_mCreator.find(typeId);

    if(it != p_mCreator.end())
    {
        return false;
    }
    p_mCreator[typeId] = creator;
    return true;
}

TargetType* TargetTypeFactory::create(const std::string& typeId )
{

    auto it = p_mCreator.find(typeId);

    if(it != p_mCreator.end())
    {
        return nullptr;
    }

    return it->second();
}
