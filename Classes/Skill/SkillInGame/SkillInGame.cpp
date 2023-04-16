#include "SkillInGame.h"

#include <utility>
#include "Skill/SkillManager/SkillManager.h"
#include "ChampionInGame/ChampionInGame.h"
#include "Dice/Dice.h"
#include "Player/Player.h"

#include "Skill/Mechanic/Mechanic.h"
#include "Skill/Mechanic/MechanicManager.h"

/////////////////////////////////////////////////////////////////////

///] Constructor

SkillStaticsAddition::SkillStaticsAddition(const float amount, const float percent, std::string& name) :
g_fAmount(amount), g_fPercentOfAmount(percent), g_sName(name)
{

}

SkillStaticsAddition::SkillStaticsAddition(const float amount, std::string& name) :
g_fAmount(amount), g_fPercentOfAmount(1), g_sName(name)
{

}

SkillStaticsAddition::SkillStaticsAddition(const SkillStaticsAddition& other)
{
    *this = other;
}

///] Static

SkillStaticsAddition* SkillStaticsAddition::create(const float amount,const float percent, std::string& name)
{
    auto ret = new (std::nothrow) SkillStaticsAddition(amount, percent, name);
    if(ret) return ret;
    CC_SAFE_DELETE(ret);
    return nullptr;
}

SkillStaticsAddition* SkillStaticsAddition::create(const float amount, std::string& name)
{
    auto ret = new (std::nothrow) SkillStaticsAddition(amount, name);
    if(ret) return ret;
    CC_SAFE_DELETE(ret);
    return nullptr;
}

SkillStaticsAddition* SkillStaticsAddition::NULL_VALUE = new (std::nothrow) SkillStaticsAddition(-1.0f, -1.0f, (std::string &)"");
SkillStaticsAddition* SkillStaticsAddition::ZERO = new (std::nothrow) SkillStaticsAddition(0.0f, 0.0f, (std::string &)"");

///] Public

bool SkillStaticsAddition::isZero() const
{
    if(g_fAmount <= 0)
    {
        return true;
    }
    return false;
}

///] Operator

inline SkillStaticsAddition::operator bool() const
{
    if(g_fAmount < 0 || g_fPercentOfAmount < 0)
    {
        return false;
    }
    return true;
}

SkillStaticsAddition& SkillStaticsAddition::operator=(const SkillStaticsAddition& other)
{
    if(this == &other)
    {
        return *this;
    }

    this->g_fAmount = other.g_fAmount;
    this->g_fPercentOfAmount = other.g_fPercentOfAmount;
    this->g_sName = other.g_sName;

    return *this;
}

/////////////////////////////////////////////////////////////////////

///] Constructor

AdditionStats* AdditionStats::createWithData(const SkillStaticsAddition* data, ...)
{
    va_list args;
    va_start(args, data);

    auto ret = AdditionStats::createWithDataList(data, args);

    va_end(args);
    return ret;
}

AdditionStats* AdditionStats::createWithDataList(const SkillStaticsAddition* data, va_list args)
{
    std::vector<const SkillStaticsAddition*> list;

    if(data)
    {
        list.push_back(data);
        auto var = va_arg(args, const SkillStaticsAddition*);
        while(var)
        {
            list.push_back(var);
            var = va_arg(args, const SkillStaticsAddition*);
        }
    }

    return AdditionStats::createWithVector(list);
}

AdditionStats* AdditionStats::createWithVector(std::vector<const SkillStaticsAddition*>& vector)
{
    auto ret = new (std::nothrow) AdditionStats();

    if(ret)
    {
        ret->m_vList = vector;
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

AdditionStats* AdditionStats::NULL_VALUE = AdditionStats::createWithData(nullptr, nullptr);
AdditionStats* AdditionStats::ZERO = AdditionStats::createWithData(STRUCT_SSA::ZERO, nullptr);

///] Public

bool AdditionStats::isZero()
{
    if(m_vList.empty()) return true;
    int zero_num = 0;
    for(auto &x : m_vList)
    {
        if(x->isZero())
        {
            zero_num++;
        }
    }
    return zero_num == m_vList.size();
}

/////////////////////////////////////////////////////////////////////

//// Constructor

SkillInGame::SkillInGame() :
m_pOwner(nullptr),
m_oMechanicCallback(nullptr),
m_bFinishSelect(false)
{
}

//// Static

SkillInGame* SkillInGame::createWithSkill(Skill* skill)
{
    auto ret = new (std::nothrow) SkillInGame();
    if(ret && ret->init() && skill)
    {
        ret->autorelease();

        //ret->m_pProperties = skill->getXProperties();
        ret->m_sDeputizeTexture = skill->getDeputizeTexture();
        ret->m_pSkillStatics = skill->getSkillStatics();
        ret->m_pSkillCard = skill->getSkillCard();
        ret->m_pSkillCard->setOwner(ret);
        //ret->m_pTargets = skill->getTarget();

        ret->config();

        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

SkillInGame* SkillInGame::createTest()
{
    auto ret = new (std::nothrow) SkillInGame();
    if(ret && ret->init())
    {
        ret->autorelease();

        ret->m_pSkillStatics = SkillStatics::create();
        ret->m_pSkillStatics->setPhysicDmg(35);
        ret->m_pSkillStatics->setManaCost(0);
        ret->m_pSkillCard = SkillCard::createDefault();
        ret->m_pSkillCard->setDescriptionLabel("The champion moves to a new Arena with a number equal to the Dice number");
        ret->m_pSkillCard->setManaCostLabel("0");
        ret->m_pSkillCard->setNameLabel("MOVE");
        ret->m_pSkillCard->setSkillPointCostLabel("0");
        ret->m_pSkillCard->setOwner(ret);
        ret->m_pCondition = Condition::create();
        ret->m_pCondition->setOwner(ret);
        ret->m_bIsNeedDice = true;
        ret->config();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

SkillInGame* SkillInGame::createNoDice()
{
    auto ret = SkillInGame::createTest();
    ret->m_bIsNeedDice = false;
    ret->m_pSkillStatics->setPhysicDmg(50);

    return ret;
}

///] ALL MECHANIC

void SkillInGame::MoveBySkill(SkillInGame* skill, float dt)
{
    if(skill->m_bIsNeedDice && skill->m_pOwner->getOwner()->getDice()->isRolled())
    {
        if(skill->m_pOwner->getOwner()->isCastingSkill())
        {
            skill->m_pOwner->getOwner()->jumpTo(skill->m_pOwner->getOwner()->getDice()->getLastestDiceNum());
        }
    }
}

void SkillInGame::Healing(SkillInGame* skill, float dt)
{
    //skill->m_pOwner->getOwner()->getStatics()->addHp(20);
    //skill->m_pOwner->getOwner()->endTurn();
    //skill->m_pOwner->getOwner()->getOwner()->finishAction();
    //if(skill->m_pOwner->getOwner()->isCastingSkill())
    //{
    //    auto pj = ShootProjectile::create(skill, 5, "projectile/arrow.png", 50, 2.0f);
    //    skill->addChild(pj);
    //    if(pj->getIsFinish())
    //    {
    //        skill->m_pOwner->getOwner()->endTurn();
    //        skill->m_pOwner->getOwner()->getOwner()->finishAction();
    //    }
    //}
}

///] Virtual

void SkillInGame::log()
{
    ZY_EZ_LOG;
}

std::string SkillInGame::toString(int nTab)
{
    std::string ts;
    std::string tab = ZY_SP_TAB(nTab);
    ts += m_pSkillCard->toString(nTab + 1);
    return ts;
}

bool SkillInGame::init()
{
    return true;
}

void SkillInGame::config()
{
    this->addChild(m_pSkillCard);
    this->addChild(m_pCondition);
}

void SkillInGame::update(float dt)
{
}

void SkillInGame::setMechanic(MechanicManager* mechanic)
{
    this->m_pMechanic = mechanic;
    this->addChild(mechanic);
}

void SkillInGame::onTrigger()
{
    /*
     * This is only called after Player clicks the USE button (which belongs to
     * SkillManager -> this means SkillManager must check the USE's condition,
     * which, must be TRUE)
     */

    ///) If this skill need dice, enable dice (the button of dice).
    if(m_bIsNeedDice)
    {
        this->m_pOwner->getOwner()->enableDice();
    }

    ///) Set this skill to cool down
    this->m_pSkillStatics->castSkill();

    ///) Force owner to pay the mana/hp/sp cost.
    auto mc = m_pSkillStatics->getManaCost();
    auto hc = m_pSkillStatics->getHpCost();
    auto sc = m_pSkillStatics->getSpCost();
    this->m_pOwner->getOwner()->castingSkill(mc, hc, sc);

    /// Disable USE button
    this->m_pOwner->setUseButton(false);

    /// Schedule the skill's mechanic
    //this->schedule(CC_SCHEDULE_SELECTOR(SkillInGame::scheduleMechanic));
    if(m_pMechanic) m_pMechanic->onTrigger();
    //// Do Mechanic here
}

void SkillInGame::endTrigger()
{
    //this->unschedule(CC_SCHEDULE_SELECTOR(SkillInGame::scheduleMechanic));
    //// FORCE END TURN
    //this->m_pOwner->getOwner()->endTurn();
    /// Kill all selected target

}

void SkillInGame::scheduleMechanic(float dt)
{
    if(this->m_oMechanicCallback)
    {
        this->m_oMechanicCallback(this, dt);
    }
    //if(this->m_bIsFinish)
    if(!this->m_pOwner->getOwner()->isTurn())
    {
        this->endTrigger();
    }
}

void SkillInGame::doMechanic(float dt)
{
    /// Do mechanic here
}

//// Public

void SkillInGame::onSelect()
{
    //if(!m_pCondition->isValid()) return false;
    //// Condition
    this->m_pOwner->unselectSkill();
    this->m_pOwner->setSelectingSkill(this);

    //// Check On select condition (Move this to skill card -> only do True)
        ///True: Change The Owner selecting skill to this
        ///False: Return

    //// Check this skill target type
        ///!NONE: Do selecting target here
        ///NONE: Skip

}

void SkillInGame::unSelect()
{
    this->m_pSkillCard->onUnselect();
    //// Kill the selected target here
}

void SkillInGame::conNotify()
{
    this->m_pCondition->notify();
}

void SkillInGame::disable()
{
    this->m_pSkillCard->disable();
}

void SkillInGame::enable()
{
    this->m_pSkillCard->enable();
}

///

void SkillInGame::additionStats(STRUCT_AS *physicDmg,
                                STRUCT_AS *magicDmg,
                                STRUCT_AS *pureDmg,
                                STRUCT_AS *physicPier,
                                STRUCT_AS *magicPier,
                                STRUCT_AS *physicPierNum,
                                STRUCT_AS *magicPierNum,
                                STRUCT_AS *physicCritRate,
                                STRUCT_AS *magicCritRate,
                                STRUCT_AS *physicCritMulti,
                                STRUCT_AS *magicCritMulti)
{
    additionPhysicDamage(physicDmg);
    additionMagicDamage(magicDmg);
    additionPureDamage(pureDmg);

    additionPhysicPiercingPercent(physicPier);
    additionMagicPiercingPercent(magicPier);

    additionPhysicPiercingNumber(physicPierNum);
    additionMagicPiercingNumber(magicPierNum);

    additionPhysicCritRate(physicCritRate);
    additionMagicCritRate(magicCritRate);

    additionPhysicCritMultiple(physicCritMulti);
    additionMagicCritMultiple(magicCritMulti);
}

void SkillInGame::additionPhysicDamage(STRUCT_AS *value)
{
    if(!value) return;
    if(value->isZero()) return;
    auto v = value->getStatsVector();
    for(auto *x : v)
    {
        m_pSkillStatics->addPhysicDmg(x->getValue());
    }
}

void SkillInGame::additionMagicDamage(STRUCT_AS *value)
{
    if(!value) return;
    if(value->isZero()) return;
    auto v = value->getStatsVector();
    for(auto *x : v)
    {
        m_pSkillStatics->addMagicDmg(x->getValue());
    }
}

void SkillInGame::additionPureDamage(STRUCT_AS *value)
{
    if(!value) return;
    if(value->isZero()) return;
    auto v = value->getStatsVector();
    for(auto *x : v)
    {
        m_pSkillStatics->addPureDmg(x->getValue());
    }
}

void SkillInGame::additionPhysicPiercingPercent(STRUCT_AS *value)
{
    if(!value) return;
    if(value->isZero()) return;
    auto v = value->getStatsVector();
    for(auto *x : v)
    {
        m_pSkillStatics->addPhysicPiercingPercent(x->getValue());
    }
}

void SkillInGame::additionMagicPiercingPercent(STRUCT_AS *value)
{
    if(!value) return;
    if(value->isZero()) return;
    auto v = value->getStatsVector();
    for(auto *x : v)
    {
        m_pSkillStatics->addMagicPiercingPercent(x->getValue());
    }
}

void SkillInGame::additionPhysicPiercingNumber(STRUCT_AS *value)
{
    if(!value) return;
    if(value->isZero()) return;
    auto v = value->getStatsVector();
    for(auto *x : v)
    {
        m_pSkillStatics->addPhysicPiercingNumber(x->getValue());
    }
}

void SkillInGame::additionMagicPiercingNumber(STRUCT_AS *value)
{
    if(!value) return;
    if(value->isZero()) return;
    auto v = value->getStatsVector();
    for(auto *x : v)
    {
        m_pSkillStatics->addMagicPiercingNumber(x->getValue());
    }
}

void SkillInGame::additionPhysicCritRate(STRUCT_AS *value)
{
    if(!value) return;
    if(value->isZero()) return;
    auto v = value->getStatsVector();
    for(auto *x : v)
    {
        m_pSkillStatics->addPhysicCritRate(x->getValue());
    }
}

void SkillInGame::additionMagicCritRate(STRUCT_AS *value)
{
    if(!value) return;
    if(value->isZero()) return;
    auto v = value->getStatsVector();
    for(auto *x : v)
    {
        m_pSkillStatics->addMagicCritRate(x->getValue());
    }
}

void SkillInGame::additionPhysicCritMultiple(STRUCT_AS *value)
{
    if(!value) return;
    if(value->isZero()) return;
    auto v = value->getStatsVector();
    for(auto *x : v)
    {
        m_pSkillStatics->addPhysicCritMultiple(x->getValue());
    }
}

void SkillInGame::additionMagicCritMultiple(STRUCT_AS *value)
{
    if(!value) return;
    if(value->isZero()) return;
    auto v = value->getStatsVector();
    for(auto *x : v)
    {
        m_pSkillStatics->addMagicCritMultiple(x->getValue());
    }
}
