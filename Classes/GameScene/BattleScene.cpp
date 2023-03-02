#include "BattleScene.h"
#include "Map/Map.h"

#include "Dice/Dice.h"
#include "Champion/Champion.h"
#include "ChampionInGame/ChampionInGame.h"
#include "Player/Player.h"
#include "ChampionInGame/UI/ChampionUI.h"

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
    auto champ = Champion::createWithProperties("champion/char-2.png", Statics::createWithProperties(), ChampionStatics::create());
    auto ui = ChampionUI::createDefault();
    std::vector<SkillInGame*> vec;
    auto cig = ChampionInGame::createWithProperties(champ, ui, dice, vec);
    cig->setPosition(ZYDR_GVS/1.5);
    auto ig = IngameStatics::create();
    ig->setStatics(Statics::createWithProperties(50, 50));
    cig->setStatics(ig);
    cig->config();
    auto player = Player::create();
    player->addChampion(cig);

    MAP_MNG_GI->setClientPlayer(player);
    m_vPlayers.push_back(player);

    for(auto x : m_vPlayers)
    {
        this->addChild(x, 1);
    }

    return true;
}

//// Public

void BattleScene::update(float dt)
{

}
