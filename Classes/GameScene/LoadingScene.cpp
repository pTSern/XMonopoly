#include "LoadingScene.h"

///] Static

Scene* LoadingScene::createScene(const std::string& targetScene)
{
    auto scene = Scene::create();
    auto layer = LoadingScene::create();
    layer->setTargetScene(targetScene);
    scene->addChild(layer);
    return scene;
}

LoadingScene* LoadingScene::createWithTargetId(const std::string& targetScene)
{
    auto ret = new (std::nothrow) LoadingScene();
    if(ret && ret->init())
    {
        ret->setTargetScene(targetScene);
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

///] Virtual

bool LoadingScene::init()
{
    if (!Layer::init()) return false;

    auto visibleSize = ZYDR_TGVS;
    auto origin = ZYDR_GI->getVisibleOrigin();

    auto background = ZYSprite::create("ui/scene/background_loading.png");
    auto loadingBar = ui::LoadingBar::create("ui/scene/progress_loading.png");

    background->setPosition(Point(ZYDR_TGVS.width / 2, ZYDR_TGVS.height / 8));
    loadingBar->setPosition(background->getPosition());

    this->addChild(background);
    this->addChild(loadingBar, 1);

    return true;
}

void LoadingScene::finishLoading()
{
    //CCDR_GI->replaceScene(TransitionSceneFactory::getInstance()->create(m_sTargetScene));
    runAction(RemoveSelf::create(true));
}

void LoadingScene::update(float dt)
{

}