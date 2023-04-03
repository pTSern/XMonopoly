#pragma once

#include "ZyUwU/ZyUwU.h"
#include "Player/Player.h"

USING_NS_ALL;

class BattleScene : public Layer
{
public:
    static Scene* createScene();

    virtual bool init();
    void update(float dt);

    ZY_CREATE_FUNC(BattleScene);

    void goToGameOver(Ref* sender);
    void goToMenu(Ref* sender);

    CREATE_SET_FUNC(setPhysicsWorld, PhysicsWorld*, m_pPhysicWorld);
    bool onContactBegin(PhysicsContact& contact);

protected:
    std::vector<Player*> m_vPlayers;
    PhysicsWorld* m_pPhysicWorld;
    EventListenerPhysicsContact* p_pContactListener;
};