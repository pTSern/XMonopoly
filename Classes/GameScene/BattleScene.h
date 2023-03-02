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

protected:
    std::vector<Player*> m_vPlayers;
};