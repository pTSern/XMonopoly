#pragma once

#include "ZyUwU/ZyUwU.h"
#include "ui/CocosGUI.h"
#include "GameObject/GameObject.h"

USING_NS_ALL;

#define HUD_DIR std::string("hud/")
#define BAR_DIR std::string("bar/")
#define BACKGROUND_DIR std::string("background/")
#define HEALTH_DIR std::string("health_bar/")
#define MANA_DIR std::string("mana_bar/")
#define SKILL_POINT_DIR std::string("skillpoint_bar/")

#define HEALTH_BAR_DIR HUD_DIR + HEALTH_DIR + BAR_DIR
#define HP_BAR_FULL_DIR(__NAME__) HEALTH_BAR_DIR + __NAME__
#define HPBF_DIR(__NAME__) HP_BAR_FULL_DIR(__NAME__)
#define HEALTH_BACKGROUND_DIR HUD_DIR + HEALTH_DIR + BACKGROUND_DIR
#define HP_BG_FULL_DIR(__NAME__) HEALTH_BACKGROUND_DIR + __NAME__
#define HPBGF_DIR(__NAME__) HP_BG_FULL_DIR(__NAME__)

#define MANA_BAR_DIR HUD_DIR + MANA_DIR + BAR_DIR
#define MANA_BACKGROUND_DIR HUD_DIR + MANA_DIR + BACKGROUND_DIR
#define MANA_BAR_FULL_DIR(__NAME__) MANA_BAR_DIR + __NAME__
#define MNBF_DIR(__NAME__) MANA_BAR_FULL_DIR(__NAME__)
#define MANA_BG_FULL_DIR(__NAME__) MANA_BACKGROUND_DIR + __NAME__
#define MNBGF_DIR(__NAME__) MANA_BG_FULL_DIR(__NAME__)

#define SKILL_POINT_BAR_DIR HUD_DIR + SKILL_POINT_DIR + BAR_DIR
#define SKILL_POINT_BACKGROUND_DIR HUD_DIR + SKILL_POINT_DIR + BACKGROUND_DIR
#define SKILL_POINT_BAR_FULL_DIR(__NAME__) SKILL_POINT_BAR_DIR + __NAME__
#define SPBF_DIR(__NAME__) SKILL_POINT_BAR_FULL_DIR(__NAME__)
#define SKILL_POINT_BACKGROUND_FULL_DIR(__NAME__) SKILL_POINT_BACKGROUND_DIR + __NAME__
#define SPBGF_DIR(__NAME__) SKILL_POINT_BACKGROUND_FULL_DIR(__NAME__)

#define SET_SHOW_MORE_BOARD_HELPER(__ACTION__) \
this->m_pBackgroundBox->__ACTION__;            \
this->m_pAtkBox->__ACTION__;                   \
this->m_pDefBox->__ACTION__;                   \
this->m_pMagicDmg->__ACTION__;                 \
this->m_pMagicRes->__ACTION__;                 \
this->m_pLifeSteal->__ACTION__;                \
this->m_pMagicLifeSteal->__ACTION__;           \
this->m_pTinyBox->__ACTION__;                  \
this->m_pAtkBoxLabel->__ACTION__;              \
this->m_pDefBoxLabel->__ACTION__;              \

#define SET_STATS_BOARD_HELPER(__ACTION__) \
this->m_pAtkDmg->__ACTION__;               \
this->m_pLife->__ACTION__;                 \
this->m_pSpeed->__ACTION__;                \
this->m_pArmor->__ACTION__;                \
this->m_pAvatar->__ACTION__;               \
this->m_pHp->__ACTION__;                   \
this->m_pMana->__ACTION__;                 \
this->m_pSp->__ACTION__;                   \
this->m_pHpBar->__ACTION__;                \
this->m_pManaBar->__ACTION__;              \
this->m_pSpBar->__ACTION__;                \
this->m_pHpBackground->__ACTION__;         \
this->m_pManaBackground->__ACTION__;       \
this->m_pSpBackground->__ACTION__;         \

class ChampionInGame;
BEGIN_CREATE_REFCLASS(ChampionHUD, GameObject)

public:
    static ChampionHUD* createWithChampion(ChampionInGame *pOwner);

public:
    virtual void update(float dt);
    void updateString();

public:
    void config();
    void disable();
    void enable();
    void initAllElement();
    bool initWithChampion(ChampionInGame *pOwner);
    void showMoreButton(Ref* pSender, ui::Widget::TouchEventType type);
    void showMore();

    CREATE_SET_FUNC(setOwner, ChampionInGame*, m_pOwner);

public:
    bool onTouchBegin(Touch *touch, cocos2d::Event *event);
    void onTouchEnd(Touch *touch, cocos2d::Event *event);

protected:
    ChampionInGame *m_pOwner;

    ui::Button *m_pAvatar;
    ZYLabel *m_pChampionName;
    ZYLabel *m_pAtkDmg, *m_pMagicDmg;
    ZYLabel *m_pArmor, *m_pMagicRes;
    ZYLabel *m_pLifeSteal, *m_pMagicLifeSteal;
    ui::LoadingBar *m_pHpBar, *m_pManaBar, *m_pSpBar;
    ZYSprite *m_pHpBackground, *m_pManaBackground, *m_pSpBackground;
    ZYLabel *m_pHp, *m_pMana, *m_pSp;
    ZYLabel *m_pLife, *m_pSpeed;

    ZYSprite *m_pAtkBox, *m_pDefBox;
    ZYLabel *m_pAtkBoxLabel, *m_pDefBoxLabel;
    ZYSprite *m_pBackgroundBox;
    ZYSprite *m_pTinyBox;

    bool m_bIsShow;        ///< Mark if the show-more board is shown or not

END_CREATE_REFCLASS