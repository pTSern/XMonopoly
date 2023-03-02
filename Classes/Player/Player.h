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

public:
    virtual void update(float dt);

public:
    bool onTouch(Touch *touch, Event *event);
    bool endTouch(Touch *touch, Event *event);

public:
    void setControlChampion(ChampionInGame *pChampion);
    void setChampionViewPoint(ChampionInGame *pChampion);
    bool buyingProperty(Player* pOwner);
    void pay(Player* player, float money);
    void onLandArena(Arena* arena);
    CREATE_SET_GET_FUNC(setSelectType, getSelectType, SelectType, m_eType);
    CREATE_SET_GET_FUNC(setSelectObject, getSelectObject, GameObject*, m_pSelectingObject)

//// Client Player
    bool yesOrNoSelector(std::string sMessage);
    void addChampion(ChampionInGame* pChamp);

protected:
    std::vector<ChampionInGame*> m_vChampions;
    ChampionInGame* m_pControllingChampion;
    ChampionInGame* m_pViewPointChampion;
    Economy m_pEconomy;
    EventListenerTouchOneByOne *m_pEventListener;

    GameObject* m_pSelectingObject;
    SelectType m_eType;
    // Money Label

END_CREATE_REFCLASS