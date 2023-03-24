#include "MainMenu.h"
#include "BattleScene.h"
#include "ui/CocosGUI.h"
#include "Support/GameConstant.h"

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

    //auto backgroundSprite = Sprite::create("bg.png");
    //backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    //this->addChild(backgroundSprite, -1);

    //auto frame = cocos2d::Sprite::create(User::GetInstance()->GetUserUITexture()->g_sFrame);
    //frame->setPosition(Point(0 + frame->getContentSize().width / 2, visibleSize.height - frame->getContentSize().height / 2));
    //this->addChild(frame, 1);

    //auto avatar = cocos2d::Sprite::create(User::GetInstance()->GetUserUITexture()->g_sAvatar);
    //avatar->setPosition(frame->getPosition());
    //this->addChild(avatar, 0);

    //auto p_pUserName = cocos2d::Label::createWithTTF(User::GetInstance()->GetUserInformation()->g_sNickname, "fonts/arial.ttf", 20);
    //p_pUserName->setPosition(Point(frame->getPosition().x + frame->getContentSize().width / 1.8, visibleSize.height - 10));
    //this->addChild(p_pUserName, 1);


    //User::GetInstance()->log();
    return true;
}

void MainMenuScene::onEnter()
{
    Layer::onEnter();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto icon = MenuItemImage::create("ui/iconbar.png", "ui/iconbar.png");
    //icon->setPosition(Point(visibleSize.width - icon->getContentSize().width / 2, 0));
    //p_pIconList = Menu::create(icon, NULL);
    //p_pIconList->setPosition(Point::ZERO);

    //SoundManager::GetInstance()->PlayMainMenuSound();
    //this->addChild(p_pIconList);
}

void MainMenuScene::goToPvP(Ref* pSender)
{
    auto scene = BattleScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.0, scene));
}
