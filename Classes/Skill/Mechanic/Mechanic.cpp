#include "Mechanic.h"
#include "Arena/Arena.h"

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
m_nFlewTime(0), m_nMoveDistance(0),
m_eDir(),
m_nHitTarget(0), m_nNumberTarget(0),
m_pProjectile(nullptr), m_pCaster(nullptr),
//m_nStartPoint(0), m_nEndPoint(0),
m_coord(Coordinate::UNKNOWN),
m_bIsFinish(false)
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
    auto ret = new (std::nothrow) Projectile();
    if(ret && ret->initWithProperties(texture, caster, distance, numberTarget, dir))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

Projectile* Projectile::createSingleTargetProjectile(const std::string& texture, ChampionInGame* caster, int distance, HeadDir dir)
{
    auto ret = new (std::nothrow) Projectile();
    if(ret && ret->initWithProperties(texture, caster, distance, 1, dir))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

Projectile::~Projectile()
{
    ZY_EZ_DE_LOG;
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
    autoRotate();
    //collideTargetChecker();
    updatePhysicBody();
}

void Projectile::updatePhysicBody()
{
    m_pPhysicBody->setPositionOffset(m_pProjectile->getPosition());
    m_pPhysicBody->setRotationOffset(m_pProjectile->getRotation());
}

void Projectile::contactTo(PhysicsContact& contact, GameObject* target)
{
    auto champ = dynamic_cast<ChampionInGame*>(target);
    if(champ && champ != m_pCaster)
    {
        m_nHitTarget++;
        hitTarget(champ);
        collideTargetChecker();
    }
}

void Projectile::hitTarget(ChampionInGame* target)
{
    // Do animation

    // Do be attacked
}

void Projectile::contactBy(PhysicsContact& contact, GameObject* target)
{
    // Do nothing
}

///] Protected

void Projectile::collideTargetChecker()
{
    if(m_nNumberTarget == INFINITE_TARGET) return;
    if(m_nHitTarget == m_nNumberTarget)
    {
        destruct();
    }
}

void Projectile::autoRotate()
{
    int x = 1;
    auto coord = (int)m_coord.g_nIndex;
    if (coord < 0) x = -1;

    float deg = 0;
    if((int)m_eDir < 0) deg = -180.0f;

    switch (m_coord.g_eDir) {
        case Dir::NE:
            m_pProjectile->setRotation((180 + GM_GI->getMap()->getAngleHorizon()) + deg);
            break;

        case Dir::ES:
            m_pProjectile->setRotation((360 - GM_GI->getMap()->getAngleHorizon()) + deg);
            break;

        case Dir::WS:
            m_pProjectile->setRotation(GM_GI->getMap()->getAngleHorizon() + deg);
            break;

        case Dir::NW:
            m_pProjectile->setRotation((180 -  GM_GI->getMap()->getAngleHorizon()) + deg);
            break;
    }
}

bool Projectile::initWithProperties(const std::string& texture, ChampionInGame *caster,
                                    int distance, int targetNum, HeadDir dir)
{
    ZYASSERT_BREAK(CC_FILEUTILS_GI->isFileExist(texture), "Call Projectile::initWithProperties with blank resource file name", false);
    ZYASSERT_BREAK(caster, "Call Projectile::initWithProperties with nullptr caster", false);
    ZYASSERT_BREAK(distance >= 0, "Call Projectile::initWithProperties with invalid distance", false);

    this->initSprite(texture);

    ///v Init all properties
    this->setName(p_sClassName);

    this->m_pCaster = caster;
    auto startPoint = caster->getPosition();
    this->m_coord = caster->getCoordinate();
    this->m_eDir = dir;

    this->m_differentVec2 = startPoint - caster->getLandingArena()->getCentralPoint();
    this->m_nMoveDistance = distance;

    this->m_nNumberTarget = targetNum;
    ///^ End init all properties

    this->initPhysicBody();

    this->flyToNextCoord();

    this->scheduleUpdate();
    return true;
}

void Projectile::initSprite(const std::string& texture)
{
    m_pProjectile = ZYSprite::create(texture);
    this->addChild(m_pProjectile);
}

void Projectile::initPhysicBody()
{
    m_pPhysicBody = PhysicsBody::createBox(m_pProjectile->getContentSize());
    m_pPhysicBody->setDynamic(false);
    m_pPhysicBody->setGravityEnable(false);
    m_pPhysicBody->setContactTestBitmask(GM_GI->getBitMask());
    this->setPhysicsBody(m_pPhysicBody);
}

void Projectile::flyTo(Point pos)
{
    auto move_to = MoveTo::create(projectile_move_time, pos);
    auto callback = CallFunc::create(CC_CALLBACK_0(Projectile::endFly, this));
    auto seq = Sequence::create(move_to, callback, nullptr);

    m_pProjectile->runAction(seq);
}

void Projectile::flyTo(Coordinate coord)
{
    auto a = GM_GI->getMap()->getArenaByCoord(coord);
    m_coord = a->getCoordinate();
    flyTo(a);
}

void Projectile::flyTo(Arena* arena)
{
    flyTo(arena->getCentralPoint() + m_differentVec2);
}

void Projectile::flyToNextCoord()
{
    m_coord.moveIndex((int)m_eDir);
    m_nFlewTime ++;
    flyTo(m_coord);
}

void Projectile::endFly()
{
    if(m_nMoveDistance == m_nFlewTime)
    {
        CCLOG("END FLY");
        destruct();
    }
    else if(m_nFlewTime < m_nMoveDistance)
    {
        flyToNextCoord();
    }
}

void Projectile::destruct()
{
    m_pProjectile->setVisible(false);
    //m_pProjectile->removeFromParentAndCleanup(true);
    //unscheduleUpdate();
    //removeFromParentAndCleanup(true);
}

///////////////////////////////

///] Constructor

ShootProjectile::ShootProjectile()
{
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