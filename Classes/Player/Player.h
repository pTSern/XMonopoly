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

    enum class PlayerAction
    {
        IDLE = 0,
        CONTROLLING
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
    void setChampionViewPoint(ChampionInGame *pChampion);
    void setControlChampion(ChampionInGame* champ);

    bool buyingProperty(Property *pro);
    void pay(Player* player, float money);
    void onLandArena(Arena* arena);
    void receiveMoney(float fAmount);
    CREATE_SET_GET_FUNC(setSelectType, getSelectType, SelectType, m_eType);
    CREATE_SET_GET_FUNC(setSelectObject, getSelectObject, GameObject*, m_pSelectingObject)
    CREATE_SET_GET_FUNC(setTheColor, getTheColor, Color4F, m_Color);
    void disable();
    void enable();
    void finishAction();

    void startTurn(ChampionInGame* child);
    void endTurn();

    CREATE_GET_FUNC(getChampChildren, std::vector<ChampionInGame*>, m_vChampions);

    void lose();
    void moneyIndicator(float money, bool isPay);


    ///\ Client Player
    bool yesOrNoSelector(std::string sMessage);
    void addChampion(ChampionInGame* pChamp);


protected:
    /// Must declare
    std::vector<ChampionInGame*> m_vChampions;        ///< array of children champions
    std::vector<Property*> m_vOwn;                    ///< weak reference to parent champion

    /// Container
    ChampionInGame* m_pControllingChampion;           ///< weak reference to the is-turn champion
    ChampionInGame* m_pViewPointChampion;             ///< weak reference to the viewpoint champion

    Economy m_pEconomy;                               ///< contain player's money
    EventListenerTouchOneByOne *m_pEventListener;     ///< event listener
    GameObject* m_pSelectingObject;                   ///< weak reference to selecting object
    SelectType m_eType;                               ///< mark the selecting object's type
    PlayerAction m_eAction;                           ///< current action of the player

    // Money Label
    ZYLabel* m_pMoney;                                ///< money's label, help display

    Color4F m_Color;                                  ///< player's color

    int m_nChangeCount;

END_CREATE_REFCLASS