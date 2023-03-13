#include "Tax.h"

//// Factory Register

static SpecialArenaTypeRegister<TaxArena> s_register("TAX");

//// Static

TaxArena* TaxArena::createWithProperties(const std::string& title, Coordinate& coord, Size rectSize, Point left)
{
    auto ret = new (std::nothrow) TaxArena();
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

TaxArena::TaxArena()
{

}

//// Virtual

bool TaxArena::init()
{
    return true;
}

void TaxArena::update(float dt)
{
    SpecialArena::update(dt);
}

void TaxArena::onLand(ChampionInGame* pChamp)
{
    SpecialArena::onLand(pChamp);
}

void TaxArena::config()
{
    SpecialArena::config();
    int x = 1;
    if ((int)m_Coord.g_eDir < 0) x = -1;

    m_pTitle->setRotationSkewX(x*MAP_MNG_GI->getAngleVertical());
    m_pTitle->setRotationSkewY(x*MAP_MNG_GI->getAngleHorizon());
}

void TaxArena::log()
{

}

std::string TaxArena::toString(int nTab)
{

}