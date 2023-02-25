#pragma once

#include "../ZyUwU/ZyUwU.h"
#include "../GameObject/GameObject.h"

USING_NS_ALL;

BEGIN_CREATE_REFCLASS(GameEffect, GameObject)

public:
    virtual void update(float dt);

END_CREATE_REFCLASS
