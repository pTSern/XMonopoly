#include "SkillStatics.h"

// SkillStatics

/**  @Note Damage Multiplier work the same as Dota2.
 *   @Formula DMG = 1 - ( (f*R) / (b+f*|R|) )
 *   @With     f is ARMOR FORMULA FACTOR = 0.06\n
 *             R is armor value\n
 *             b is ARMOR FORMULA BASE = 1\n
 *             DMG being the Damage multiplier\n
 */

///] Constructor

SkillStatics::SkillStatics() :
m_fPhysicDmg(0), m_fMagicDmg(0),
m_fPureDmg(0),
m_cPhysicPie(0), m_cMagicPie(0),
m_nCoolDown(0), m_nCurrentCoolDown(0),
m_fMnCost(0), m_fHpCost(0), m_fSpCost(0),
m_cPhysicCrit(0), m_cMagicCrit(0),
m_sDescription()
{
}

////] Static

SkillStatics* SkillStatics::create()
{
    auto ret = new (std::nothrow) SkillStatics();

    if(ret && ret->init())
    {
        return ret;
    }
    delete ret;
    return nullptr;
}

SkillStatics* SkillStatics::getMerge(SkillStatics* target)
{
    auto ret = SkillStatics::create();
    if(ret)
    {
        ret->merge(target);
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

///] Protected

bool SkillStatics::init()
{
    return true;
}

void SkillStatics::log()
{
    ZY_EZ_LOG;
}

std::string SkillStatics::toString(int nTab)
{
    std::string ts;
    std::string tab = ZY_SP_TAB(nTab);
    ts += (tab + " + Physic Damage: " + ZY_SP_NUMBER_TO_STRING(m_fPhysicDmg));
    ts += (tab + " + Magic Damage: " + ZY_SP_NUMBER_TO_STRING(m_fMagicDmg));
    ts += (tab + " + Pure Damage: " + ZY_SP_NUMBER_TO_STRING(m_fPureDmg));
    ts += (tab + " > Physic Pierce: " + m_cPhysicPie.toString(nTab + 1));
    ts += (tab + " > Magic Pierce: " + m_cMagicPie.toString(nTab + 1));
    ts += (tab + " + CoolDown: " + ZY_SP_NUMBER_TO_STRING(m_nCoolDown));
    ts += (tab + " + Mana Cost: " + ZY_SP_NUMBER_TO_STRING(m_fMnCost));
    ts += (tab + " + Heath Point Cost: " + ZY_SP_NUMBER_TO_STRING(m_fHpCost));
    ts += (tab + " + Skill Point Cost: " + ZY_SP_NUMBER_TO_STRING(m_fSpCost));
    ts += (tab + " > Physic Crit: " + m_cPhysicCrit.toString(nTab + 1));
    ts += (tab + " > Magic Crit: " + m_cMagicCrit.toString(nTab + 1));
    return ts;
}

SkillStatics* SkillStatics::clone()
{
    auto pElement = SkillStatics::create();

    if(pElement)
    {
        pElement->setMagicDmg(this->getMagicDmg());
        pElement->setPhysicDmg(this->getPhysicDmg());
        pElement->setPhysicPiercing(this->getThePhysicPiercing());
        pElement->setMagicPiercing(this->getTheMagicPiercing());
        pElement->setManaCost(this->getManaCost());
        pElement->setHpCost(this->getHpCost());
        pElement->setSpCost(this->getSpCost());
        pElement->setCoolDown(this->getCoolDown());
        pElement->setPhysicCrit(this->getThePhysicCrit());
        pElement->setMagicCrit(this->getTheMagicCrit());
        pElement->setDescription(this->getDescription());
        return pElement;
    }

    CC_SAFE_DELETE(pElement);
    return nullptr;
}

void SkillStatics::autoCoolDown()
{
    if(m_nCurrentCoolDown < m_nCoolDown)
    {
        m_nCurrentCoolDown++;
    }
}

void SkillStatics::castSkill()
{
    this->m_nCurrentCoolDown = 0;
}

bool SkillStatics::isReady()
{
    if(m_nCoolDown == 0) return true;
    if(m_nCurrentCoolDown == m_nCoolDown) return true;
    return false;
}

void SkillStatics::merge(SkillStatics* target)
{
    if(target)
    {
        this->m_fPhysicDmg = target->m_fPhysicDmg;
        this->m_fMagicDmg = target->m_fMagicDmg;

        this->m_fPureDmg = target->m_fPureDmg;

        this->m_cPhysicCrit = target->m_cPhysicCrit;
        this->m_cMagicCrit = target->m_cMagicCrit;

        this->m_nCoolDown = target->m_nCoolDown;
        this->m_nCurrentCoolDown = target->m_nCurrentCoolDown;

        this->m_cPhysicPie = target->m_cPhysicPie;
        this->m_cMagicPie = target->m_cMagicPie;

        this->m_fMnCost = target->m_fMnCost;
        this->m_fHpCost = target->m_fHpCost;
        this->m_fSpCost = target->m_fSpCost;

        this->m_sDescription = target->m_sDescription;
    }
}