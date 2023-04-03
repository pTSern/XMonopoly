#include "Mechanic.h"

///] Constructor

SkillMechanic::SkillMechanic() :
m_pOwner(nullptr),
m_pCaster(nullptr),
m_pRequirement(nullptr)
{

}

SkillMechanic::~SkillMechanic()
{
    m_pOwner = nullptr;
    m_pCaster = nullptr;
    CC_SAFE_DELETE(m_pRequirement);
}

void SkillMechanic::setOwner(SkillInGame* pSkill)
{
    if(pSkill)
    {
        this->m_pOwner = pSkill;
        this->m_pCaster = pSkill->getOwner()->getOwner();
    }
}

///////////////////////////////

///] Constructor

Projectile::Projectile() :
m_nMoveDistance(),
m_pAddition(nullptr),
m_eDir()
{

}

///] Virtual

Projectile::~Projectile()
{
    ZY_EZ_DE_LOG;
    CC_SAFE_DELETE(m_pAddition);
}

bool Projectile::init()
{
    return true;
}

void Projectile::log()
{
    ZY_EZ_LOG;
}

std::string Projectile::toString(int nTab)
{
    std::string ts;
    return ts;
}

void Projectile::update(float dt)
{

}

///////////////////////////////

///] Constructor

ShootProjectile::ShootProjectile()
{
    m_vProjectiles.reserve(2);
}

ShootProjectile::~ShootProjectile()
{
}

///] Virtual

void ShootProjectile::callback(float dt)
{

}

void ShootProjectile::autoGetTarget()
{

}