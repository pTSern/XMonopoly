#include "SpecialArena.h"

//// Factory Registry
//static ArenaTypeRegister<SpecialArena> s_register("special");

//// Constructor

SpecialArena::SpecialArena()
{

}

//// Public

//Static



//Virtual

bool SpecialArena::init()
{
    this->m_bIsBuyAble = true;

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

}

void SpecialArena::onLand(ChampionInGame* pChamp)
{

}

void SpecialArena::config()
{

}