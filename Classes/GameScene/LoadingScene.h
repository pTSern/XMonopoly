#pragma once

#include "ZyUwU/ZyUwU.h"
#include "ui/CocosGUI.h"
#include "Support/GameConstant.h"
#include "SceneTransition.h"

USING_NS_ALL;

class LoadingScene : public Layer
{
public:
    static Scene* createScene(const std::string& targetScene);
    virtual bool init();
    ZY_CREATE_FUNC(LoadingScene);
    CREATE_SET_FUNC(setTargetScene, std::string, m_sTargetScene);
    void finishLoading();
    static LoadingScene* createWithTargetId(const std::string& targetScene);
    virtual void update(float dt);

protected:
    std::string m_sTargetScene;
};