#include "SpecialArena.h"


//// Constructor

SpecialArena::SpecialArena()
{

}

//// Public

//Static



//Virtual

bool SpecialArena::init()
{
    return true;
}

void SpecialArena::log()
{

}

std::string SpecialArena::toString(int nTab)
{
    std::string ts;
    return ts;
}

void SpecialArena::update(float dt)
{
    Arena::update(dt);
}

void SpecialArena::config()
{
    Arena::config();

    m_bIsBuyAble = false;
    this->m_pTitle->setPosition(m_Left.getMidpoint(m_Right));

    this->m_eType = Type::SPECIAL;
    this->scheduleUpdate();
}

void SpecialArena::onLand(ChampionInGame* pChamp)
{
    Arena::onLand(pChamp);

    pChamp->getOwner()->onLandSpecialArena(this);
}

void SpecialArena::onPass(ChampionInGame* pChamp)
{

}
