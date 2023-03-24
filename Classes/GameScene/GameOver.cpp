#include "GameOver.h"
#include "Support/GameConstant.h"
#include "MainMenu.h"
#include "Map/Map.h"
#include "GameMaster/GameMaster.h"

Scene* GameOverScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameOverScene::init()
{
    if(!Layer::init()) return false;
    auto bg = ZYSprite::create("background/game_over.png");
    this->addChild(bg, -1);
    bg->setPosition(ZYDR_TGVS/2);
    auto config = defaultTTFConfig;
    config.fontSize = 60;
    config.bold = true;
    auto label = ZYLabel::createWithTTF(config, "END GAME", TextHAlignment::CENTER, ZYDR_TGVS.width/2);
    label->setColor(Color3B::RED);
    label->setPosition(ZYDR_TGVS/2);
    label->setGlobalZOrder(7);
    this->addChild(label);

    auto button = MenuItemImage::create(sr_button_default, sr_button_clicked, CC_CALLBACK_1(GameOverScene::goToMainMenu, this));
    button->setPosition(Point(ZYDR_TGVS.width/2, label->getContentPositionMiddleBottom().y - button->getContentSize().height));
    this->addChild(button);
    button->setGlobalZOrder(8);

    config.fontSize = button->getContentSize().height/2;
    auto bl = ZYLabel::createWithTTF(config, "CONTINUE", TextHAlignment::CENTER);
    bl->setPosition(button->getPosition());
    this->addChild(bl, 1);

    auto menu = Menu::create(button, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    return true;
}

void GameOverScene::goToMainMenu(Ref* sender)
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.0, scene));
    //GM_GI->selfDestroyInstance();
    //MAP_MNG_GI->selfDestroyInstance();
}
