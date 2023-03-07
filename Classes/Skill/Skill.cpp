#include "Skill.h"
#include "SkillCard/SkillCard.h"

//// Constructor

Skill::Skill() :
m_pSkillStatics(nullptr),
m_pSkillCard(nullptr),
//m_pTargets(nullptr),
m_pCondition(nullptr),
m_eType(SkillType::ACTIVE),
m_eTarget(TargetType::NONE)
{

}

Skill::~Skill()
{
    CC_SAFE_DELETE(m_pSkillStatics);
    CC_SAFE_RELEASE(m_pSkillCard);
}

//// Static

Skill* Skill::createWithProperties(XProperties *pProperties, SkillStatics *pStatics, SkillCard *card, bool bIsClone, bool bIsClean)
{
    auto ret = Skill::create();
    if(ret && pProperties && pStatics && card)
    {
        ret->setProperties(pProperties, bIsClone, bIsClean);
        ret->setStatics(pStatics, bIsClone, bIsClean);
        ret->setSkillCard(card);
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//// Virtual

bool Skill::init()
{
    return true;
}

void Skill::update(float dt)
{

}

void Skill::log()
{
    ZY_EZ_LOG;
}

std::string Skill::toString(int nTab)
{
    std::string ts = GameObject::toString(nTab);
    std::string tab = ZY_SP_TAB(nTab);
    ZY_TSHP(ts, tab, nTab, " > Skill Statics: ", m_pSkillStatics);
    ZY_TSHP(ts, tab, nTab, " > Skill Card: ", m_pSkillCard);
    return ts;
}