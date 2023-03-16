#pragma once

#include "ZyUwU/ZyUwU.h"
#include "../SpecialArena.h"

USING_NS_ALL;

BEGIN_CREATE_REFCLASS(TaxArena, SpecialArena)

public:
    static TaxArena* createWithProperties(const std::string& title, Coordinate& coord, Size& rectSize, Point& left);
    static TaxArena* createFullPath(const std::string& title, Coordinate& coord, Size& rectSize, Point& left, float& tax);

public:
    virtual void update(float dt);
    virtual void onLand(ChampionInGame *pChamp);
    virtual void config();

public:
    CREATE_SET_GET_FUNC(setTax, getTax, float, m_fTax);

protected:
    float m_fTax;

END_CREATE_REFCLASS
