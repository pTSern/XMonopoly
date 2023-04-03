#pragma once

#include "ZyUwU/ZyUwU.h"
#include "Skill/SkillInGame/SkillInGame.h"
#include "ChampionInGame/ChampionInGame.h"
#include "Skill/SkillManager/SkillManager.h"

struct SkillRequirement
{
public:
    int g_nCastRange_F;                    ///< the cast range of the skill in arena index follow the head dir of the caster
    int g_nCastRange_B;                    ///< the cast range of the skill in arena index follow the opposite head dir of the caster
    int g_nAreaEffect_F;                   ///< the area effect of the skill in arena index follow the head dir of the caster
    int g_nAreaEffect_B;                   ///< the area effect of the skill in arena index follow the opposite head dir of the caster
    int g_nTargetNum;                      ///< the number of target
};

class SkillMechanic
{
public:
    virtual void callback(float dt) = 0;
    virtual void autoGetTarget() = 0;
    void setOwner(SkillInGame* pSkill);

protected:
    SkillMechanic();
    virtual ~SkillMechanic();

protected:
    ///] Must declare
    SkillInGame *m_pOwner;              ///< weak reference to the owner of this mechanic
    SkillRequirement *m_pRequirement;   ///< pointer storage the requirement of the skill

    ///] Auto declare
    ChampionInGame *m_pCaster;          ///< weak reference to the caster of this mechanic
};

////////////////////////////////////////////////////////////////////////

BEGIN_CREATE_REFCLASS(Projectile, GameObject)

public:
    enum class ProjectileType
    {
        END_POINT,
        NUMBER
    };

public:
    virtual ~Projectile();
    virtual void update(float dt);

protected:
    int m_nMoveDistance;
    SkillStatics *m_pAddition;
    int m_nStartPoint;
    HeadDir m_eDir;
    ProjectileType m_eType;

END_CREATE_REFCLASS

////////////////////////////////////////////////////////////////////////

class ShootProjectile : public SkillMechanic
{
public:

public:
    virtual void callback(float dt);
    virtual void autoGetTarget();

protected:
    ShootProjectile();
    virtual ~ShootProjectile();

protected:
    std::vector<Projectile*> m_vProjectiles;
};

class Toggle : public SkillMechanic
{
public:
    virtual void callback(float dt);
    virtual void autoGetTarget();

protected:
    SkillStatics *m_pAddition;
};

class Moving : public SkillMechanic
{
public:
    virtual void callback(float dt);
    virtual void autoGetTarget();

};