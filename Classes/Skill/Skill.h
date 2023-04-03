#pragma once

#include "../ZyUwU/ZyUwU.h"
#include "../Statics/Statics.h"
#include "../GameObject/GameObject.h"
#include "SkillStatics/SkillStatics.h"
#include "SkillCard/SkillCard.h"
#include "Condition/Condition.h"

USING_NS_ALL;

class TargetType;
BEGIN_CREATE_REFCLASS(Skill, GameObject)

public:
    enum class SkillType
    {
        PASSIVE,
        ACTIVE,
        TOGGLE
    };

    enum class TargetType
    {
        NONE,
        CHAMPION,
        ARENA,
        BOTH
    };

public:
    static Skill* createWithProperties(const std::string& deputizePath, SkillStatics *pStatics, SkillCard *card = SkillCard::createDefault(), bool bIsClone = true, bool bIsClean = false);

public:
    virtual void update(float dt);
    virtual ~Skill();

public:
    //CREATE_CLONE_SET_FUNC(setProperties, XProperties, m_pProperties);
    CREATE_CLONE_SET_FUNC(setStatics, SkillStatics, m_pSkillStatics);

    CREATE_SET_GET_FUNC(setSkillCard, getSkillCard, SkillCard*, m_pSkillCard);
    CREATE_SET_GET_FUNC(setType, getType, SkillType, m_eType);
    CREATE_SET_GET_FUNC(setNeedDice, getNeedDice, bool, m_bIsNeedDice);
    CREATE_SET_GET_FUNC(setNeedSelect, getNeedSelect, bool, m_bIsNeedSelect);

    CREATE_GET_FUNC(getSkillStatics, SkillStatics*, m_pSkillStatics);
    //CREATE_GET_FUNC(getXProperties, XProperties*, m_pProperties);
    //CREATE_GET_FUNC(getTarget, TargetType*, m_pTargets);
    CREATE_GET_FUNC(getTarget, TargetType, m_eTarget);

protected:
    SkillStatics *m_pSkillStatics;
    SkillCard *m_pSkillCard;
    Condition *m_pCondition;
    //TargetType* m_pTargets;

    TargetType m_eTarget;
    SkillType m_eType;

    bool m_bIsNeedDice;
    bool m_bIsNeedSelect;

END_CREATE_REFCLASS
