#pragma once

#include "cocos2d.h"
#include "../ZyUwU/ZyUwU.h"

#define ARMOR_FORMULA_FACTOR 0.06f
#define ARMOR_FORMULA_BASE 1f

class PercentStatics
{
public:
    PercentStatics(float fAmount = 0);
public:
    std::string toString(int nTab = 2);
    inline void setAmount(float fAmount) {this->m_fAmount = fAmount;}
public:
    inline float getAmount() {return this->m_fAmount;}
    inline float getPcAmount() {return this->m_fAmount/100;}
protected:
    float m_fAmount;
};

class RegenStatics
{
public:
    RegenStatics(float fAmount = 0, float fRegen = 0);
public:
    std::string toString(int nTab = 2);
    inline void setAmount(float fAmount) {this->m_fAmount = fAmount;}
    inline void setRegen(float fRegen) {this->m_fRegen = fRegen;}
public:
    inline float getAmount() {return this->m_fAmount;}
    inline float getRegen() {return this->m_fRegen;}
protected:
    float m_fAmount;
    float m_fRegen;
};

class CritStatics
{
public:
    CritStatics(float fDmgMultiple = 0, float fRate = 0);
public:
    std::string toString(int nTab = 2);
    inline void setDmgMultiple(float fAmount) {this->m_fDmgMultiple = fAmount;}
    inline void setRate(PercentStatics cRate) {this->m_cRate = cRate;}
    inline void setRate(float fRate) {this->m_cRate.setAmount(fRate);}
public:
    inline float getDmgMultiple() {return this->m_fDmgMultiple;}
    inline PercentStatics getTheRate() {return this->m_cRate;}
    inline float getRate() {return this->m_cRate.getPcAmount();}
protected:
    float m_fDmgMultiple;
    PercentStatics m_cRate;
};