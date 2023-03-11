#pragma once

#include "ZyUwU/ZyUwU.h"

USING_NS_ALL;

class Player;
BEGIN_CREATE_REFCLASS(ViewPoint, Node)

public:
    void setViewPointPlayer(Player* player);

protected:
    void disableCurrentViewPoint();

protected:
    Player* m_pViewPointPlayer;         ///< weak reference to the view-point player. Default is cilent player

END_CREATE_REFCLASS