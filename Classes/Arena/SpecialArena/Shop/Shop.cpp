#include "Shop.h"

//// Factory Register

static SpecialArenaTypeRegister<ShopArena> s_register("SHOP");

//// Constructor

ShopArena::ShopArena()
{

}

//// Static

ShopArena* ShopArena::createWithProperties(const std::string& title, Coordinate& coord, Size rectSize, Point left)
{
    auto ret = new (std::nothrow) ShopArena();
    if(ret && ret->Arena::initWithProperties(title, coord, rectSize, left))
    {
        ret->autorelease();
        ret->config();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//// Virtual

bool ShopArena::init()
{
    return true;
}

void ShopArena::update(float dt)
{
    SpecialArena::update(dt);
}

void ShopArena::onLand(ChampionInGame* pChamp)
{
    SpecialArena::onLand(pChamp);
}

void ShopArena::config()
{
    SpecialArena::config();
    this->m_pTitle->setVisible(false);
}

void ShopArena::log()
{

}

std::string ShopArena::toString(int nTab)
{

}

