#pragma once

#include "ZyUwU/ZyUwU.h"
#include "ui/CocosGUI.h"

USING_NS_ALL;

class Player;
BEGIN_CREATE_REFCLASS(PlayerUI, Node)

public:
    void revokeYesOrNo();

protected:
    Menu* m_pBuyingProperty;
    Menu* m_pYesOrNo;
    Player* m_pOwner;

END_CREATE_REFCLASS