#pragma once

#include "ZyUwU/ZyUwU.h"
#include "Skill/Skill.h"

USING_NS_ALL;

class ChampionInGame;
class SkillManager;

struct SkillStaticsAddition
{
public:
    static const SkillStaticsAddition NULL_VALUE;
public:
    /**
     * @param amount The amount
     * @param percent The amount of the percent of this amount.
     * @warning This Value must be a decimal number.
     */
    SkillStaticsAddition(const float amount,const float percent, std::string& name);

    SkillStaticsAddition(const float amount, std::string& name);

    SkillStaticsAddition(const SkillStaticsAddition& other);

public:
    float g_fAmount = 0.0f;
    /**
     * @def This Value defines the amount of the percent of the amount of this class.
     * @warning This Value must be a decimal number.
     * @example If the Value is 10% -> 0.1 is the value you must define to it
     */
    float g_fPercentOfAmount = 0.0f;

    std::string g_sName;

    inline operator bool() const;
    SkillStaticsAddition& operator=(const SkillStaticsAddition& other);
};

using STRUCT_SSA = SkillStaticsAddition;

struct AdditionStats
{
public:
    /**
     *
     * @param data The SkillStaticsAddition pointer that storage required data
     * @param ... Other SkillStaticsAddition
     * @return A new SkillHookChampionStatics pointer storage all SkillStaticsAddition data
     */
    static AdditionStats* createWithData(const SkillStaticsAddition* data, ...) CC_REQUIRES_NULL_TERMINATION;
    static AdditionStats* createWithDataList(const SkillStaticsAddition* data, va_list args);
    static AdditionStats* createWithVector(std::vector<const SkillStaticsAddition*>& vector);

protected:
    std::vector<const SkillStaticsAddition*> m_vList;
};

using SkillStaticsExtend = AdditionStats;

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