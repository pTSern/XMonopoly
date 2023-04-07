#include "GameMaster.h"
#include "ChampionInGame/ChampionInGame.h"
#include "Player/Player.h"
#include "Player/UI/PlayerUI.h"
#include "Map/Map.h"

#include "Statics/Statics.h"
//#include "Skill/SkillStatics/SkillStatics.h"

GameMaster* GameMaster::sp_pInstance = nullptr;

//// Constructor

GameMaster::GameMaster() :
m_pIsTurnChampion(nullptr),
m_pMarkIsTurnChampion_UP(nullptr), m_pMarkIsTurnChampion_DOWN(nullptr),
m_nChampionIsTurnIndex(-1), m_nRound(0),
m_pRunningScene(nullptr), m_pBattleLayer(nullptr),
m_pClient(nullptr), m_pMap(nullptr), p_bLockEndGame(false),
m_pClientUI(nullptr), p_nBitmask(0)
{

}

void GameMaster::revoke()
{
    //CC_SAFE_RELEASE_NULL(m_pMarkIsTurnChampion_UP);
    //CC_SAFE_RELEASE_NULL(m_pMarkIsTurnChampion_DOWN);
    m_pIsTurnChampion = nullptr;
    m_pClientUI = nullptr;

    for(auto &child: m_vList)
    {
        child = nullptr;
    }
    m_vList.clear();

    m_pRunningScene = nullptr;
    m_pBattleLayer = nullptr;
    p_bLockEndGame = false;
    p_nBitmask = 0;

    CC_SAFE_RELEASE_NULL(m_pMap);
    this->scheduleUpdate();
}

//// Public

bool GameMaster::init()
{
    m_pMarkIsTurnChampion_UP = ZYSprite::create("champion/up.png");
    m_pMarkIsTurnChampion_DOWN = ZYSprite::create("champion/down.png");

    this->addChild(m_pMarkIsTurnChampion_UP);
    this->addChild(m_pMarkIsTurnChampion_DOWN);
    this->scheduleUpdate();
    return true;
}
void GameMaster::generateMap(const std::string& tileMap)
{
    m_pMap = MapManager::create();
    m_pMap->loadTileMap(tileMap);
    m_pMap->setPosition(Point(ZYDR_TGVS.width/2, (ZYDR_TGVS.height + m_pMap->getContentSize().height/2)/2));
    addChild(m_pMap);
    m_pMap->generateArenas();
}

int GameMaster::getBitMask()
{
    p_nBitmask ++;
    return p_nBitmask;
}

void GameMaster::setClientPlayer(Player* target)
{
    if(target)
    {
        //m_pClientUI = PlayerUI::createClientUI();
        target->setIsClient(true);
        //target->addChild(m_pClientUI, 5);
        m_pClient = target;
    }
}

void GameMaster::log()
{

}

void GameMaster::setRunningScene(Scene* var, Layer* layer,ui::Widget::ccWidgetTouchCallback callback)
{
    this->m_pRunningScene = var;
    this->m_pEndGameCallback = callback;
    this->m_pBattleLayer = layer;
}

std::string GameMaster::toString(int nTab)
{
    std::string ts;
    return ts;
}

void GameMaster::setIsTurnChampion(ChampionInGame* champion)
{
    this->m_pIsTurnChampion = champion;
}

void GameMaster::markChampion()
{
    if(m_pIsTurnChampion)
    {
        this->m_pMarkIsTurnChampion_UP->setPosition(Point(m_pIsTurnChampion->getIcon()->getPosition().x, m_pIsTurnChampion->getIcon()->getContentPositionMiddleTop().y + 2*m_pMarkIsTurnChampion_UP->getContentSize().height/3));
        this->m_pMarkIsTurnChampion_DOWN->setPosition(m_pIsTurnChampion->getIcon()->getContentPositionMiddleBottom());
        auto color = m_pIsTurnChampion->getOwner()->getTheColor();
        auto color3b = ZYSP_3BT4F(m_pIsTurnChampion->getOwner()->getTheColor());
        this->m_pMarkIsTurnChampion_UP->setColor(color3b);
        this->m_pMarkIsTurnChampion_DOWN->setColor(color3b);
    }
}

void GameMaster::update(float dt)
{
    this->markChampion();
}

void GameMaster::calculateNewTurn()
{
    //std::sort(m_vList.begin(), m_vList.end(), ChampionInGame::SortChampion());
    CCLOG("CALL CALCULATE NEW TURN");
    int next_index = 0;
    if(m_nChampionIsTurnIndex + 1 <= m_vList.size() - 1)
    {
        next_index = m_nChampionIsTurnIndex + 1;
    }
    //if(m_vList[next_index]->isValidTurn())
    {
        m_nRound ++;
        m_pIsTurnChampion = m_vList[next_index];
        m_nChampionIsTurnIndex = next_index;
        CCLOG("INDEX: %d", m_nChampionIsTurnIndex);
        m_pIsTurnChampion->startTurn();
    }
}

void GameMaster::addChampList(std::vector<ChampionInGame*> list)
{
    for(auto &x : list)
    {
        m_vList.push_back(x);
    }
}

void GameMaster::endGame(bool bIsClient)
{
    if(!p_bLockEndGame)
    {
        auto ttf = defaultTTFConfig;
        ttf.fontSize = 50;
        ttf.bold = true;
        auto color = Color3B::BLUE;
        std::string str= "YOU WIN";
        if(bIsClient)
        {
            color = Color3B::RED;
            str = "YOU LOSE";
        }
        floatingNotify(str, ttf, color, ZYDR_TGVS/2, 2, true);
        m_pBattleLayer->getEventDispatcher()->removeAllEventListeners();

        auto button = ui::Button::create(sr_button_default, sr_button_clicked);
        button->setTitleText("CONTINUE");
        CCUB_SSTFSP(button, 0.8);
        button->addTouchEventListener(m_pEndGameCallback);
        button->setPosition(Point(ZYDR_TGVS.width/2, ZYDR_TGVS.height/4));
        m_pBattleLayer->addChild(button);
        button->setGlobalZOrder(7);
        p_bLockEndGame = true;
    }
}

void GameMaster::floatingNotify(const std::string& message, const TTFConfig& ttf, const Color3B& color, const Point& position, const float& duration, bool isLock)
{
    if(m_pBattleLayer)
    {
        auto dim = LayerColor::create(Color4B::BLACK);
        m_pBattleLayer->addChild(dim);
        dim->setGlobalZOrder(5);
        dim->setOpacity(dim->getOpacity()/2);
        auto label = ZYLabel::createWithTTF(ttf, message, TextHAlignment::CENTER, ZYDR_TGVS.width/4*3);
        m_pBattleLayer->addChild(label);
        label->setGlobalZOrder(6);
        label->setColor(color);
        label->setPosition(position);
        if(!isLock)
        {
            label->setScale(0);
            auto scaleTo = ScaleTo::create(0.75f, 1.0f);
            auto delay = DelayTime::create(duration);
            auto fade = FadeOut::create(0.25f);
            auto remove = RemoveSelf::create();
            auto sequence = Sequence::create(scaleTo, delay, fade, remove, nullptr);
            label->runAction(sequence);
            auto seq = Sequence::create(DelayTime::create(duration + 1.5f), remove->clone(), nullptr);
            dim->runAction(seq);
        }
    }
}

void GameMaster::floatingNotify(const std::string& message)
{
    auto ttf = defaultTTFConfig;
    ttf.fontSize = 50;
    floatingNotify(message, ttf, Color3B::BLACK, ZYDR_TGVS/2);
}

float GameMaster::magicDmgCalculator(Statics* defender, SkillStatics* attacker, Point pos)
{
    float mr = defender->getMagicResistance() - attacker->getMagicPieInNum();
    float mrToDc = Fraction::fastPercent(MRFB - (MRFF * mr)/(MRFB + MRFF * abs(mr)));
    // Total magic resistance in decimal (0.xxx)
    float totalMrInDc = mrToDc * (1 - attacker->getTheMagicPiercing().getPcAmount());
    // Run gacha if this crit

    bool isCrit = critStar(pos, attacker->getMagicCritRate());
    // Run crit

    // Total magic damage
    float totalMd = (isCrit*attacker->getMagicCritDmgMul() + 1) * attacker->getMagicDmg();
    float causeDmg = (1 - totalMrInDc) * totalMd;

    return causeDmg;
}

float GameMaster::physicDmgCalculator(Statics* defender, SkillStatics* attacker, Point pos)
{
    float ar = defender->getArmor() - attacker->getPhysicPieInNum();
    float arToDc = Fraction::fastPercent(PRFB - (PRFF * ar)/(PRFB + PRFF * abs(ar)));
    // Total armor resistance in decimal (0.xxx)
    float totalArInDc = arToDc * (1 - attacker->getThePhysicPiercing().getPcAmount());
    // Run gacha if this crit

    bool isCrit = critStar(pos, attacker->getPhysicCritRate());
    // Run crit

    // Total magic damage
    float totalMd = (isCrit*attacker->getPhysicCritDmgMul() + 1) * attacker->getPhysicDmg();
    float causeDmg = (1 - totalArInDc) * totalMd;

    return causeDmg;
}

float GameMaster::totalDmgCalculator(Statics* defender, SkillStatics* attacker, Point pos)
{
    return magicDmgCalculator(defender, attacker, pos) + physicDmgCalculator(defender, attacker, pos);
}

void GameMaster::attackScene(ChampionInGame* attacker, ChampionInGame* defender)
{
    auto dim = LayerColor::create(Color4B::BLACK);
    m_pBattleLayer->addChild(dim);
    dim->setGlobalZOrder(5);
    dim->setOpacity(dim->getOpacity()/2);

    auto atk = attacker->getIcon()->clone();
    m_pBattleLayer->addChild(atk, 10);
    atk->setPosition(Point(ZYDR_TGVS.width/4*3, ZYDR_TGVS.height/2));
    auto def = defender->getIcon()->clone();
    m_pBattleLayer->addChild(def, 10);
    def->setPosition(Point(ZYDR_TGVS.width/4, ZYDR_TGVS.height/2));
    auto delay = DelayTime::create(2.0f);
    auto x = def->getPosition();
    auto rm = RemoveSelf::create(true);
    auto mt = MoveTo::create(0.5f, Point( x.x + atk->getContentSize().width/2,x.y));
    auto sq = Sequence::create(delay, rm, nullptr);
    auto seq = Sequence::create(mt, rm->clone(), nullptr);
    atk->runAction(seq);
    def->runAction(sq);
    dim->runAction(sq->clone());
}

bool GameMaster::critStar(Point pos, float chance)
{
    if(ZYGC_GI->runGacha(chance))
    {
        this->critStar(pos);
        return true;
    }
    return false;
}

void GameMaster::critStar(Point pos)
{

}