#include "GameMaster.h"
#include "ChampionInGame/ChampionInGame.h"
#include "Player/Player.h"

GameMaster* GameMaster::sp_pInstance = nullptr;

//// Constructor

GameMaster::GameMaster() :
m_pIsTurnChampion(nullptr),
m_pMarkIsTurnChampion_UP(nullptr), m_pMarkIsTurnChampion_DOWN(nullptr),
m_nChampionIsTurnIndex(-1), m_nRound(0)
{

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

void GameMaster::log()
{

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
        this->m_pMarkIsTurnChampion_UP->setPosition(Point(m_pIsTurnChampion->getIcon()->getPosition().x, m_pIsTurnChampion->getIcon()->getContentPositionMiddleTop().y + m_pMarkIsTurnChampion_UP->getContentSize().height));
        this->m_pMarkIsTurnChampion_DOWN->setPosition(m_pIsTurnChampion->getIcon()->getContentPositionMiddleBottom());
    }
}

void GameMaster::update(float dt)
{
    this->markChampion();
    //if(m_pIsTurnChampion)
    //{
    //    if(m_pIsTurnChampion->getOwner()->isTrulyEndTurn() && !m_pIsTurnChampion->isTurn()) this->calculateNewTurn();
    //}
}

void GameMaster::calculateNewTurn()
{
    //std::sort(m_vList.begin(), m_vList.end(), ChampionInGame::sortChampion());
    int next_index = 0;
    if(m_nChampionIsTurnIndex + 1 <= m_vList.size() - 1)
    {
        next_index = m_nChampionIsTurnIndex + 1;
    }
    //zif(m_vList[next_index]->isValidTurn())
    {
        m_nRound ++;
        m_pIsTurnChampion = m_vList[next_index];
        m_nChampionIsTurnIndex = next_index;
        m_pIsTurnChampion->startTurn();
        CCLOG("INDEX %d", next_index);
    }
}

void GameMaster::addChampList(std::vector<ChampionInGame*> list)
{
    for(auto &x : list)
    {
        m_vList.push_back(x);
    }
}