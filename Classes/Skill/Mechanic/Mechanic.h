#pragma once

#include "ZyUwU/ZyUwU.h"
#include "Skill/SkillInGame/SkillInGame.h"
#include "ChampionInGame/ChampionInGame.h"
#include "Skill/SkillManager/SkillManager.h"
#include "GameMaster/GameMaster.h"
#include "Map/Map.h"
#include "Support/GameConstant.h"

struct SkillRequirement
{
public:
    int g_nCastRange_F;                    ///< the cast range of the skill in arena index follow the head dir of the caster
    int g_nCastRange_B;                    ///< the cast range of the skill in arena index follow the opposite head dir of the caster
    int g_nAreaEffect_F;                   ///< the area effect of the skill in arena index follow the head dir of the caster
    int g_nAreaEffect_B;                   ///< the area effect of the skill in arena index follow the opposite head dir of the caster
    int g_nTargetNum;                      ///< the number of target
};

class SkillMechanic : public Node
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

class Projectile : public GameObject
{
#define INFINITE_TARGET -1
public:
    static Projectile* createPiercingProjectile(const std::string& texture, ChampionInGame* caster, int distance, HeadDir dir);
    static Projectile* createHitNumberProjectile(const std::string& texture, ChampionInGame* caster, int distance, int numberTarget, HeadDir dir);
    static Projectile* createSingleTargetProjectile(const std::string& texture, ChampionInGame* caster, int distance, HeadDir dir);

public:
    Projectile();
    virtual ~Projectile();
    virtual bool init();
    virtual void log();
    virtual std::string toString(int nTab = 2);
    virtual void update(float dt);
    virtual void contactTo(PhysicsContact& contact, GameObject* target) override;
    virtual void contactBy(PhysicsContact& contact, GameObject* target) override;

protected:
    bool initWithProperties(const std::string& texture, ChampionInGame* caster, int distance, int targetNum, HeadDir dir);
    void initPhysicBody();
    void initSprite(const std::string& texture);

    void destruct();
    void collideTargetChecker();

    void flyTo(Point pos);
    void flyTo(Coordinate coord);
    void flyToNextCoord();
    void endFly();
    void flyTo(Arena* arena);

    void autoRotate();
    void updatePhysicBody();
    void hitTarget(ChampionInGame* target);


protected:
    int m_nMoveDistance;
    //int m_nStartPoint, m_nEndPoint;
    HeadDir m_eDir;

    int m_nHitTarget, m_nNumberTarget;
    int m_nFlewTime;
    Coordinate m_coord;
    ZYSprite* m_pProjectile;

    Point m_differentVec2;

    bool m_bIsFinish;
    ChampionInGame* m_pCaster;

private:
    const std::string p_sClassName = "Projectile";
};

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
    int m_nProjectileNum;
    int m_nCreatedNum;
    float m_fDelayEachTimeCreateProjectile;

    std::string m_sProjectileTexture;
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