#pragma once

#include "ZyUwU/ZyUwU.h"
#include "Skill/Skill.h"

USING_NS_ALL;

class ChampionInGame;
class SkillManager;
BEGIN_CREATE_REFCLASS(SkillInGame, Skill)

#define MAX_SKILL_IN_DECK 5

    typedef std::function<void(SkillInGame*, float)> SkillMechanicCallback;

public:
    static SkillInGame* createWithSkill(Skill* skill);
    static SkillInGame* createTest();

public: // Other callback func
    static void MoveBySkill(SkillInGame* skill, float dt);
    static void Healing(SkillInGame* skill, float dt);

public: // Virtual func
    virtual void config();
    virtual void onTrigger();
    virtual void endTrigger();

    virtual void doMechanic(float dt);

    //Schedule
    virtual void update(float dt);
    virtual void scheduleMechanic(float dt);

public:
    CREATE_SET_GET_FUNC(setOwner,getOwner, SkillManager*, m_pOwner);
    CREATE_GET_FUNC(getSkillCard, SkillCard*, m_pSkillCard);
    CREATE_GET_FUNC(isFinishSelect, bool, m_bFinishSelect);
    CREATE_GET_FUNC(isSelectable, bool, m_pCondition->isValid());
    CREATE_GET_FUNC(isReady, bool, m_pSkillStatics->isReady());
    void onSelect();
    void unSelect();

    CREATE_SET_FUNC(setSkillMechanic, const SkillMechanicCallback&, m_oMechanicCallback);
    void conNotify();

    void disable();
    void enable();

protected:
    SkillManager *m_pOwner;

    bool m_bFinishSelect;

    SkillMechanicCallback m_oMechanicCallback;

END_CREATE_REFCLASS