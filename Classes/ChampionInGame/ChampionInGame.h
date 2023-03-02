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
class Dice;
class ChampionUI;
class SkillInGame;
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
    static ChampionInGame* createWithProperties(Champion *pChamp, ChampionUI *pUI, Dice* pDice, std::vector<SkillInGame*> vSkillDeck);

public:
    virtual void update(float dt);
    virtual void setPosition(Coordinate& coord);
    virtual void setPosition(Arena* pArena);
    virtual void setPosition(cocos2d::Vec2 pos);
    virtual Point getPosition();
    virtual void config();

public:
    void setOwner(Player *pOwner, bool bIsRepresent);

    CREATE_GET_FUNC(getOwner, Player*, m_pOwner);

    CREATE_SET_FUNC(setDice, Dice*, m_pDice);
    CREATE_SET_FUNC(setSkillDeck, std::vector<SkillInGame*>&, m_vSkillDeck);
    CREATE_SET_FUNC(setUI, ChampionUI*, m_pChampionUI);

    CREATE_GET_FUNC(getCoordinate, Coordinate, m_cCoordinate);
    CREATE_SET_GET_FUNC(setStatics, getStatics, IngameStatics*, m_pIngameStatics);

public:
    bool initWithProperties(ChampionUI *pUI, Dice* pDice, std::vector<SkillInGame*> vSkillDeck);

    void updateAfterAction();
    void updateAfterMoving();
    void updateAfterAttacking();
    void beginTurnUpdate();
    void endTurnUpdate();
    bool isContainPoint();


//    void move(Coordinate &coord, MoveType eMoveType);
    void autoFlip();
    bool lifeCheck();
    void setLandingArena(Arena *pArena);
    void reloadDataFromMemory(int nRound);
    void addChampChild(ChampionInGame *pChild);
    void setParent(ChampionInGame *pParent);
    std::string getChildsString(int nTab);
    std::string toStringHelper(int nTab = 2, bool bIsShowParent = true);

    void onLand(Arena *arena);

    void applyEffectToSelf(std::vector<GameEffect*> vEffects);
    void attack(std::vector<ChampionInGame*> vChampions);
    bool onTouch(cocos2d::Touch *touch, cocos2d::Event *event);
    bool endTouch(cocos2d::Touch *touch, cocos2d::Event *event);
    void run(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

public:
    void preDicePhase();
    void doDice();
    void postDicePhase();

protected:
    /// Container
    std::map<ChampionAction, ZYSprite*> m_mSprites;
    std::vector<ChampionInGame*> m_vChilds;
    std::map<int, Arena*> m_mArenaMemory;
    std::map<int, ChampionInGame*> m_mSelfMemory;
    std::vector<ChampionAction> m_vActionMemory;

    /// Must declare
    IngameStatics* m_pIngameStatics;
    Dice* m_pDice;
    Player *m_pOwner;
    ChampionUI* m_pChampionUI;
    std::vector<SkillInGame*> m_vSkillDeck;

    /// Auto declare, has first init value
    Coordinate m_cCoordinate;
    ChampionAction m_eAction;
    HeadDir m_eHead;
    Arena *m_pLandingArena;
    ui::Button *m_pSelfButton;

    /// Auto declare, can be nullptr
    ChampionInGame* m_pParent;

    ///
    bool m_bIsRepresentPlayer;

private:


END_CREATE_REFCLASS