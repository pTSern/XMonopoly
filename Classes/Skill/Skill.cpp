#include "Skill.h"
#include "SkillCard/SkillCard.h"

//// Constructor

Skill::Skill() :
m_pSkillStatics(nullptr),
m_pSkillCard(nullptr)
{

}

Skill::~Skill()
{
    CC_SAFE_DELETE(m_pSkillStatics);
    CC_SAFE_RELEASE(m_pSkillCard);
}

//// Public

//Static

Skill* Skill::createWithProperties(XProperties *pProperties, SkillStatics *pStatics, bool bIsClone, bool bIsClean)
{
    auto ret = Skill::create();
    if(ret)
    {
        ret->setProperties(pProperties, bIsClone, bIsClean);
        ret->setStatics(pStatics, bIsClone, bIsClean);

        return ret;
    }
    CC_SAFE_DELETE(pProperties);
    CC_SAFE_DELETE(pStatics);
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//Virtual

bool Skill::init()
{
    m_pSkillStatics = SkillStatics::create();
    m_pSkillCard = SkillCard::create();

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