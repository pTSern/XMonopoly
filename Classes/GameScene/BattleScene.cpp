#include "BattleScene.h"
#include "Map/Map.h"

#include "GameOver.h"
#include "MainMenu.h"

#include "Dice/Dice.h"
#include "Champion/Champion.h"
#include "ChampionInGame/ChampionInGame.h"
#include "Player/Player.h"
#include "ChampionInGame/AI/BotChampion.h"
#include "Player/Brain/AI/BotPlayer.h"
#include "ChampionInGame/UI/ChampionUI.h"
#include "ChampionInGame/UI/ChampionHUD.h"
#include "Arena/Arena.h"
#include "Skill/SkillManager/SkillManager.h"
#include "Skill/SkillInGame/SkillInGame.h"

#include "GameMaster/GameMaster.h"
#include "SceneTransition.h"

//// Static

static SceneRegister<BattleScene> s_register("BATTLE");

Scene* BattleScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    //auto scene = Scene::create();

    auto layer = BattleScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    GM_GI->setRunningScene(scene, layer,CC_CALLBACK_1(BattleScene::goToMenu, layer));
    return scene;
}

//// Virtual

bool BattleScene::init()
{
    if(!Layer::init()) return false;

    GM_GI->revoke();

    auto ttf = defaultTTFConfig;
    ttf.fontSize = 60;

    auto backgroundSprite = ZYSprite::create("background/battle.png");
    backgroundSprite->setPosition(ZYDR_TGVS/2);
    this->addChild(backgroundSprite, -5);

    this->setName("Battle Scene");

    auto visibleSize = ZYDR_GI->getVisibleSize();
    auto origin = ZYDR_GI->getVisibleOrigin();

    auto x = ZYSprite::create("skill_icon/skillcard2.png");
    x->setPosition(Point((visibleSize.width/2 + origin.x)/1, (x->getContentSize().height/3 + origin.y)/1));

    /// Input Map
    auto map = MapManager::create();
    GM_GI->setMap(map);
    map->loadTileMap("TileMaps/map-13.tmx");
    map->getTileMap()->setPosition(x->getPositionX(), (ZYDR_GI->getTrueVisibleSize().height + x->getContentPositionMiddleTop().y) /2);
    this->addChild(map, 0);
    map->generateArenas();

    p_pContactListener = EventListenerPhysicsContact::create();
    p_pContactListener->onContactBegin = CC_CALLBACK_1(BattleScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(p_pContactListener, this);

    /// Add schedule update
    this->scheduleUpdate();

    auto dice = Dice::createWithProperties("dice/128.png");
    auto champ = Champion::createWithProperties("champion/zed.png", Statics::createWithProperties(), ChampionStatics::create());
    auto ui = ChampionUI::createDefault();
    auto sig = SkillInGame::createTest();
    sig->setSkillMechanic(SkillInGame::MoveBySkill);
    auto heal = SkillInGame::createTest();
    heal->setSkillMechanic(SkillInGame::Healing);
    auto sm = SkillManager::createWithSkillInGame(sig, heal, nullptr);
    auto cig = ChampionInGame::createWithProperties(champ, ui, dice, sm);
    auto coord = Coordinate(Dir::WS, 0);
    //auto ig = IngameStatics::createTest();
    //cig->setStatics(ig);
    auto player = Player::create();
    player->setTheColor(Color4F::YELLOW);
    //MAP_MNG_GI->setClientPlayer(player);
    GM_GI->setClientPlayer(player);
    player->addChampion(cig);
    player->setName("PLAYER 1");
    m_vPlayers.push_back(player);
    cig->setPosition(coord);
    cig->getStatics()->setCurrentHp(50);
    cig->setName("CHAMP A");

    auto dice2 = Dice::createWithProperties("dice/128-red.png");
    auto champ2 = Champion::createWithProperties("champion/zed.png", Statics::createWithProperties(), ChampionStatics::create());
    auto ui2 = ChampionUI::createDefault();
    auto sig2 = SkillInGame::createTest();
    sig2->setSkillMechanic(SkillInGame::MoveBySkill);
    sig2->setName("move");
    auto sm2 = SkillManager::createWithSkillInGame(sig2, nullptr);
    auto cig2 = TesterBot::createWithProperties(champ2, ui2, dice2, sm2);
    //auto cig2 = ChampionInGame::createWithProperties(champ2, ui2, dice2, sm2);
    auto coord2 = Coordinate(Dir::WS, 0);
    auto player2 = BotPlayer::create();
    //auto player2 = Player::create();
    player2->addChampion(cig2);
    //player2->disable();
    m_vPlayers.push_back(player2);
    cig2->setPosition(coord2);
    cig2->setName("CHAMP B");

    for(auto z : m_vPlayers)
    {
        this->addChild(z, 1);
    }

    this->addChild(GM_GI, 1);
    GM_GI->addChampList(player->getChampChildren());
    GM_GI->addChampList(player2->getChampChildren());
    GM_GI->calculateNewTurn();

    //getEventDispatcher()->addEventListenerWithSceneGraphPriority(p_pContactListener, this);

    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("champion/samurai.png");
    //auto values = ValueMap();
    //for(int i = 0; i <= 28; i++)
    //{
    //    auto frameName = StringUtils::format("samurai_%02.png", i);
    //    auto frameRect = Rect(0,0, 168,168);

    //    ValueMap x;
    //    x["x"] = Value(frameRect.getMinX());
    //    x["y"] = Value(frameRect.getMinY());
    //    x["width"] = Value(frameRect.size.width);
    //    x["height"] = Value(frameRect.size.height);
    //    values[frameName] = x;
    //}

    //auto fileUtils = FileUtils::getInstance();
    //auto filePath = "champion/samurai.plist";
    return true;
}

//// Public

void BattleScene::update(float dt)
{
}

void BattleScene::goToGameOver(Ref* sender)
{
    auto scene = GameOverScene::createScene();
    CCDR_GI->replaceScene(scene);
}

void BattleScene::goToMenu(Ref* sender)
{
    auto scene = MainMenuScene::createScene();
    CCDR_GI->replaceScene(scene);
    //TransitionSceneFactory::getInstance()->transitionScene("MAIN_MENU");
}

bool BattleScene::onContactBegin(PhysicsContact& contact)
{
    auto pNodeA = contact.getShapeA()->getBody()->getNode();
    auto pNodeB = contact.getShapeB()->getBody()->getNode();
    auto pGameObjectA = dynamic_cast<GameObject*>(pNodeA);
    auto pGameObjectB = dynamic_cast<GameObject*>(pNodeB);
    if(pGameObjectA && pGameObjectB)
    {
        pGameObjectA->contactTo(contact, pGameObjectB);
        pGameObjectB->contactBy(contact, pGameObjectA);
    }
    return true;
}
