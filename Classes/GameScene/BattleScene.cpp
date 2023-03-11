#include "BattleScene.h"
#include "Map/Map.h"

#include "Dice/Dice.h"
#include "Champion/Champion.h"
#include "ChampionInGame/ChampionInGame.h"
#include "Player/Player.h"
#include "ChampionInGame/UI/ChampionUI.h"
#include "Arena/Arena.h"
#include "Skill/SkillManager/SkillManager.h"
#include "Skill/SkillInGame/SkillInGame.h"
#include "Skill/SkillInGame/MoveBy/SkillMoveBy.h"

#include "GameMaster/GameMaster.h"

//// Static

Scene* BattleScene::createScene()
{
    auto scene = Scene::create();

    auto layer = BattleScene::create();
    scene->addChild(layer);
    return scene;
}

//// Virtual

bool BattleScene::init()
{
    if(!Layer::init()) return false;

    this->setName("Battle Scene");

    auto visibleSize = ZYDR_GI->getVisibleSize();
    auto origin = ZYDR_GI->getVisibleOrigin();

    auto x = ZYSprite::create("skill_icon/skillcard2.png");
    x->setPosition(Point((visibleSize.width/2 + origin.x)/1, (x->getContentSize().height/3 + origin.y)/1));

    /// Input Map
    MAP_MNG_GI->loadTileMap("TileMaps/map-13.tmx");
    MAP_MNG_GI->getTileMap()->setPosition(x->getPositionX(), (ZYDR_GI->getTrueVisibleSize().height + x->getContentPositionMiddleTop().y) /2);
    this->addChild(MAP_MNG_GI, 0);

    MAP_MNG_GI->generateArenas();

    /// Add schedule update
    this->scheduleUpdate();

    auto dice = Dice::createWithProperties("dice/128.png");
    auto champ = Champion::createWithProperties("champion/char-3.png", Statics::createWithProperties(), ChampionStatics::create());
    auto ui = ChampionUI::createDefault();
    auto sig = SkillInGame::createTest();
    sig->setSkillMechanic(SkillInGame::MoveBySkill);
    auto sm = SkillManager::createWithSkillInGame(sig, SkillInGame::createTest(),nullptr);
    auto cig = ChampionInGame::createWithProperties(champ, ui, dice, sm);
    auto coord = Coordinate(Dir::WS, 0);
    cig->setPosition(coord);
    auto ig = IngameStatics::create();
    ig->setStatics(Statics::createWithProperties(50, 50));
    cig->setStatics(ig);
    auto player = Player::create();
    player->setTheColor(Color4F::YELLOW);
    player->addChampion(cig);
    player->disable();
    MAP_MNG_GI->setClientPlayer(player);
    m_vPlayers.push_back(player);

    auto dice2 = Dice::createWithProperties("dice/128.png");
    auto champ2 = Champion::createWithProperties("champion/char-3.png", Statics::createWithProperties(), ChampionStatics::create());
    auto ui2 = ChampionUI::createDefault();
    auto sig2 = SkillInGame::createTest();
    sig2->setSkillMechanic(SkillInGame::MoveBySkill);
    auto sm2 = SkillManager::createWithSkillInGame(sig2, SkillInGame::createTest(),nullptr);
    auto cig2 = ChampionInGame::createWithProperties(champ2, ui2, dice2, sm2);
    auto coord2 = Coordinate(Dir::WS, 0);
    cig2->setPosition(coord2);
    auto ig2 = IngameStatics::create();
    ig2->setStatics(Statics::createWithProperties(50, 50));
    cig2->setStatics(ig2);
    auto player2 = Player::create();
    player2->setTheColor(Color4F::RED);
    player2->addChampion(cig2);
    player2->disable();
    m_vPlayers.push_back(player2);

    for(auto x : m_vPlayers)
    {
        this->addChild(x, 1);
    }

    this->addChild(GM_GI, 1);
    GM_GI->addChampList(player->getChampChildren());
    GM_GI->addChampList(player2->getChampChildren());
    GM_GI->calculateNewTurn();

    return true;
}

//// Public

void BattleScene::update(float dt)
{
}
