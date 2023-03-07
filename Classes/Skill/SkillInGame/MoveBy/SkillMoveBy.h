#pragma once

#include "ZyUwU/ZyUwU.h"
#include "../SkillInGame.h"

USING_NS_ALL;

BEGIN_CREATE_REFCLASS(MoveBySkill, SkillInGame)

public:
    virtual void doMechanic(float dt);
END_CREATE_REFCLASS