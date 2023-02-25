#pragma once

#include "ZyUwU/ZyUwU.h"
#include "ui/CocosGUI.h"

#include "ChampionInGame/ChampionInGame.h"
#include "GameObject/Economy/Economy.h"

USING_NS_ALL;

class Property;
BEGIN_CREATE_REFCLASS(Player, Layer)

public:
    virtual void update(float dt);

public:
    bool onTouch(Touch *touch, Event *event);
    bool endTouch(Touch *touch, Event *event);

public:
    void setControlChampion(ChampionInGame *pChampion);
    void setChampionViewPoint(ChampionInGame *pChampion);
    void loadSkillDeck();
    bool buyingProperty(Player* pOwner);
    void pay(Player* player, float money);
    void onLandArena(Arena* arena);
//// Client Player
    bool yesOrNoSelector(std::string sMessage);

protected:
    std::vector<ChampionInGame*> m_vChampions;
    ChampionInGame* m_pControllingChampion;
    ChampionInGame* m_pViewPointChampion;
    Economy m_pEconomy;
    EventListenerTouchOneByOne *m_pEventListener;

END_CREATE_REFCLASS