#pragma once

#include "ZyUwU/ZyUwU.h"
#include "Support/GameConstant.h"
#include "GameObject/GameObject.h"
#include "Support/Coordinate.h"

USING_NS_ALL;

class MechanicManager;
class SkillManager;
class SkillInGame;
class ChampionInGame;
class MapManager;
class GameMaster;
enum class HeadDir;
class Arena;
class SkillStatics;

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
    void setOwner(MechanicManager* owner);
    CREATE_GET_FUNC(getCaster, ChampionInGame*, m_pCaster);
    CREATE_GET_FUNC(getOwner, MechanicManager*, m_pOwner);

    void markProjectileToRemove(GameObject* object);
    virtual void call()
    {
        scheduleUpdate();
    }
    virtual void end()
    {
        unscheduleUpdate();
    }

    CREATE_GET_FUNC(getIsFinish, bool, m_bIsFinish);

protected:
    SkillMechanic();
    virtual ~SkillMechanic();

protected:
    ///] Must declare
    MechanicManager *m_pOwner;          ///< weak reference to the owner of this mechanic
    SkillRequirement *m_pRequirement;   ///< pointer storage the requirement of the skill

    ///] Auto declare
    ChampionInGame *m_pCaster;          ///< weak reference to the caster of this mechanic

    std::vector<GameObject*> m_vMarkedList;
    bool m_bIsFinish = false;
};

////////////////////////////////////////////////////////////////////////

class Projectile : public GameObject
{
#define INFINITE_TARGET -1
public:
    static Projectile* createPiercingProjectile(const std::string& texture, SkillMechanic* owner, int distance, HeadDir dir);
    static Projectile* createHitNumberProjectile(const std::string& texture, SkillMechanic* owner, int distance, int numberTarget, HeadDir dir);
    static Projectile* createSingleTargetProjectile(const std::string& texture, SkillMechanic* owner , int distance, HeadDir dir);

public:
    Projectile();
    virtual ~Projectile();
    virtual bool init() override;
    virtual void log() override;
    virtual std::string toString(int nTab = 2) override;
    virtual void update(float dt) override;
    virtual void contactTo(PhysicsContact& contact, GameObject* target) override;
    virtual void contactBy(PhysicsContact& contact, GameObject* target) override;

public:
    CREATE_GET_FUNC(isFinish, bool, m_bIsFinish);

protected:
    bool initWithProperties(const std::string& texture, SkillMechanic* owner, int distance, int targetNum, HeadDir dir);

    void initPhysicBody();
    void initSprite(const std::string& texture);

    void destruct(float dt);
    void preDestruct();
    void collideTargetChecker();

    void flyTo(Point pos);
    void flyTo(Coordinate coord);
    void flyToNextCoord();
    void endFly();
    void flyTo(Arena* arena);

    void autoRotate();
    void updatePhysicBody();
    void hitTarget(ChampionInGame* target);

    void hitTargetAnimation(ChampionInGame* target);

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

    SkillMechanic* m_pOwner;

    bool m_bBlockUpdate;

private:
    const std::string p_sClassName = "Projectile";

};

////////////////////////////////////////////////////////////////////////

class ShootProjectile : public SkillMechanic
{
public:
    static ShootProjectile* create(int projectileNum, const std::string& projectileTexture, int distance, float delay);

public:
    ShootProjectile();

    virtual void callback(float dt){}
    virtual void autoGetTarget();
    virtual bool initWithProperties(int projectileNum, const std::string& projectileTexture, int distance, float delay);
    virtual void update(float dt);
    virtual void call();
    virtual void end();

    void cleanupLoop(float dt);
protected:
    virtual ~ShootProjectile();

protected:
    std::vector<Projectile*> m_vList;

    float m_fDelay;
    std::string m_sProjectileTexture;
    int m_nDistance, m_nProjectileNum;
    int m_nTargetNum;

    int m_nCleanNum = 0;
};

class Toggle : public SkillMechanic
{
public:
    virtual void callback(float dt) override {};
    virtual void autoGetTarget() override {};

protected:
    SkillStatics *m_pAddition;
};

class Moving : public SkillMechanic
{
public:
    static Moving* create();

public:
    virtual bool initWithProperties(MechanicManager* owner);
    virtual void callback(float dt) override {}
    virtual void autoGetTarget() override {};
    virtual void update(float dt) override;
    virtual void call() override;

};

class FooCallback : public SkillMechanic
{
public:
    typedef std::function<void(SkillMechanic*)> FooMechanicCallback;

public:
    static FooCallback* create();

public:
    virtual bool initWithProperties(MechanicManager* owner);
    virtual void callback(float dt) override {}
    virtual void autoGetTarget() override {};
    virtual void update(float dt) override;
    virtual void call() override;
    virtual void end() override;

public:
    static void HealingOnTrigger(SkillMechanic* mechanic);
    static void ForceEndTurn(SkillMechanic* mechanic);

public:
    CREATE_SET_FUNC(setOnTriggerCallback, const FooMechanicCallback&, m_oOnTrigger);
    CREATE_SET_FUNC(setEndTriggerCallback, const FooMechanicCallback&, m_oEndTrigger);
    CREATE_SET_FUNC(setLoopCallback, const FooMechanicCallback&, m_oLoop);

protected:
    FooMechanicCallback m_oOnTrigger, m_oEndTrigger, m_oLoop;

};