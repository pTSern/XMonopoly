#pragma once

#include "ZyUwU/ZyUwU.h"
#include "../SpecialArena.h"

USING_NS_ALL;

BEGIN_CREATE_REFCLASS(SpawnArena, SpecialArena)

public:
    static SpawnArena* createWithProperties(const std::string& title, Coordinate& coord, Size rectSize, Point left);

public:
    virtual void update(float dt);
    virtual void onLand(ChampionInGame *pChamp);
    virtual void onPass(ChampionInGame *pChamp);
    virtual void config();

    CREATE_SET_FUNC(setBonusMoney, float, p_fBonusMoney);

private:
    float p_fBonusMoney;

END_CREATE_REFCLASS