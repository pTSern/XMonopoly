#pragma once

#include "ZyUwU/ZyUwU.h"

USING_NS_ALL;

#include "../Economy.h"

BEGIN_CREATE_REFCLASS(IngameEconomyManager, Node)

public:
    static IngameEconomyManager* createIngameEconomy();

public:
    virtual void update(float dt) override;

public:
    enum class MoveVDirection
    {
        NONE = 0,
        TOP = 1,
        BOTTOM = -1
    };

    enum class MoveHDirection
    {
        NONE = 0,
        LEFT = -1,
        RIGHT = 1
    };

    struct MoveDirection
    {
    public:
        MoveDirection(MoveHDirection hDir, MoveVDirection vDir);
        CREATE_GET_FUNC(hDirectionToFloat, float, (float)g_eHDir);
        CREATE_GET_FUNC(vDirectionToFloat, float, (float)g_eVDir);

        MoveHDirection g_eHDir;
        MoveVDirection g_eVDir;
    };

///] Global control
    void disable();
    void enable();

///] Label control

    void setPosition(Point pos);
    virtual void setPosition(const float xx, const float yy) override;
    void executeIndicator(const float& money, const bool& isPay);

///] Economy control

    void setAmount(float amount);
    bool pay(IngameEconomyManager *target, float money, bool animate = true);
    bool pay(float money, bool animate = true);
    bool isPayable(float money);
    void receive(float money, bool animate = true);
    CREATE_GET_FUNC(getEconomy, Economy, m_economy);
    CREATE_GET_FUNC(getAmount, float, m_economy.getAmount());

///] Update loop

protected:
    MoveDirection autoSelectMoveDirection();

protected:
    Economy m_economy;
    ZYLabel *m_pLabel;
    ZYSprite *m_pIcon;

END_CREATE_REFCLASS

using IgEcoMng = IngameEconomyManager;

