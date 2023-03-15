#include "SkillInGame.h"
#include "Skill/SkillManager/SkillManager.h"
#include "ChampionInGame/ChampionInGame.h"
#include "Dice/Dice.h"

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

        ret->m_pProperties = skill->getXProperties();
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
        ret->m_pSkillStatics->setManaCost(0);
        ret->m_pSkillCard = SkillCard::createDefault();
        ret->m_pSkillCard->setDescriptionLabel("The champion moves to a new Arena with a number equal to the Dice number");
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

// ALL MECHANIC

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

//// Virtual

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

void SkillInGame::onTrigger()
{
    /*
     * This is only called after Player clicks the USE button (which belongs to
     * SkillManager -> this means SkillManager must check the USE's condition,
     * which, must be TRUE)
     */

    if(m_bIsNeedDice)
    {
        this->m_pOwner->getOwner()->enableDice();
    }

    /// Pay the Mana, Hp, Sp Cost. Set Skill to cool down
    this->m_pSkillStatics->castSkill();
    this->m_pOwner->getOwner()->castingSkill();

    /// Disable USE button
    this->m_pOwner->setUseButton(false);

    /// Schedule the skill's mechanic
    this->schedule(CC_SCHEDULE_SELECTOR(SkillInGame::scheduleMechanic));
    //// Do Mechanic here
}

void SkillInGame::endTrigger()
{
    this->unschedule(CC_SCHEDULE_SELECTOR(SkillInGame::scheduleMechanic));
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