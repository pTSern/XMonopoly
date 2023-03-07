#include "Airport.h"

//// Factory Register

static SpecialArenaTypeRegister<AirportArena> s_register("AIRPORT");

//// Static

AirportArena* AirportArena::createWithProperties(const std::string& title, Coordinate& coord, Size rectSize, Point left)
{
    auto ret = new (std::nothrow) AirportArena();
    if(ret && ret->Arena::initWithProperties(title, coord, rectSize, left))
    {
        ret->autorelease();
        ret->config();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//// Constructor

AirportArena::AirportArena()
{

}

//// Virtual

bool AirportArena::init()
{
    return true;
}

void AirportArena::update(float dt)
{
    SpecialArena::update(dt);
}

void AirportArena::onLand(ChampionInGame* pChamp)
{

}

void AirportArena::config()
{
    SpecialArena::config();
    this->m_pTitle->setVisible(false);
}

void AirportArena::log()
{

}

std::string AirportArena::toString(int nTab)
{

}