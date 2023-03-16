#include "Shop.h"

//// Factory Register

static SpecialArenaTypeRegister<ShopArena> s_register(special_arena_shop_key);

//// Constructor

ShopArena::ShopArena()
{

}

//// Static

ShopArena* ShopArena::createWithProperties(const std::string& title, Coordinate& coord, Size rectSize, Point left)
{
    auto ret = new (std::nothrow) ShopArena();
    if(ret && ret->SpecialArena::initWithProperties(title, coord, rectSize, left))
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
    this->setName("SHOP ARENA");
    this->m_pTitle->setVisible(false);
}

void ShopArena::log()
{

    SpecialArena::log();
}

std::string ShopArena::toString(int nTab)
{
    return SpecialArena::toString(nTab);
}

