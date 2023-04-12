#include "MainMenu.h"
#include "BattleScene.h"
#include "ui/CocosGUI.h"
#include "Support/GameConstant.h"
#include "SceneTransition.h"

#include "Audio/SoundManager.h"

static SceneRegister<MainMenuScene> s_register("MAIN_MENU");

Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();

    auto layer = MainMenuScene::create();
    scene->setName("MAIN MENU");
    scene->addChild(layer);

    return scene;
}

bool MainMenuScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    SM_GI->playMainMenuSound();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto pvp = MenuItemImage::create(sr_button_default, sr_button_clicked, CC_CALLBACK_1(MainMenuScene::goToPvP, this));
    pvp->setPosition(ZYDR_TGVS/2);

    auto menu = Menu::create(pvp, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    auto config = defaultTTFConfig;
    config.fontSize = pvp->getContentSize().height/2;
    config.bold = true;
    auto label = ZYLabel::createWithTTF(config, "PLAY", TextHAlignment::CENTER, ZYDR_TGVS.width/2);
    label->setColor(Color3B::BLACK);
    label->setPosition(ZYDR_TGVS/2);
    this->addChild(label, 2);

    auto backgroundSprite = ZYSprite::create("background/main_menu.png");
    backgroundSprite->setPosition(ZYDR_TGVS/2);
    this->addChild(backgroundSprite, -1);

    return true;
}

void MainMenuScene::goToPvP(Ref* pSender)
{
    auto scene = BattleScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.0, scene));
    //TransitionSceneFactory::getInstance()->transitionScene("BATTLE");
}
