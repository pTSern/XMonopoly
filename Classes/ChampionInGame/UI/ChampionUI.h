#pragma once

#include "../../ZyUwU/ZyUwU.h"
#include "ui/CocosGUI.h"
#include "Support/GameConstant.h"
#include "GameObject/GameObject.h"

USING_NS_ALL;

class ChampionUISupport
{
public:
    ChampionUISupport(std::string background, std::string main, std::string front) :
    g_sBackground(background), g_sFrontEnd(front), g_sMain(main)
    {

    }
    std::string g_sBackground, g_sMain, g_sFrontEnd;
};

typedef ChampionUISupport ChampUISup;

class ChampionInGame;
BEGIN_CREATE_REFCLASS(ChampionUI, GameObject)

public:
    static ChampionUI* createWithProperties(const ChampUISup& hp, const ChampUISup& mana,
                              const std::string& globalBackground);
    static ChampionUI * createWithProperties(std::string hp_background, std::string hp_main, std::string hp_front_end, std::string mana_background, std::string mana_main, std::string mana_front_end, std::string global_background);
    static ChampionUI* createDefault();
public:
    virtual ~ChampionUI();
    virtual void setPosition(Point position);

public:
    virtual void update(float dt);
    void config();
    void updateAfterMoving();
    CREATE_SET_FUNC(setOwner, ChampionInGame*, m_pOwner);

protected:
    void loadElement(const ChampUISup& hp,const ChampUISup& mana,
                     const std::string& globalBackground);
    void loadElement(std::string hp_background, std::string hp_main, std::string hp_front_end, std::string mana_background, std::string mana_main, std::string mana_front_end, std::string global_background);

protected:
    ChampionInGame* m_pOwner;

    ui::LoadingBar *m_pHpBar, *m_pManaBar;
    ZYSprite *m_pHpBackground, *m_pManaBackground;
    ZYSprite *m_pHpFrontEnd, *m_pManaFrontEnd;
    ZYLabel *m_pSkillPoint;

    ZYSprite * m_pGlobalBackground;

END_CREATE_REFCLASS;
