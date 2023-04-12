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
m_cHP(100,0),
m_cMana(100,0),
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
                       int nLife, float speed,float fMagicRisis, PercentStatics cLifeSteal,
                       PercentStatics cMagicLifeSteal, RegenStatics cHP, RegenStatics cMana,
                       RegenStatics cSkillPoint)
{
    auto pElement = Statics::create();
    if(pElement)
    {
        pElement->setProperties(fAttackDmg, fMagicDmg, fArmor, nLife, speed, fMagicRisis, cLifeSteal, cMagicLifeSteal, cHP, cMana, cSkillPoint);
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

        pElement->setSpeed(this->getSpeed());

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
                   int nLife, float speed, float fMagicRisis, PercentStatics cLifeSteal,
                   PercentStatics cMagicLifeSteal, RegenStatics cHP, RegenStatics cMana,
                   RegenStatics cSkillPoint)
{

    this->m_fAttackDmg = fAttackDmg;
    this->m_fMagicDmg = fMagicDmg;
    this->m_fArmor = fArmor;
    this->m_nLife = nLife;
    this->m_fMagicResis = fMagicRisis;
    this->m_fSpeed = speed;

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
m_pStatics(nullptr),
m_fCurrentHp(1),
m_fCurrentSp(1),
m_fCurrentMana(1),
p_bStopHealing(false),
m_nCurrentLife(1)
{

}

//// Static

IngameStatics* IngameStatics::createWithStatics(Statics* pStatics, bool bIsClone, bool bIsClean)
{
    auto ret = new (std::nothrow) IngameStatics();
    if(ret && ret->init() && pStatics)
    {
        //ret->autorelease();
        ret->setStatics(pStatics->clone());
        ret->fillStatics(100);
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

IngameStatics* IngameStatics::createTest()
{
    auto ret = new (std::nothrow) IngameStatics();
    ret->m_pStatics = Statics::createWithProperties(35, 0 ,0,1,1,0,0,0,RegenStatics(100, 5), RegenStatics(20, 2), RegenStatics(1,1));
    ret->fillStatics(100);
    return ret;
}

//// public

void IngameStatics::fillStatics(float percent)
{
    if(percent > 100) percent = 100;
    if(percent < 0) percent = 0;
    auto double_percent = percent/100;
    m_fCurrentSp = m_pStatics->getMaxSkillPoint() * double_percent;
    m_fCurrentHp = m_pStatics->getMaxHp() * double_percent;
    m_fCurrentMana = m_pStatics->getMaxMana() * double_percent;
}

void IngameStatics::fillHp(float percent)
{
    if(percent > 100) percent = 100;
    if(percent < 0) percent = 0;
    auto double_percent = percent/100;
    m_fCurrentHp = m_pStatics->getMaxHp() * double_percent;
}

void IngameStatics::fillMana(float percent)
{
    if(percent > 100) percent = 100;
    if(percent < 0) percent = 0;
    auto double_percent = percent/100;
    m_fCurrentMana = m_pStatics->getMaxMana() * double_percent;
}

bool IngameStatics::reduceLife(int num)
{
    if(m_nCurrentLife <= 1) return false;
    this->m_nCurrentLife-=num;
    CCLOG("CURRENT LIFE: %d", m_nCurrentLife);
    return true;
}

void IngameStatics::addLife(int num)
{
    this->m_nCurrentLife+=num;
}

void IngameStatics::regen(const float multiple)
{
    if(p_bStopHealing) return;
    this->m_fCurrentHp += m_pStatics->getRegenHp() * (1.0f + multiple);
    this->m_fCurrentSp += m_pStatics->getRegenSkillPoint() * (1.0f + multiple);
    this->m_fCurrentMana += m_pStatics->getRegenMana() * (1.0f + multiple);
    this->autoValid();
}

bool IngameStatics::doRespawn(float percent)
{
    if(reduceLife())
    {
        this->fillStatics(percent);
        p_bStopHealing = false;
        return true;
    }
    return false;
}

void IngameStatics::fillSp(float percent)
{
    if(percent > 100) percent = 100;
    if(percent < 0) percent = 0;
    auto double_percent = percent/100;
    m_fCurrentSp = m_pStatics->getMaxSkillPoint() * double_percent;
}

void IngameStatics::autoValid()
{
    if(m_fCurrentSp > m_pStatics->getMaxSkillPoint()) m_fCurrentSp = m_pStatics->getMaxSkillPoint();
    if(m_fCurrentHp > m_pStatics->getMaxHp()) m_fCurrentHp = m_pStatics->getMaxHp();
    if(m_fCurrentMana > m_pStatics->getMaxMana()) m_fCurrentMana = m_pStatics->getMaxMana();
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

void IngameStatics::reduceHp(float var)
{
    this->m_fCurrentHp -= var;
    if(m_fCurrentHp <= 0)
    {
        this->m_fCurrentHp = 0;
        p_bStopHealing = true;
    }
}

void IngameStatics::addHp(float amount)
{
    if(p_bStopHealing) return;
    m_fCurrentHp += amount;
    autoValid();
}

void IngameStatics::reduceHpEqualToPercentOfMaxHp(float percent, bool isDecimal)
{
    if(percent < 0) percent = 0;
    auto decimal = percent;
    if(!isDecimal) decimal = zy::Fraction::fastPercent(decimal);

    reduceHp(decimal * m_pStatics->getMaxHp());
}

void IngameStatics::reduceManaEqualToPercentOfMaxMana(float percent, bool isDecimal)
{
    if(percent < 0) percent = 0;
    auto decimal = percent;
    if(!isDecimal) decimal = zy::Fraction::fastPercent(decimal);

    reduceMana(decimal * m_pStatics->getMaxMana());
}

void IngameStatics::reduceSpEqualToPercentOfMaxSp(float percent, bool isDecimal)
{
    if(percent < 0) percent = 0;
    auto decimal = percent;
    if(!isDecimal) decimal = zy::Fraction::fastPercent(decimal);

    reduceSp(decimal * m_pStatics->getMaxSkillPoint());
}

///] Virtual

bool IngameStatics::init()
{
    m_pStatics = Statics::create();
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
