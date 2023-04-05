#pragma once

#include "ZyUwU/ZyUwU.h"

USING_NS_ALL;

class TransitionSceneFactory
{
public:
    static TransitionSceneFactory* getInstance()
    {
        return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new (std::nothrow) TransitionSceneFactory();
    }

    bool registerType(const std::string& sTypeId, std::function<Layer*()> pCreator);
    Layer* create(const std::string &typeId);
    void transitionScene(const std::string& targetScene);
private:
    static TransitionSceneFactory* sp_pInstance;
    std::map<std::string, std::function<Layer*()>> p_mCreators;
};

template<class Type>
class SceneRegister
{
public:
    SceneRegister(std::string sClassName)
    {
        TransitionSceneFactory::getInstance()->registerType(sClassName, []()->Type* {return Type::create();});
    }
};
