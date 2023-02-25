#pragma once

#include "../GameObject/GameObject.h"
#include "../ZyUwU/ZyUwU.h"
#include "../Champion/Champion.h"
#include "../Support/Coordinate.h"
#include "Extension.h"

USING_NS_ALL;

enum class HeadDir
{
    FRONT = 1,
    BEHIND = -1
};

enum class MoveType
{
    MOVE_TO,
    MOVE_BY
};

class Player;
class Arena;
class GameEffect;
BEGIN_CREATE_REFCLASS(ChampionInGame, Champion)

public:
    enum class ChampionAction
    {
        IDLE,
        MOVED,
        ATTACKED
    };
public:
    static ChampionInGame* createWithChampion(Champion *pChamp, bool bIsClone = true, bool bIsDeleteCloner = false);

public:
    virtual void update(float dt);
    virtual void setPosition(Coordinate& coord);
    virtual void setPosition(Arena* pArena);

public:
//    void move(Coordinate &coord, MoveType eMoveType);
    void autoFlip();
    bool lifeCheck();
    void setLandingArena(Arena *pArena);
    void reloadDataFromMemory(int nRound);
    void addChampChild(ChampionInGame *pChild);
    void setParent(ChampionInGame *pParent);
    std::string getChildsString(int nTab);
    std::string toStringHelper(int nTab = 2, bool bIsShowParent = true);

    CREATE_SET_GET_FUNC(setOwner, getOwner, Player*, m_pOwner);
    void onLand(Arena *arena);

    void applyEffectToSelf(std::vector<GameEffect*> vEffects);
    void attack(std::vector<ChampionInGame*> vChampions);

protected:
    std::map<ChampionAction, ZYSprite*> m_mSprites;
    IngameStatics* m_pIngameStatics;
    Coordinate m_cCoordinate;
    ChampionAction m_eAction;
    std::vector<ChampionInGame*> m_vChilds;
    HeadDir m_eHead;
    std::map<int, Arena*> m_mArenaMemory;
    std::map<int, ChampionInGame*> m_mSelfMemory;
    Arena *m_pLandingArena;
    ChampionInGame* m_pParent;

    std::vector<ChampionAction> m_vActionMemory;

    Player *m_pOwner;
    bool m_bIsRepresentPlayer;

private:


END_CREATE_REFCLASS