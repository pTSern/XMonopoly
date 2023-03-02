#pragma once

#include "../ZyUwU/ZyUwU.h"
#include "../Statics/Statics.h"
#include "../GameObject/GameObject.h"
#include "SkillStatics/SkillStatics.h"

USING_NS_ALL;

class SkillCard;
BEGIN_CREATE_REFCLASS(Skill, GameObject)

public:
    static Skill* createWithProperties(XProperties *pProperties, SkillStatics *pStatics, bool bIsClone = true, bool bIsClean = false);

public:
    virtual void update(float dt);
    virtual ~Skill();

public:
    CREATE_CLONE_SET_FUNC(setProperties, XProperties, m_pProperties);
    CREATE_CLONE_SET_FUNC(setStatics, SkillStatics, m_pSkillStatics);

    CREATE_GET_FUNC(getSkillCard, SkillCard*, m_pSkillCard);
    CREATE_GET_FUNC(getSkillStatics, SkillStatics*, m_pSkillStatics);
    CREATE_GET_FUNC(getXProperties, XProperties*, m_pProperties);

protected:
    SkillStatics *m_pSkillStatics;
    SkillCard *m_pSkillCard;


END_CREATE_REFCLASS
