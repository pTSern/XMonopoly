#include "Statics.h"

//Statics


Statics::Statics() :
m_fAttackDmg(0),
m_fMagicDmg(0),
m_nLife(1),
m_fArmor(0),
m_fMagicResis(0),
m_cLifeSteal(0),
m_cMagicLifeSteal(0),
m_cHP(1,0),
m_cMana(1,0),
m_cSkillPoint(1,0)
{

}
bool Statics::init()
{
    return true;
}

Statics* Statics::clone(Statics *pClone)
{
    Statics *pElement = Statics::create();

    if(pElement)
    {
        pElement->setAttackDmg(pClone->getAttackDmg());
        pElement->setMagicDmg(pClone->getMagicDmg());
        pElement->setLife(pClone->getLife());
        pElement->setArmor(pClone->getArmor());
        pElement->setMagicResistance(pClone->getMagicResistance());

        pElement->setLifeSteal(pClone->getTheLifeSteal());
        pElement->setMagicLifeSteal(pClone->getTheMagicLifeSteal());

        pElement->setMaxHp(pClone->getTheHp());
        pElement->setMaxMana(pClone->getTheMana());
        pElement->setMaxSkillPoint(pClone->getTheSkillPoint());

        return pElement;
    }

    CC_SAFE_DELETE(pElement);
    return nullptr;
}

Statics* Statics::createWithProperties(float fAttackDmg, float fMagicDmg, float fArmor,
                       int nLife, float fMagicRisis, PercentStatics cLifeSteal,
                       PercentStatics cMagicLifeSteal, RegenStatics cHP, RegenStatics cMana,
                       RegenStatics cSkillPoint)
{
    auto pElement = Statics::create();
    if(pElement)
    {
        pElement->setProperties(fAttackDmg, fMagicDmg, fArmor, nLife, fMagicRisis, cLifeSteal, cMagicLifeSteal, cHP, cMana, cSkillPoint);
        return pElement;
    }

    CC_SAFE_DELETE(pElement);
    return nullptr;
}
Statics* Statics::clone()
{
    Statics *pElement = Statics::create();

    if(pElement)
    {
        pElement->setAttackDmg(this->getAttackDmg());
        pElement->setMagicDmg(this->getMagicDmg());
        pElement->setLife(this->getLife());
        pElement->setArmor(this->getArmor());
        pElement->setMagicResistance(this->getMagicResistance());

        pElement->setLifeSteal(this->getTheLifeSteal());
        pElement->setMagicLifeSteal(this->getTheMagicLifeSteal());

        pElement->setMaxHp(this->getTheHp());
        pElement->setMaxMana(this->getTheMana());
        pElement->setMaxSkillPoint(this->getTheSkillPoint());

        return pElement;
    }

    CC_SAFE_DELETE(pElement);
    return nullptr;
}

std::string Statics::toString(int nTab)
{
    std::string ts;
    std::string tab = ZY_SP_TAB(nTab);
    ts += (tab + " + Attack Damage: " + ZY_SP_NUMBER_TO_STRING(m_fAttackDmg));
    ts += (tab + " + Magic Damage: " + ZY_SP_NUMBER_TO_STRING(m_fMagicDmg));
    ts += (tab + " + Life: " + ZY_SP_NUMBER_TO_STRING(m_nLife));
    ts += (tab + " + Armor: " + ZY_SP_NUMBER_TO_STRING(m_fArmor));
    ts += (tab + " + Magic Resistance: " + ZY_SP_NUMBER_TO_STRING(m_fMagicResis));
    ts += (tab + " > Life Steal: " + m_cLifeSteal.toString(nTab + 1));
    ts += (tab + " > Magic Life Steal: " + m_cMagicLifeSteal.toString(nTab + 1));
    ts += (tab + " > Heath Point: " + m_cHP.toString(nTab + 1));
    ts += (tab + " > Mana Point: " + m_cMana.toString(nTab + 1));
    ts += (tab + " > Skill Point: " + m_cSkillPoint.toString(nTab + 1));
    return ts;
}

void Statics::setProperties(float fAttackDmg, float fMagicDmg, float fArmor,
                   int nLife, float fMagicRisis, PercentStatics cLifeSteal,
                   PercentStatics cMagicLifeSteal, RegenStatics cHP, RegenStatics cMana,
                   RegenStatics cSkillPoint)
{

    this->m_fAttackDmg = fAttackDmg;
    this->m_fMagicDmg = fMagicDmg;
    this->m_fArmor = fArmor;
    this->m_nLife = nLife;
    this->m_fMagicResis = fMagicRisis;

    this->m_cMagicLifeSteal = cMagicLifeSteal;
    this->m_cLifeSteal = cLifeSteal;

    this->m_cHP = cHP;
    this->m_cMana = cMana;
    this->m_cSkillPoint = cSkillPoint;

}

void Statics::log()
{
    ZY_EZ_LOG;
}

/////// ChampionStatics

ChampionStatics::ChampionStatics() :
m_nId(0)
{

}

//Static

ChampionStatics* ChampionStatics::clone()
{
    auto ret = ChampionStatics::create();
    if(ret)
    {
        ret->m_nId = this->m_nId;
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//Virtual
bool ChampionStatics::init()
{
    return true;
}

void ChampionStatics::log()
{

}

std::string ChampionStatics::toString(int nTab)
{
    std::string ts;
    std::string tab = ZY_SP_TAB(nTab);
    ts += (tab + " + Id: " + ZY_SP_NUMBER_TO_STRING(m_nId));
    return ts;
}

//IngameStatics

IngameStatics::IngameStatics() :
m_pStatics(Statics::create()),
m_fCurrentHp(1),
m_fCurrentSp(1),
m_fCurrentMana(1)
{

}


IngameStatics* IngameStatics::clone()
{
    auto pElement = IngameStatics::create();

    if(pElement)
    {
        pElement->setStatics(this->m_pStatics);
        pElement->setCurrentHp(this->getCurrentHp());
        pElement->setCurrentSp(this->m_fCurrentSp);
        pElement->setCurrentMana(this->getCurrentMana());

        return pElement;
    }

    CC_SAFE_DELETE(pElement);
    return nullptr;

}

//Virtual

bool IngameStatics::init()
{
    return true;
}

void IngameStatics::log()
{
    ZY_EZ_LOG;
}

std::string IngameStatics::toString(int nTab)
{
    std::string ts;
    std::string tab = ZY_SP_TAB(nTab);
    ts += (tab + " + Current Heath Point: " + ZY_SP_NUMBER_TO_STRING(m_fCurrentHp));
    ts += (tab + " + Current Mana: " + ZY_SP_NUMBER_TO_STRING(m_fCurrentMana));
    ts += (tab + " + Current SKill Point: " + ZY_SP_NUMBER_TO_STRING(m_fCurrentSp));
    ts += (tab + " > Statics: " + m_pStatics->toString(nTab + 1));
    return ts;
}
