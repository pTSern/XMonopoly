#include "Spawn.h"

//// Register To Factory

static SpecialArenaTypeRegister<SpawnArena> s_register("SPAWN");

//// Constructor

SpawnArena::SpawnArena()
{

}

//// Static

SpawnArena* SpawnArena::createWithProperties(const std::string& title, Coordinate& coord, Size rectSize, Point left)
{
    auto ret = new (std::nothrow) SpawnArena();
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

bool SpawnArena::init()
{
    return true;
}

void SpawnArena::update(float dt)
{
    SpecialArena::update(dt);
}

void SpawnArena::onLand(ChampionInGame* pChamp)
{
}

void SpawnArena::onPass(ChampionInGame* pChamp)
{
    pChamp->getOwner()->receiveMoney(p_fBonusMoney);
}

void SpawnArena::config()
{
    SpecialArena::config();
    this->m_pTitle->setVisible(false);
}

void SpawnArena::log()
{

}

std::string SpawnArena::toString(int nTab)
{

}
