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
class Statics;
class SkillStatics;
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
    void floatingNotify(const std::string& message);
    void setClientPlayer(Player* target);
    void generateMap(const std::string& tileMap);

    float attackScene(ChampionInGame* attacker, ChampionInGame* defender, bool isPreCalculate = false);
    float attackScene(ChampionInGame* attacker, std::vector<ChampionInGame*>& defenders);
    const int getAttackIndexInAnimation(const std::string& name);

    void critStar(Point pos);
    bool critStar(Point pos, float chance);

    int numberFrames(const std::string& path, const std::string& key);

    CREATE_GET_FUNC(getClientPlayer, Player*, m_pClient);
    CREATE_SET_GET_FUNC(setMap, getMap, MapManager*, m_pMap);
    int getBitMask();
    //CREATE_GET_FUNC(getClientUI, PlayerUI*, m_pClientUI);

    float magicDmgCalculator(Statics* defender, SkillStatics* attacker, Point pos);
    float physicDmgCalculator(Statics* defender, SkillStatics* attacker, Point pos);
    float totalDmgCalculator(Statics* defender, SkillStatics* attacker, Point pos);

    CREATE_SET_GET_FUNC(setMaxCoordIndex, getMaxCoordIndex, int, m_nMaxCoordIndex);

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
    int m_nMaxCoordIndex;

    PlayerUI* m_pClientUI;

private:
    bool p_bLockEndGame;
    int p_nBitmask;

END_CREATE_INSTANCE_REFCLASS;
