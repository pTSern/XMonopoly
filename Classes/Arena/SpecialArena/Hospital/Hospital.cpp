#include "Hospital.h"

//// Factory Register

static SpecialArenaTypeRegister<HospitalArena> s_register("HOSPITAL");

//// Static

HospitalArena* HospitalArena::createWithProperties(const std::string& title, Coordinate& coord, Size rectSize, Point left)
{
    auto ret = new (std::nothrow) HospitalArena();
    if(ret && ret->SpecialArena::initWithProperties(title, coord, rectSize, left))
    {
        ret->autorelease();
        ret->config();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//// Constructor

HospitalArena::HospitalArena()
{

}

//// Virtual

bool HospitalArena::init()
{
    return true;
}

void HospitalArena::update(float dt)
{
    SpecialArena::update(dt);
}

void HospitalArena::onLand(ChampionInGame* pChamp)
{
    SpecialArena::onLand(pChamp);
}

void HospitalArena::config()
{
    SpecialArena::config();
    this->setName("TAX ARENA");
    int x = 1;
    if ((int)m_Coord.g_eDir < 0) x = -1;

    m_pTitle->setRotationSkewX(x*MAP_MNG_GI->getAngleVertical());
    m_pTitle->setRotationSkewY(x*MAP_MNG_GI->getAngleHorizon());
}

void HospitalArena::log()
{
    SpecialArena::log();
}

std::string HospitalArena::toString(int nTab)
{
    return SpecialArena::toString(nTab);
}
