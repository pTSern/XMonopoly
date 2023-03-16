#pragma once

#include "../Arena.h"
#include "Factory/Factory.h"

USING_NS_ALL;

BEGIN_CREATE_REFCLASS(SpecialArena, Arena)

public:

public:
    virtual void update(float dt);
    virtual void onLand(ChampionInGame *pChamp);
    virtual void onPass(ChampionInGame *pChamp) override;
    virtual void config();
    virtual bool initWithProperties(const std::string& sTitle, Coordinate &coord, Size& rectSize, Point& left);

END_CREATE_REFCLASS