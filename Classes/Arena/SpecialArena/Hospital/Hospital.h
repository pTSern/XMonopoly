#pragma once

#include "ZyUwU/ZyUwU.h"
#include "../SpecialArena.h"

USING_NS_ALL;

BEGIN_CREATE_REFCLASS(HospitalArena, SpecialArena)

public:
    static HospitalArena* createWithProperties(const std::string& title, Coordinate& coord, Size& rectSize, Point& left);
    static HospitalArena* createFullPath(const std::string& title, Coordinate& coord, Size& rectSize, Point& left, float& fee);

public:
    virtual void update(float dt);
    virtual void onLand(ChampionInGame *pChamp);
    virtual void config();

    CREATE_SET_FUNC(setFeePerHp, float, m_fFeePerHp);

protected:
    float m_fFeePerHp;

END_CREATE_REFCLASS
