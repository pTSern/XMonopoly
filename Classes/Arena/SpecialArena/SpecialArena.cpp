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

bool SpecialArena::initWithProperties(const std::string& sTitle, Coordinate &coord, Size& rectSize, Point& left)
{
    return Arena::initWithProperties(sTitle, coord, rectSize, left);
};
void SpecialArena::log()
{
    Arena::log();
}

std::string SpecialArena::toString(int nTab)
{
    return Arena::toString(nTab);
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
}

void SpecialArena::onPass(ChampionInGame* pChamp)
{
}
