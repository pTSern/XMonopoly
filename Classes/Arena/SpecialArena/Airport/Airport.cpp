#include "Airport.h"

//// Factory Register

static SpecialArenaTypeRegister<AirportArena> s_register(special_arena_airport_key);

//// Static

AirportArena* AirportArena::createWithProperties(const std::string& title, Coordinate& coord, Size& rectSize, Point& left)
{
    auto ret = new (std::nothrow) AirportArena();
    if(ret && ret->SpecialArena::initWithProperties(title, coord, rectSize, left))
    {
        ret->autorelease();
        ret->config();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

AirportArena* AirportArena::createFullPath(const std::string& title, Coordinate& coord, Size& rectSize, Point& left, float& price)
{
    auto ret = AirportArena::createWithProperties(title, coord, rectSize, left);
    if(ret)
    {
        ret->setPricePerArena(price);
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
    SpecialArena::onLand(pChamp);
}

void AirportArena::config()
{
    SpecialArena::config();
    this->setName("AIRPORT ARENA");
    this->m_pTitle->setVisible(false);
}

void AirportArena::log()
{
    SpecialArena::log();
}

std::string AirportArena::toString(int nTab)
{
    return SpecialArena::toString(nTab);
}