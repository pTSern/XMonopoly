#pragma once

#include "ZyUwU/ZyUwU.h"
#include "Support/GameConstant.h"
#include "ui/UIButton.h"

USING_NS_ALL;

#define GM_GI GameMaster::getInstance()

class MapManager;
class ChampionInGame;
class Player;
class MapManager;
class PlayerUI;
BEGIN_CREATE_INSTANCE_REFCLASS(GameMaster, Node)

public:
    //virtual ~GameMaster();

public:
    void setIsTurnChampion(ChampionInGame* champion);
    void markChampion();
    void update(float dt);
    void calculateNewTurn();
    void revoke();
    void addChampList(std::vector<ChampionInGame*> list);
    void endGame(bool bIsClient);
    void setRunningScene(Scene* var , Layer* layer,ui::Widget::ccWidgetTouchCallback callback);
    void floatingNotify(const std::string& message, const TTFConfig& ttf, const Color3B& color, const Point& position, const float& duration = 1.0f, bool isLock = false);
    void setClientPlayer(Player* target);

    CREATE_GET_FUNC(getClientPlayer, Player*, m_pClient);
    CREATE_SET_GET_FUNC(setMap, getMap, MapManager*, m_pMap);
    //CREATE_GET_FUNC(getClientUI, PlayerUI*, m_pClientUI);

protected:
    ZYSprite* m_pMarkIsTurnChampion_UP, * m_pMarkIsTurnChampion_DOWN;
    ChampionInGame* m_pIsTurnChampion;
    std::vector<ChampionInGame*> m_vList;
    int m_nChampionIsTurnIndex;
    int m_nRound;
    Scene* m_pRunningScene;
    Layer* m_pBattleLayer;
    ui::Widget::ccWidgetTouchCallback m_pEndGameCallback;
    Player* m_pClient;
    MapManager* m_pMap;

    PlayerUI* m_pClientUI;

private:
    bool p_bLockEndGame;

END_CREATE_INSTANCE_REFCLASS;
