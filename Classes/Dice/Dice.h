#pragma once

#include "../ZyUwU/ZyUwU.h"
#include "cocos2d.h"

USING_NS_ALL;

BEGIN_CREATE_REFCLASS(Dice, Ref)

public:
    static Dice* createWithProperties();

public:
    CREATE_GET_FUNC(getLastestDiceNum, int, m_vDiceMemory.back());


protected:
    ZYSprite* m_pDice;
    int m_nDiceNum;
    std::vector<int> m_vDiceMemory;

END_CREATE_REFCLASS;