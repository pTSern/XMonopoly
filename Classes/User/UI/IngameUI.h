#pragma once

#include "../../ZyUwU/ZyUwU.h"
#include "User/Helper.h"

USING_NS_ALL;

BEGIN_CREATE_INSTANCE_REFCLASS(IngameUI, Node)

public:
    FUNC_REPLACE_UI(setBackground, m_pBackground, p_sBackground);
    FUNC_REPLACE_UI(setHouseIcon, m_pHouseIcon, p_sHouseIcon);
    FUNC_REPLACE_UI(setDice, m_pDice, p_sDice);

    CREATE_SET_GET_FUNC(setBackground, getBackground, ZYSprite*, m_pBackground);
    CREATE_SET_GET_FUNC(setHouseIcon, getHouseIcon, ZYSprite*, m_pHouseIcon);
    CREATE_SET_GET_FUNC(setDice, getDice, ZYSprite*, m_pDice);

protected:
    ZYSprite* m_pBackground, *m_pHouseIcon, *m_pDice;

private:
    std::string p_sBackground, p_sHouseIcon, p_sDice;

END_CREATE_INSTANCE_REFCLASS