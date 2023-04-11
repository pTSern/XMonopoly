#include "MechanicManager.h"
#include "Mechanic.h"
#include "Skill/SkillInGame/SkillInGame.h"
#include "Skill/SkillManager/SkillManager.h"
#include "ChampionInGame/ChampionInGame.h"

///] Constructor

MechanicManager::MechanicManager() :
m_pMechanic(nullptr), m_pOwner(nullptr)
{

}

///] Static

MechanicManager* MechanicManager::create(SkillInGame *owner, SkillMechanic *mechanic)
{
    auto ret = new (std::nothrow) MechanicManager();
    if(ret && ret->initWithProperties(owner, mechanic))
    {
        ret->autorelease();
        ret->setup();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

///] Virtual

bool MechanicManager::initWithProperties(SkillInGame* owner, SkillMechanic *mechanic)
{
    if(!owner || !mechanic) {
        return false;
    }
    m_pOwner = owner;
    m_pMechanic = mechanic;
    this->addChild(mechanic);
    return true;
}

void MechanicManager::setup()
{
    m_pOwner->setMechanic(this);
    m_pMechanic->setOwner(this);
}

void MechanicManager::onTrigger()
{
    this->schedule(CC_SCHEDULE_SELECTOR(MechanicManager::loop));
    m_pMechanic->call();
}

void MechanicManager::endTrigger()
{
    this->unschedule(CC_SCHEDULE_SELECTOR(MechanicManager::loop));
    //m_pOwner->endTrigger();
    m_pMechanic->end();
}

void MechanicManager::loop(float dt)
{
    if(m_pMechanic->getIsFinish() || !m_pOwner->getOwner()->getOwner()->isTurn())
    {
        endTrigger();
    }
}

/////////////////////////
