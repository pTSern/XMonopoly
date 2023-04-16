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

#include "Skill/Mechanic/MechanicManager.h"
#include "Skill/Mechanic/Mechanic.h"

#include "Audio/SoundManager.h"

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
    SM_GI->playMainMenuSound();

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

    auto statics = Statics::createWithProperties(25, 10, 30, 1, 3, 30, 0, 0, RegenStatics(100, 10), RegenStatics(30, 5), RegenStatics(1, 1));
    auto dice2 = Dice::createWithProperties("dice/128-red.png");
    auto champ2 = Champion::createWithProperties("champion/samurai.png", statics, ChampionStatics::create());
    auto ui2 = ChampionUI::createDefault();
    auto sig2 = SkillInGame::createTest();
    sig2->getSkillStatics()->setPhysicDmg(35);
    sig2->getSkillCard()->setDescriptionLabel("Moving forward with the number equal to the dice num. Deal 35 dmg to every target on landed arena.");

    //sig2->setSkillMechanic(SkillInGame::MoveBySkill);
    sig2->setName("move");
    auto sm2 = SkillManager::createWithSkillInGame(sig2, nullptr);
    auto cig2 = TesterBot::createWithProperties(champ2, ui2, dice2, sm2);

    auto skill_mechanic = Moving::create();
    auto mechanic_manager = MechanicManager::create(sig2, skill_mechanic);

    //auto cig2 = ChampionInGame::createWithProperties(champ2, ui2, dice2, sm2);
    auto coord2 = Coordinate(Dir::WS, 0);
    auto player2 = BotPlayer::create();
    //auto player2 = Player::create();
    player2->addChampion(cig2);
    //player2->disable();
    cig2->setPosition(coord2);
    cig2->setName("CHAMP B");

    auto dice = Dice::createWithProperties("dice/128.png");
    auto statics2 = Statics::createWithProperties(20, 20, 20, 1, 1, 30, 0, 0, RegenStatics(150, 10), RegenStatics(50, 5), RegenStatics(1, 1));
    auto champ = Champion::createWithProperties("champion/duelist.png", statics2, ChampionStatics::create());
    auto ui = ChampionUI::createDefault();

    ///v Skill
    auto sig = SkillInGame::createTest();
    sig->getSkillStatics()->setPhysicDmg(20);
    sig->getSkillCard()->setDescriptionLabel("Moving forward with the number equal to the dice num. Deal 20 dmg to every target on landed arena.");
    auto heal = SkillInGame::createNoDice();
    heal->getSkillCard()->setNameLabel("HEAL");
    heal->getSkillStatics()->setCoolDown(12);
    heal->getSkillStatics()->setManaCost(50);
    heal->getSkillCard()->setDescriptionLabel("Self healing 100 HP.");
    heal->setName("heal");

    auto arrow = SkillInGame::createNoDice();
    arrow->getSkillStatics()->setCoolDown(7);
    arrow->getSkillStatics()->setPhysicDmg(10);
    arrow->getSkillStatics()->setManaCost(20);
    arrow->getSkillCard()->setDescriptionLabel("Shoot 3 arrows forward with the distance is 12. Disappear after hitting target");
    arrow->getSkillCard()->setNameLabel("ARROW");
    auto arrow_m = ShootProjectile::create(4, "projectile/arrow.png", 12, 0.5);
    auto mechanic_manager34= MechanicManager::create(arrow, arrow_m);

    auto sm = SkillManager::createWithSkillInGame(sig, heal, arrow, nullptr);
    auto cig = ChampionInGame::createWithProperties(champ, ui, dice, sm);

    auto skill_mechanic2 = Moving::create();
    auto mechanic_manager2 = MechanicManager::create(sig, skill_mechanic2);

    auto skill_mechanic3 = FooCallback::create();
    skill_mechanic3->setOnTriggerCallback(FooCallback::HealingOnTrigger);
    skill_mechanic3->setEndTriggerCallback(FooCallback::ForceEndTurn);
    auto mechanic_manager3 = MechanicManager::create(heal, skill_mechanic3);


    //heal->setSkillMechanic(SkillInGame::Healing);
    auto coord = Coordinate(Dir::WS, 0);
    //auto ig = IngameStatics::createTest();
    //cig->setStatics(ig);
    auto player = Player::create();
    player->setTheColor(Color4F::YELLOW);
    //MAP_MNG_GI->setClientPlayer(player);
    GM_GI->setClientPlayer(player);
    player->addChampion(cig);
    player->setName("PLAYER 1");
    cig->setPosition(coord);
    cig->setName("CHAMP A");

    cig->getStatics()->log();
    cig2->getStatics()->log();
    m_vPlayers.push_back(player2);
    m_vPlayers.push_back(player);

    for(auto z : m_vPlayers)
    {
        this->addChild(z, 1);
    }

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
    GM_GI->update(dt);
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
    if(CCDR_GI->isPaused()) CCDR_GI->resume();
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
