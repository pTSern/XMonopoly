#include "Player.h"
#include "Arena/Arena.h"
#include "Support/GameConstant.h"
#include "Arena/Property/Property.h"

//// Constructor

Player::Player() :
m_pEconomy(Economy::IngameCoin)
{

}

//// Virtual

bool Player::init()
{
    if(!Layer::init()) return false;

    // Init Event Listener
    m_pEventListener = EventListenerTouchOneByOne::create();
    m_pEventListener->onTouchBegan = CC_CALLBACK_2(Player::onTouch, this);
    m_pEventListener->onTouchEnded = CC_CALLBACK_2(Player::endTouch, this);

    return true;
}

std::string Player::toString(int nTab)
{
    std::string ts;
    return ts;
}

void Player::log()
{

}

void Player::update(float dt)
{

}

//// Public

bool Player::onTouch(Touch *touch, Event *event)
{
    return true;
}
bool Player::endTouch(Touch *touch, Event *event)
{
    return true;
}

void Player::setControlChampion(ChampionInGame *pChampion)
{

}

void Player::setChampionViewPoint(ChampionInGame *pChampion)
{

}

void Player::loadSkillDeck()
{

}

bool Player::buyingProperty(Player *pOwner)
{
    if(!pOwner)
    {
        return true;
    }
    return true;
}

bool Player::yesOrNoSelector(std::string sMessage)
{
    return true;
}

void Player::onLandArena(Arena* arena)
{
    if((Property*)arena)
    {
        auto pro = (Property*)arena;
        this->pay(pro->getOwner(), pro->getTax());
    }
}

void Player::pay(Player* player, float money)
{
}

void Player::addChampion(ChampionInGame* pChamp)
{
    if(pChamp)
    {
        m_vChampions.push_back(pChamp);
        m_vChampions.back()->setOwner(this, true);
        this->addChild(pChamp);
    }
}

