#include "Extension.h"

/////v PERCENT STATICS

///] Public

PercentStatics::PercentStatics(float fAmount)
{
    this->m_fAmount = fAmount;
}

std::string PercentStatics::toString(int nTab)
{
    std::string ts;
    std::string tab = ZY_SP_TAB(nTab);
    ts += (tab + " + Amount: " + ZY_SP_NUMBER_TO_STRING(this->m_fAmount));
    ts += (tab + " + Amount in percent: " + ZY_SP_NUMBER_TO_STRING(this->getPcAmount()) + "%");

    return ts;
}

void PercentStatics::addAmount(float fAmount)
{
    m_fAmount += fAmount;
}

void PercentStatics::reduceAmount(float fAmount)
{
    m_fAmount -= fAmount;
    if(m_fAmount < 0) m_fAmount = 0;
}

//// REGEN STATICS

RegenStatics::RegenStatics(float fAmount, float fRegen)
{
    this->m_fAmount = fAmount;
    this->m_fRegen = fRegen;
}

std::string RegenStatics::toString(int nTab)
{
    std::string ts;
    std::string tab = ZY_SP_TAB(nTab);
    ts += (tab + " + Amount: " + ZY_SP_NUMBER_TO_STRING(this->m_fAmount));
    ts += (tab + " + Regen: " + ZY_SP_NUMBER_TO_STRING(this->m_fRegen));
    return ts;
}

//// CRIT STATICS

CritStatics::CritStatics(float fDmgMultiple, float fRate)
{
    this->m_fDmgMultiple = fDmgMultiple;
    this->m_cRate = PercentStatics(fRate);
}

std::string CritStatics::toString(int nTab)
{
    std::string ts;
    std::string tab = ZY_SP_TAB(nTab);
    ts += (tab + " + Damage Multiple: " + ZY_SP_NUMBER_TO_STRING(m_fDmgMultiple));
    ts += m_cRate.toString(nTab + 1);
    return ts;
}