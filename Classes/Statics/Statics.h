#pragma once

#include "Extension.h"
#include "../ZyUwU/ZyUwU.h"

BEGIN_CREATE_CLASS(Statics)
public:
    static Statics* createWithProperties(float fAttackDmg = 0, float fMagicDmg = 0, float fArmor = 0,
                                         int nLife = 1, float speed = 1, float fMagicRisis = 0, PercentStatics cLifeSteal = 0,
                                         PercentStatics cMagicLifeSteal = 0, RegenStatics cHP = RegenStatics(10, 1), RegenStatics cMana = RegenStatics(10, 1),
                                         RegenStatics cSkillPoint = RegenStatics(10, 1));

    static Statics* clone(Statics *pClone);
public:
    Statics* clone();
    void setProperties(float fAttackDmg = 0, float fMagicDmg = 0, float fArmor = 0,
                       int nLife = 1, float speed = 1,float fMagicRisis = 0, PercentStatics cLifeSteal = 0,
                       PercentStatics cMagicLifeSteal = 0, RegenStatics cHP = 0, RegenStatics cMana = 0,
                       RegenStatics cSkillPoint = 0);
public:
    CREATE_SET_GET_FUNC(setAttackDmg, getAttackDmg, float, m_fAttackDmg);
    CREATE_SET_GET_FUNC(setMagicDmg, getMagicDmg, float, m_fMagicDmg);
    CREATE_SET_GET_FUNC(setLife, getLife, int, m_nLife);
    CREATE_SET_GET_FUNC(setArmor, getArmor, float, m_fArmor);
    CREATE_SET_GET_FUNC(setMagicResistance, getMagicResistance, float, m_fMagicResis);

    CREATE_SET_GET_FUNC(setMagicLifeSteal, getTheMagicLifeSteal, PercentStatics, m_cMagicLifeSteal);
    CREATE_SET_GET_FUNC(setLifeSteal, getTheLifeSteal, PercentStatics, m_cLifeSteal);

    CREATE_SET_GET_FUNC(setMaxHp, getTheHp, RegenStatics, m_cHP);
    CREATE_SET_GET_FUNC(setMaxMana, getTheMana, RegenStatics, m_cMana);
    CREATE_SET_GET_FUNC(setMaxSkillPoint, getTheSkillPoint, RegenStatics, m_cSkillPoint);
    CREATE_SET_GET_FUNC(setSpeed, getSpeed, float, m_fSpeed);

    CREATE_GET_FUNC(getMaxHp, float, m_cHP.getAmount());
    CREATE_GET_FUNC(getMaxMana, float, m_cMana.getAmount());
    CREATE_GET_FUNC(getMaxSkillPoint, float, m_cSkillPoint.getAmount());
    CREATE_GET_FUNC(getRegenHp, float, m_cHP.getRegen());
    CREATE_GET_FUNC(getRegenMana, float, m_cMana.getRegen());
    CREATE_GET_FUNC(getRegenSkillPoint, float, m_cSkillPoint.getRegen());

    CREATE_GET_FUNC(getPCLifeSteal, float, m_cLifeSteal.getPcAmount());
    CREATE_GET_FUNC(getLifeSteal, float, m_cLifeSteal.getAmount());
    CREATE_GET_FUNC(getPCMagicLifeSteal, float, m_cMagicLifeSteal.getPcAmount());
    CREATE_GET_FUNC(getMagicLifeSteal, float, m_cMagicLifeSteal.getAmount());

    inline void setMagicLifeSteal(float fAmount) {this->m_cMagicLifeSteal.setAmount(fAmount);}
    inline void setLifeSteal(float fAmount) {this->m_cLifeSteal.setAmount(fAmount);}

    inline void setMaxHp(float fHp) {this->m_cHP.setAmount(fHp);}
    inline void setRegenHp(float fRegen) {this->m_cHP.setRegen(fRegen);}

    inline void setMaxMana(float fMana) {this->m_cMana.setAmount(fMana);}
    inline void setRegenMana(float fRegen) {this->m_cMana.setRegen(fRegen);}

    inline void setMaxSkillPoint(float fSp) {this->m_cSkillPoint.setAmount(fSp);}
    inline void setRegenSkillPoint(float fRegen) {this->m_cSkillPoint.setRegen(fRegen);}

protected:
    float m_fAttackDmg, m_fMagicDmg;
    int m_nLife;
    float m_fArmor, m_fMagicResis;
    PercentStatics m_cLifeSteal, m_cMagicLifeSteal;
    RegenStatics m_cHP, m_cMana, m_cSkillPoint;
    float m_fSpeed;


END_CREATE_CLASS



//
BEGIN_CREATE_CLASS(ChampionStatics)

public:
    ChampionStatics* clone();

public:
    CREATE_SET_GET_FUNC(setId, getId, int, m_nId);

protected:
    int m_nId;

END_CREATE_CLASS



//
BEGIN_CREATE_CLASS(IngameStatics)

protected:
#define CREATE_ADD_FUNC(__NAME__, __VAR__) \
void __NAME__(float var)                   \
{                                          \
    this->__VAR__ += var;                  \
    this->autoValid();                     \
}                                          \

#define CREATE_REDUCE_FUNC(__NAME__, __VAR__) \
void __NAME__(float var)                      \
{                                             \
    this->__VAR__ -= var;                     \
    if(this->__VAR__ < 0) this->__VAR__ = 0;  \
}                                             \

public:
    static IngameStatics* createWithStatics(Statics* pStatics, bool bIsClone = true, bool bIsClean = false);
    static IngameStatics* createTest();

public:
    CREATE_CLONE_SET_FUNC(setStatics, Statics, m_pStatics);

    void setCurrentHp(float fHp) {this->m_fCurrentHp = fHp;}
    void setCurrentMana(float fMana) {this->m_fCurrentMana = fMana;}
    void setCurrentSp(float fSp) {this->m_fCurrentSp = fSp;}

    void fillStatics(float percent);
    void fillHp(float percent);
    void fillMana(float percent);
    void fillSp(float percent);
    void autoValid();

    IngameStatics* clone();


public:
    inline Statics* getStatics() {return this->m_pStatics;}
    inline float getCurrentHp() {return this->m_fCurrentHp;}
    inline float getCurrentMana() {return this->m_fCurrentMana;}
    inline float getCurrentSp() {return this->m_fCurrentSp;}

    CREATE_GET_FUNC(getCurrentHpInPercent, float, m_fCurrentHp/m_pStatics->getMaxHp());
    CREATE_GET_FUNC(getCurrentMnInPercent, float, m_fCurrentMana/m_pStatics->getMaxMana());
    CREATE_GET_FUNC(getCurrentSpInPercent, float, m_fCurrentSp/m_pStatics->getMaxSkillPoint());
    CREATE_GET_FUNC(isAlive, bool, m_fCurrentHp > 0);

    CREATE_ADD_FUNC(addMana, m_fCurrentMana);
    CREATE_ADD_FUNC(addSp, m_fCurrentSp);
    void addHp(float amount);

    CREATE_REDUCE_FUNC(reduceMana, m_fCurrentMana);
    CREATE_REDUCE_FUNC(reduceSp, m_fCurrentSp);
    void reduceHp(float var);

    bool reduceLife(int num = 1);
    void addLife(int num = 1);
    void regen(float multiple = 0);

    void reduceHpEqualToPercentOfMaxHp(float percent, bool isDecimal = false);
    void reduceManaEqualToPercentOfMaxMana(float percent, bool isDecimal = false);
    void reduceSpEqualToPercentOfMaxSp(float percent, bool isDecimal = false);

    bool doRespawn(const float percent = 100);

protected:
    Statics *m_pStatics;
    float m_fCurrentHp, m_fCurrentMana, m_fCurrentSp;
    int m_nCurrentLife;

private:
    bool p_bStopHealing;

END_CREATE_REFCLASS