#pragma once

#include "../Arena.h"

USING_NS_ALL;

BEGIN_CREATE_REFCLASS(SpecialArena, Arena)

public:
    static SpecialArena* createWithProperties();

public:
    virtual void update(float dt);
    virtual void onLand(ChampionInGame *pChamp);
    virtual void config();

END_CREATE_REFCLASS