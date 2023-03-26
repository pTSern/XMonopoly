#pragma once

#include "ZyUwU/ZyUwU.h"
#include "ui/CocosGUI.h"

USING_NS_ALL;

static const std::string icon_attack_dir = "hud/helper/icon/atk.png";
static const std::string icon_armor_dir = "hud/helper/icon/armor.png";
static const std::string icon_speed_dir = "hud/helper/icon/speed.png";
static const std::string icon_life_dir = "hud/helper/icon/life.png";

class Player;
BEGIN_CREATE_REFCLASS(PlayerUI, Node)

public:
    static PlayerUI* createClientUI();

public:
    bool initWithUserData();

protected:
    ZYSprite *m_pAtk, *m_pSpeed, *m_pArmor, *m_pLife;
    ZYSprite *m_pFrame, *m_pBackground;

END_CREATE_REFCLASS