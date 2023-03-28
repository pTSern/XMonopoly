#pragma once

#include "../../Player.h"

USING_NS_ALL;

BEGIN_CREATE_REFCLASS(BotPlayer, Player)

public:
    virtual void purchaseProperty(Property* property);
    virtual void acquireProperty(Property* property);
    virtual void upgradeProperty(Property* property);

END_CREATE_REFCLASS
