#include "SceneTransition.h"
#include "LoadingScene.h"

TransitionSceneFactory* TransitionSceneFactory::sp_pInstance = nullptr;

bool TransitionSceneFactory::registerType(const std::string& sTypeId, std::function<Layer*()> pCreator)
{
    auto it = p_mCreators.find(sTypeId);
    if(it != p_mCreators.end())
    {
        return false;
    }
    p_mCreators[sTypeId] = pCreator;
    return true;
}

Layer* TransitionSceneFactory::create(const std::string &typeId)
{
    auto it = p_mCreators.find(typeId);
    if(it == p_mCreators.end())
    {
        return nullptr;
    }
    return it->second();
}

void TransitionSceneFactory::transitionScene(const std::string& targetScene)
{
    auto scene = Scene::createWithPhysics();
    auto loading = LoadingScene::createWithTargetId(targetScene);
    scene->addChild(loading, 1);
    auto layer= this->create(targetScene);
    scene->addChild(layer);
    CCDR_GI->replaceScene(scene);
}
