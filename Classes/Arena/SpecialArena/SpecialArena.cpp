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
    this->scheduleUpdate();
}

void SpecialArena::onLand(ChampionInGame* pChamp)
{

}

void SpecialArena::onPass(ChampionInGame* pChamp)
{

}
