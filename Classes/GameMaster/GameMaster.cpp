#include "GameMaster.h"
#include "ChampionInGame/ChampionInGame.h"
#include "Player/Player.h"

GameMaster* GameMaster::sp_pInstance = nullptr;

//// Constructor

GameMaster::GameMaster() :
m_pIsTurnChampion(nullptr),
m_pMarkIsTurnChampion_UP(nullptr), m_pMarkIsTurnChampion_DOWN(nullptr),
m_nChampionIsTurnIndex(-1), m_nRound(0),
m_pRunningScene(nullptr), m_pBattleLayer(nullptr),
m_pClient(nullptr), m_pMap(nullptr), p_bLockEndGame(false)
{

}

void GameMaster::revoke()
{
    //CC_SAFE_RELEASE_NULL(m_pMarkIsTurnChampion_UP);
    //CC_SAFE_RELEASE_NULL(m_pMarkIsTurnChampion_DOWN);
    m_pIsTurnChampion = nullptr;

    for(auto &child: m_vList)
    {
        child = nullptr;
    }
    m_vList.clear();

    m_pRunningScene = nullptr;
    m_pBattleLayer = nullptr;
    p_bLockEndGame = false;

    m_pMap = nullptr;
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

void GameMaster::setClientPlayer(Player* target)
{
    if(target)
    {
        target->setIsClient(true);
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
    std::sort(m_vList.begin(), m_vList.end(), ChampionInGame::SortChampion());
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
        if(!bIsClient)
        {
            color = Color3B::RED;
            str = "YOU LOSE";
        }
        floatingNotify(str, ttf, color, ZYDR_TGVS/2, 2, true);

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
    auto dim = LayerColor::create(Color4B::BLACK);
    m_pBattleLayer->addChild(dim);
    dim->setGlobalZOrder(5);
    dim->setOpacity(dim->getOpacity()/2);
    auto label = ZYLabel::createWithTTF(ttf, message);
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

