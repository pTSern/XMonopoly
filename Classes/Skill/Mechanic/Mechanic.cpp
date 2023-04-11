#include "Mechanic.h"

#include "Arena/Arena.h"
#include "MechanicManager.h"
#include "Dice/Dice.h"
#include "Skill/SkillInGame/SkillInGame.h"
#include "ChampionInGame/ChampionInGame.h"
#include "Skill/SkillManager/SkillManager.h"
#include "GameMaster/GameMaster.h"
#include "Map/Map.h"

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

void SkillMechanic::setOwner(MechanicManager* owner)
{
    if(owner)
    {
        this->m_pOwner = owner;
        this->m_pCaster = owner->getOwner()->getOwner()->getOwner();
    }
}

void SkillMechanic::markProjectileToRemove(GameObject* object)
{
    m_vMarkedList.push_back(object);
}

///////////////////////////////

///] Constructor

Projectile::Projectile() :
m_nFlewTime(0), m_nMoveDistance(0),
m_eDir(),
m_nHitTarget(0), m_nNumberTarget(0),
m_pProjectile(nullptr), m_pOwner(nullptr),
//m_nStartPoint(0), m_nEndPoint(0),
m_coord(Coordinate::UNKNOWN),
m_bIsFinish(false)
{

}

///] Virtual

Projectile* Projectile::createPiercingProjectile(const std::string& texture, SkillMechanic* owner, int distance, HeadDir dir)
{
    auto ret = new (std::nothrow) Projectile();
    if(ret && ret->initWithProperties(texture, owner, distance, INFINITE_TARGET, dir))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

Projectile* Projectile::createHitNumberProjectile(const std::string& texture, SkillMechanic* owner, int distance, int numberTarget, HeadDir dir)
{
    auto ret = new (std::nothrow) Projectile();
    if(ret && ret->initWithProperties(texture, owner, distance, numberTarget, dir))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

Projectile* Projectile::createSingleTargetProjectile(const std::string& texture, SkillMechanic* owner, int distance, HeadDir dir)
{
    auto ret = new (std::nothrow) Projectile();
    if(ret && ret->initWithProperties(texture, owner, distance, 1, dir))
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
    this->autoRotate();
    //collideTargetChecker();
    this->updatePhysicBody();
}

void Projectile::updatePhysicBody()
{
    m_pPhysicBody->setPositionOffset(m_pProjectile->getPosition());
    m_pPhysicBody->setRotationOffset(m_pProjectile->getRotation());
}

void Projectile::contactTo(PhysicsContact& contact, GameObject* target)
{
    auto champ = dynamic_cast<ChampionInGame*>(target);
    if(champ && champ != m_pOwner->getCaster())
    {
        this->hitTarget(champ);
        this->collideTargetChecker();
    }
}

void Projectile::hitTarget(ChampionInGame* target)
{
    m_nHitTarget++;
    hitTargetAnimation(target);
    // Do animation

    // Do be attacked
}

void Projectile::hitTargetAnimation(ChampionInGame* target)
{
    auto key = "pr_exp_v1";
    auto path_plist = "projectile/ani/pr_exp_v1.plist";

    auto sprite = m_pProjectile->clone();
    sprite->setPosition(target->getPosition());
    this->addChild(sprite);

    ///v Block the destruct function call before the animation is finished
    m_bBlockUpdate = true;

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(path_plist);

    auto num = ValidString::numberFrames(path_plist, key);
    auto frames = ValidString::generateFrames(key, num);

    auto animation = Animation::createWithSpriteFrames(frames, animation_dilation_each_frame);
    auto animate = Animate::create(animation);

    ///v Stop blocking destruct function
    auto endBlockFunc = CallFunc::create(
            [&]()
            {
                this->m_bBlockUpdate = false;
            }
            );

    auto seq = Sequence::create(animate, endBlockFunc, RemoveSelf::create(true), nullptr);

    sprite->runAction(seq);
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
        preDestruct();
        schedule(CC_SCHEDULE_SELECTOR(Projectile::destruct));
    }
}

void Projectile::autoRotate()
{
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

bool Projectile::initWithProperties(const std::string& texture, SkillMechanic* owner,
                                    int distance, int targetNum, HeadDir dir)
{
    ZYASSERT_BREAK(CC_FILEUTILS_GI->isFileExist(texture), "Call Projectile::initWithProperties with blank resource file name", false);
    ZYASSERT_BREAK(owner, "Call Projectile::initWithProperties with nullptr owner", false);
    ZYASSERT_BREAK(distance >= 0, "Call Projectile::initWithProperties with invalid distance", false);

    this->initSprite(texture);

    ///v Init all properties
    this->setName(p_sClassName);

    this->m_pOwner = owner;

    auto startPoint = m_pOwner->getCaster()->getPosition();
    this->m_coord = m_pOwner->getCaster()->getCoordinate();
    this->m_eDir = dir;
    m_pProjectile->setPosition(m_pOwner->getCaster()->getPosition());

    this->m_differentVec2 = startPoint - m_pOwner->getCaster()->getLandingArena()->getCentralPoint();
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
        preDestruct();
        schedule(CC_SCHEDULE_SELECTOR(Projectile::destruct));
    }
    else if(m_nFlewTime < m_nMoveDistance)
    {
        flyToNextCoord();
    }
}

void Projectile::destruct(float dt)
{
    if(m_bBlockUpdate) return;
    m_pOwner->markProjectileToRemove(this);
    unschedule(CC_SCHEDULE_SELECTOR(Projectile::destruct));
    //removeFromParentAndCleanup(true);
}

void Projectile::preDestruct()
{
    unscheduleUpdate();
    m_pPhysicBody->removeFromWorld();
    m_pProjectile->stopAllActions();
    m_pProjectile->removeFromParentAndCleanup(true);
}
////////////////////////////////////////////////////////////////////////////

///] Constructor

ShootProjectile::ShootProjectile() :
m_fDelay(0),
m_sProjectileTexture(),
m_nDistance(0), m_nProjectileNum(0), m_nTargetNum(0)
{
}

ShootProjectile::~ShootProjectile() = default;

///] Static

ShootProjectile* ShootProjectile::create(int projectileNum, const std::string& projectileTexture, int distance, float delay)
{
    auto ret = new (std::nothrow) ShootProjectile();

    if(ret && ret->initWithProperties(projectileNum, projectileTexture, distance, delay))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

///] Virtual

bool ShootProjectile::initWithProperties(int projectileNum, const std::string& projectileTexture, int distance, float delay)
{
    this->m_fDelay = delay;
    this->m_sProjectileTexture = projectileTexture;
    this->m_nDistance = distance;
    this->m_nProjectileNum = projectileNum;
    this->m_bIsFinish = false;
    return true;
}

void ShootProjectile::autoGetTarget()
{

}

void ShootProjectile::update(float dt)
{
    if(m_vMarkedList.size() == m_vList.size())
    {
        m_bIsFinish = true;
    }
}

void ShootProjectile::call()
{
    auto delay_pj = DelayTime::create(m_fDelay);
    auto createFunc = CallFunc::create(
            [&]()
            {
                auto pj = Projectile::createSingleTargetProjectile(this->m_sProjectileTexture, this, this->m_nDistance, HeadDir::FRONT);
                this->addChild(pj);
                this->m_vList.push_back(pj);
            }
    );
    auto seq = Sequence::create(createFunc->clone(), delay_pj->clone(), nullptr);
    Vector<FiniteTimeAction*> chain;
    for(int i = 0; i < m_nProjectileNum; i ++)
    {
        chain.pushBack(seq->clone());
    }

    auto call_schedule = CallFunc::create(
            [&]()
            {
                SkillMechanic::call();
            }
            );
    chain.pushBack(call_schedule);
    auto sq = Sequence::create(chain);
    runAction(sq);
}

void ShootProjectile::end()
{
    SkillMechanic::end();
    m_bIsFinish = false;
    m_vList.clear();
    m_vMarkedList.clear();
    m_pOwner->getOwner()->getOwner()->getOwner()->endTurn();
    m_pOwner->getOwner()->getOwner()->getOwner()->getOwner()->finishAction();
}

////////////////////////////////////////////////////////////////////////////

///] Virtual

void Moving::call()
{
    SkillMechanic::call();
}

void Moving::update(float dt)
{
    auto skill = m_pOwner->getOwner();
    auto champ = skill->getOwner()->getOwner();
    auto dice = champ->getDice();
    if(skill->isNeedDice() && dice->isRolled())
    {
        if(champ->isCastingSkill())
        {
            champ->jumpTo(dice->getLastestDiceNum());
        }
    }
}

bool Moving::initWithProperties(MechanicManager* owner)
{
    setOwner(owner);
    return true;
}

///] Static

Moving* Moving::create()
{
    auto ret = new (std::nothrow) Moving();

    if(ret)
    {
        //ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
