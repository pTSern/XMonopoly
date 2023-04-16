#include "../../ZyUwU/ZyUwU.h"
#include "../../Statics/Statics.h"
#include "../../GameObject/GameObject.h"

USING_NS_ALL;

//BEGIN_CREATE_REFCLASS(SkillStatics, cocos2d::Ref)

class SkillStatics
{
private:

#define CREATE_ADD_FUNC_SS(__NAME__, __TYPE__, __VAR__) \
inline void __NAME__(__TYPE__ var)                     \
{                                                       \
    __VAR__ += var;                                     \
}                                                       \

#define CREATE_REDUCE_FUNC_SS(__NAME__, __TYPE__, __VAR__) \
inline void __NAME__(__TYPE__ var)                        \
{                                                          \
    __VAR__ -= var;                                        \
    if(__VAR__ < 0) __VAR__ = 0;                           \
}                                                          \

#define CREATE_ADD_REDUCE_FUNC_SS(__ADD_NAME__, __REDUCE_NAME__, __TYPE__, __VAR__) \
CREATE_ADD_FUNC_SS(__ADD_NAME__, __TYPE__, __VAR__)                                 \
CREATE_REDUCE_FUNC_SS(__REDUCE_NAME__, __TYPE__, __VAR__)                           \


public:
    static SkillStatics* create();
    static SkillStatics* getMerge(SkillStatics* target);

public:
    SkillStatics *clone();

public:
    virtual void log();
    virtual std::string toString(int nTab = 2);

public:
    CREATE_SET_GET_FUNC(setPhysicDmg, getPhysicDmg, float, m_fPhysicDmg);
    CREATE_SET_GET_FUNC(setMagicDmg, getMagicDmg, float, m_fMagicDmg);
    CREATE_SET_GET_FUNC(setPureDmg, getPureDmg, float, m_fPureDmg);

    CREATE_GET_FUNC(getThePhysicPiercing, PercentStatics, m_cPhysicPie);
    CREATE_GET_FUNC(getPhysicPiercing, float, m_cPhysicPie.getAmount());
    CREATE_GET_FUNC(getTheMagicPiercing, PercentStatics, m_cMagicPie);
    CREATE_GET_FUNC(getMagicPiercing, float, m_cMagicPie.getAmount());

    CREATE_SET_GET_FUNC(setCoolDown, getCoolDown, int, m_nCoolDown);
    CREATE_SET_GET_FUNC(setCurrentCooldown, getCurrentCooldown, int, m_nCurrentCoolDown);
    CREATE_SET_GET_FUNC(setManaCost, getManaCost, float, m_fMnCost);
    CREATE_SET_GET_FUNC(setHpCost, getHpCost, float, m_fHpCost);
    CREATE_SET_GET_FUNC(setSpCost, getSpCost, float, m_fSpCost);

    CREATE_GET_FUNC(getThePhysicCrit, CritStatics, m_cPhysicCrit);
    CREATE_GET_FUNC(getPhysicCritRate, float, m_cPhysicCrit.getRate());
    CREATE_GET_FUNC(getPhysicCritDmgMul, float, m_cPhysicCrit.getDmgMultiple());
    CREATE_GET_FUNC(getTheMagicCrit, CritStatics, m_cMagicCrit);
    CREATE_GET_FUNC(getMagicCritRate, float, m_cMagicCrit.getRate());
    CREATE_GET_FUNC(getMagicCritDmgMul, float, m_cMagicCrit.getDmgMultiple());

    CREATE_SET_GET_FUNC(setPhysicPieInNum, getPhysicPieInNum, float, m_fPhysicPie);
    CREATE_SET_GET_FUNC(setMagicPieInNum, getMagicPieInNum, float, m_fMagicPie);

    CREATE_SET_GET_FUNC(setDescription, getDescription, std::string, m_sDescription);

    inline void setPhysicPiercing(PercentStatics cPhysicPie) { this->m_cPhysicPie = cPhysicPie; }
    inline void setPhysicPiercing(float fAmount) { this->m_cPhysicPie.setAmount(fAmount); }
    inline void setMagicPiercing(PercentStatics cMagicPie) { this->m_cMagicPie = cMagicPie; }
    inline void setMagicPiercing(float fAmount) { this->m_cMagicPie.setAmount(fAmount); }
    inline void setPhysicCrit(CritStatics cPhysicCrit) { this->m_cPhysicCrit = cPhysicCrit; }
    inline void setPhysicCritMultiplier(float fAmount) {
        this->m_cPhysicCrit.setDmgMultiple(fAmount);
    }
    inline void setPhysicCritRate(float fAmount) { this->m_cPhysicCrit.setRate(fAmount); }
    inline void setMagicCrit(CritStatics cMagicCrit) { this->m_cMagicCrit = cMagicCrit; }
    inline void setMagicCritMultiplier(float fAmount) {
        this->m_cMagicCrit.setDmgMultiple(fAmount);
    }
    inline void setMagicCritRate(float fAmount) { this->m_cMagicCrit.setRate(fAmount); }
    bool isReady();
    void castSkill();
    void merge(SkillStatics* target);

public:
    CREATE_ADD_REDUCE_FUNC_SS(addPhysicDmg, reducePhysicDmg, float, m_fPhysicDmg);
    CREATE_ADD_REDUCE_FUNC_SS(addMagicDmg, reduceMagicDmg, float, m_fPhysicDmg);
    CREATE_ADD_REDUCE_FUNC_SS(addPureDmg, reducePureDmg, float, m_fPureDmg);

    inline void addPhysicPiercingPercent(float amount)
    {
        m_cPhysicPie.addAmount(amount);
    }
    inline void reducePhysicPiercingPercent(float amount)
    {
        m_cPhysicPie.reduceAmount(amount);
    }
    inline void addMagicPiercingPercent(float amount)
    {
        m_cMagicPie.addAmount(amount);
    }
    inline void reduceMagicPiercingPercent(float amount)
    {
        m_cMagicPie.reduceAmount(amount);
    }

    CREATE_ADD_REDUCE_FUNC_SS(addPhysicPiercingNumber, reducePhysicPiercingNumber, float, m_fPhysicPie);
    CREATE_ADD_REDUCE_FUNC_SS(addMagicPiercingNumber, reduceMagicPiercingNumber, float, m_fMagicPie);

    inline void addPhysicCritRate(float amount)
    {
        m_cPhysicCrit.addRate(amount);
    }
    inline void reducePhysicCritRate(float amount)
    {
        m_cPhysicCrit.reduceRate(amount);
    }
    inline void addMagicCritRate(float amount)
    {
        m_cMagicCrit.addRate(amount);
    }
    inline void reduceMagicCritRate(float amount)
    {
        m_cMagicCrit.reduceRate(amount);
    }
    inline void addPhysicCritMultiple(float amount)
    {
        m_cPhysicCrit.addMultiple(amount);
    }
    inline void addMagicCritMultiple(float amount)
    {
        m_cMagicCrit.addMultiple(amount);
    }
    inline void reducePhysicCritMultiple(float amount)
    {
        m_cPhysicCrit.reduceMultiple(amount);
    }
    inline void reduceMagicCritMultiple(float amount)
    {
        m_cMagicCrit.reduceMultiple(amount);
    }

protected:
    SkillStatics();
    virtual bool init();
    void autoCoolDown();

protected:
    float m_fPhysicDmg, m_fMagicDmg;
    float m_fPureDmg;
    PercentStatics m_cPhysicPie, m_cMagicPie;
    float m_fPhysicPie, m_fMagicPie;
    int m_nCoolDown, m_nCurrentCoolDown;
    float m_fMnCost, m_fHpCost, m_fSpCost;
    CritStatics m_cPhysicCrit, m_cMagicCrit;
    std::string m_sDescription;

private:
    std::string p_sClassName = "SkillStatics";                                      	\
};
//END_CREATE_REFCLASS
