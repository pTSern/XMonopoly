#include "SkillMoveBy.h"
#include "Skill/SkillManager/SkillManager.h"
#include "ChampionInGame/ChampionInGame.h"
#include "Dice/Dice.h"

//// Constructor

MoveBySkill::MoveBySkill()
{

}

//// Virtual

bool MoveBySkill::init()
{
    m_bIsNeedDice = true;
    m_bIsNeedSelect = false;
    this->m_pSkillStatics = SkillStatics::create();
    this->m_pSkillStatics->setManaCost(0);
    this->m_pSkillCard = SkillCard::createDefault();
    this->m_pSkillCard->setOwner(this);
    this->m_pCondition = Condition::create();
    this->m_pCondition->setOwner(this);
    this->m_bIsNeedDice = true;
    this->config();
    return true;
}

void MoveBySkill::log()
{
    ZY_EZ_LOG;
}

std::string MoveBySkill::toString(int nTab)
{
    std::string ts = SkillInGame::toString(nTab);
    return ts;
}

void MoveBySkill::doMechanic(float dt)
{
    if(this->m_bIsNeedDice && this->m_pOwner->getOwner()->getDice()->isRolled())
    {
        auto dice = this->m_pOwner->getOwner()->getDice()->getLastestDiceNum();
    }
}