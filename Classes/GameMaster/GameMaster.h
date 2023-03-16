#pragma once

#include "ZyUwU/ZyUwU.h"
#include "Support/GameConstant.h"
#include "ui/UIButton.h"

USING_NS_ALL;

#define GM_GI GameMaster::getInstance()

class MapManager;
class ChampionInGame;
BEGIN_CREATE_INSTANCE_REFCLASS(GameMaster, Node)

public:
    void setIsTurnChampion(ChampionInGame* champion);
    void markChampion();
    void update(float dt);
    void revoke();
    void calculateNewTurn();
    void addChampList(std::vector<ChampionInGame*> list);
    void endGame(const std::string& loser);
    void setRunningScene(Scene* var , Layer* layer,std::function<void(Ref*)> callback);

protected:
    ZYSprite* m_pMarkIsTurnChampion_UP, * m_pMarkIsTurnChampion_DOWN;
    ChampionInGame* m_pIsTurnChampion;
    std::vector<ChampionInGame*> m_vList;
    int m_nChampionIsTurnIndex;
    int m_nRound;
    Scene* m_pRunningScene;
    Layer* m_pBattleLayer;
    std::function<void(Ref*)> m_pEndGameCallback;

END_CREATE_INSTANCE_REFCLASS;
