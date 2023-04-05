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
m_eDir(),
m_nHitTarget(0), m_nNumberTarget(0),
m_pProjectile(nullptr),
m_nStartPoint(0), m_nEndPoint(0),
m_startPoint(), m_nLoop(0)
{

}

///] Virtual

Projectile* Projectile::createPiercingProjectile(const std::string& texture, ChampionInGame* caster, int distance, HeadDir dir)
{
    auto ret = new (std::nothrow) Projectile();
    if(ret && ret->initWithProperties(texture, caster, distance, INFINITE_TARGET, dir))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

Projectile* Projectile::createHitNumberProjectile(const std::string& texture, ChampionInGame* caster, int distance, int numberTarget, HeadDir dir)
{

}

Projectile* Projectile::createSingleTargetProjectile(const std::string& texture, ChampionInGame* caster, int distance, HeadDir dir)
{

}

Projectile::~Projectile()
{
    ZY_EZ_DE_LOG;
    CC_SAFE_DELETE(m_pAddition);
    CC_SAFE_DELETE(m_pProjectile);
    unscheduleUpdate();
}

///] Virtual

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

void Projectile::contactTo(PhysicsContact& contact, GameObject* target)
{
    // Only contact to Champion
    auto champ = dynamic_cast<ChampionInGame*>(target);
    if(champ)
    {
        champ->g
    }
}

void Projectile::contactBy(PhysicsContact& contact, GameObject* target)
{
    // Do nothing
}

///] Protected

bool Projectile::initWithProperties(const std::string& texture, ChampionInGame *caster,
                                    int distance, int targetNum, HeadDir dir)
{
    setName(p_sClassName);
    ZYASSERT_BREAK(CC_FILEUTILS_GI->isFileExist(texture), "Call Projectile::initWithProperties with blank resource file name", false);
    ZYASSERT_BREAK(caster, "Call Projectile::initWithProperties with nullptr caster", false);
    ZYASSERT_BREAK(distance >= 0, "Call Projectile::initWithProperties with invalid distance", false);

    m_pProjectile = ZYSprite::create(texture);
    m_nStartPoint = caster->getCoordinate().g_nIndex;
    m_startPoint = caster->getPosition();
    m_eDir = dir;
    m_nHitTarget = 0;
    m_nNumberTarget = targetNum;
    auto num = GM_GI->getMap()->getArenaNumber();
    m_nLoop = distance / num;
    distance %= num;
    m_nEndPoint = ((m_nStartPoint - (m_nStartPoint / num) * num + ((int)dir * distance) % num) + num) % num;

    m_pPhysicBody = PhysicsBody::createBox(m_pProjectile->getContentSize());
    m_pPhysicBody->setDynamic(false);
    m_pPhysicBody->setGravityEnable(false);
    auto p = GM_GI->getBitMask();
    m_pPhysicBody->setContactTestBitmask(p);
    this->setPhysicsBody(m_pPhysicBody);

    return true;
}

void Projectile::autoPathFinder()
{

}

void Projectile::initAction()
{
    auto map = GM_GI->getMap();
    auto w = map->getWCorner();
    auto n = map->getNCorner();
    auto s = map->getSCorner();
    auto e = map->getECorner();

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