#pragma once

#include "ZyUwU/ZyUwU.h"
#include "ui/CocosGUI.h"

#include "ChampionInGame/ChampionInGame.h"
#include "GameObject/Economy/Economy.h"

USING_NS_ALL;

class Property;
BEGIN_CREATE_REFCLASS(Player, Layer)

public:
    enum class SelectType
    {
        NONE = 0,
        CHAMPION,
        ARENA,
        BOTH
    };

    enum class SelectMode
    {
        NONE = 0,
        SKILL_TARGET,
        SELLING_ARENA
    };

    enum class PlayerAction
    {
        NORMAL,
        THINKING
    };

    enum class PlayerSelect
    {
        NONE = 0,
        YES,
        NO
    };

public:
    static Player* createClientPlayer();
    static Player* createBot();
    static Player* createPlayer();

public:
    virtual void update(float dt);

public:
    bool onTouch(Touch *touch, Event *event);
    bool endTouch(Touch *touch, Event *event);

public:
    void setControlChampion(ChampionInGame *pChampion);
    void setChampionViewPoint(ChampionInGame *pChampion);
    bool buyingProperty(Property *pro);
    void pay(Player* player, float money);
    void onLandArena(Arena* arena);
    void receiveMoney(float fAmount);
    CREATE_SET_GET_FUNC(setSelectType, getSelectType, SelectType, m_eType);
    CREATE_SET_GET_FUNC(setSelectObject, getSelectObject, GameObject*, m_pSelectingObject)
    CREATE_SET_FUNC(setControllingChamp, ChampionInGame*, m_pControllingChampion);
    CREATE_SET_GET_FUNC(setTheColor, getTheColor, Color4F, m_Color);
    void disable();
    void enable();
    void finishAction();

    CREATE_GET_FUNC(getChampChildren, std::vector<ChampionInGame*>, m_vChampions);
    CREATE_GET_FUNC(isTrulyEndTurn, bool, m_bTruelyEndTurn);

    void lose();


//// Client Player
    bool yesOrNoSelector(std::string sMessage);
    void addChampion(ChampionInGame* pChamp);

protected:
    /// Must declare
    std::vector<ChampionInGame*> m_vChampions;
    std::vector<Property*> m_vOwn;

    /// Container
    ChampionInGame* m_pControllingChampion;
    ChampionInGame* m_pViewPointChampion;
    Economy m_pEconomy;
    EventListenerTouchOneByOne *m_pEventListener;
    GameObject* m_pSelectingObject;
    SelectType m_eType;
    PlayerAction m_eAction;
    PlayerSelect m_eSelect;
    // Money Label

    ZYLabel* m_pMoney;

    Color4F m_Color;

    int m_nChangeCount;
    bool m_bTruelyEndTurn;

END_CREATE_REFCLASS