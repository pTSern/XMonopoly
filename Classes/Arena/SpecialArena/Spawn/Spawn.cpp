#include "Spawn.h"

//// Register To Factory

static SpecialArenaTypeRegister<SpawnArena> s_register(special_arena_spawn_key);

//// Constructor

SpawnArena::SpawnArena()
{

}

//// Static

SpawnArena* SpawnArena::createWithProperties(const std::string& title, Coordinate& coord, Size& rectSize, Point left)
{
    auto ret = new (std::nothrow) SpawnArena();
    if(ret && ret->SpecialArena::initWithProperties(title, coord, rectSize, left))
    {
        ret->autorelease();
        ret->config();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

SpawnArena* SpawnArena::createFullPath(const std::string& title, Coordinate& coord, Size& rectSize, Point left, float bonus)
{
    auto ret = SpawnArena::createWithProperties(title, coord, rectSize, left);
    if(ret)
    {
        ret->setBonusMoney(bonus);
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
    SpecialArena::onLand(pChamp);
    auto target = pChamp->getOwner();
    target->finishAction();
}

void SpawnArena::onPass(ChampionInGame* pChamp)
{
    pChamp->getOwner()->receiveMoney(p_fBonusMoney);
}

void SpawnArena::config()
{
    SpecialArena::config();
    this->setName("SPAWN ARENA");
    this->m_pTitle->setVisible(false);
}

void SpawnArena::log()
{

    SpecialArena::log();
}

std::string SpawnArena::toString(int nTab)
{
    return SpecialArena::toString(nTab);
}
