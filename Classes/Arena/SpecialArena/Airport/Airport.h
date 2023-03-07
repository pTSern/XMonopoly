#pragma once

#include "ZyUwU/ZyUwU.h"
#include "../SpecialArena.h"

USING_NS_ALL;

BEGIN_CREATE_REFCLASS(AirportArena, SpecialArena)

public:
    static AirportArena* createWithProperties(const std::string& title, Coordinate& coord, Size rectSize, Point left);

public:
    virtual void update(float dt);
    virtual void onLand(ChampionInGame *pChamp);
    virtual void config();

END_CREATE_REFCLASS
