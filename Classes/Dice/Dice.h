#pragma once

#include "../ZyUwU/ZyUwU.h"
#include "cocos2d.h"
#include "Map/Map.h"
#include "GameObject/GameObject.h"

USING_NS_ALL;

BEGIN_CREATE_REFCLASS(Dice, GameObject)

public:
    static Dice* createWithProperties(const std::string& sPath);

public:
    virtual void config();
    virtual void update(float dt)
    {
        CCLOG("VUA");
    }

public:
    CREATE_GET_FUNC(getLastestDiceNum, int, m_vDiceMemory.back());
    int rollDice();
    bool initWithProperties(const std::string& sPath );
    void loadElement(const std::string& path);
    void disableDice();
    void enableDice();

protected:
    ZYSprite* m_pDice;
    int m_nDiceNum;
    Rect m_centerRect;
    std::vector<int> m_vDiceMemory;

private:
    Size diceSize;

END_CREATE_REFCLASS;