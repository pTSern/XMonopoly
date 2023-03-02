#pragma once

#include "ZyUwU/ZyUwU.h"
#include "Skill/Skill.h"

USING_NS_ALL;

class ChampionInGame;
BEGIN_CREATE_REFCLASS(SkillInGame, Skill)

public:

protected:
    ChampionInGame* m_pOwner;

END_CREATE_REFCLASS