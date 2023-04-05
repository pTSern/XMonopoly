#pragma once

#include "../GameObject/GameObject.h"
#include "../ZyUwU/ZyUwU.h"
#include "../Champion/Champion.h"
#include "../Support/Coordinate.h"
#include "Extension.h"
#include "Skill/SkillInGame/SkillInGame.h"

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
class SkillManager;
class ChampionHUD;
BEGIN_CREATE_REFCLASS(ChampionInGame, Champion)

public:
    enum class ChampionAction
    {
        IDLE,
        MOVING,
        ATTACKING,
        CASTING_SKILL
    };

    enum class ChampionStatus
    {
        NORMAL,
        DYING,
        DEATH
    };

    enum class ChampionTurnPhase
    {
        NONE,
        PRE_DICE,
        POS_DICE,
    };

public:
    static ChampionInGame* createWithChampion(Champion *pChamp, bool bIsClone = true, bool bIsDeleteCloner = false);
    static ChampionInGame* createWithProperties(Champion *pChamp, ChampionUI *pUI, Dice* pDice, SkillManager* vSkillDeck);

public:
    struct SortChampion
    {
        inline bool operator() (ChampionInGame* l, ChampionInGame* r)
        {
            return l->getStatics()->getStatics()->getSpeed() < r->getStatics()->getStatics()->getSpeed();
        }
    };

public:
    virtual void update(float dt);
    virtual void setPosition(Coordinate& coord);
    virtual void setPosition(Arena* pArena);
    virtual void setPosition(cocos2d::Vec2 pos);
    virtual Point getPosition();
    virtual void config();
    virtual void contactTo(PhysicsContact& contact, GameObject* target) override;
    virtual void contactBy(PhysicsContact& contact, GameObject* target) override;

public:
    void setOwner(Player *pOwner, bool bIsRepresent);

    CREATE_GET_FUNC(getOwner, Player*, m_pOwner);

    CREATE_SET_GET_FUNC(setDice, getDice, Dice*, m_pDice);
    CREATE_SET_FUNC(setPreDiceSkillDeck, SkillManager*, m_pPreDiceSkillDeck);
    CREATE_SET_FUNC(setPostDiceSkillDeck, SkillManager*, m_pPostDiceSkillDeck);
    CREATE_SET_FUNC(setUI, ChampionUI*, m_pChampionUI);

    CREATE_GET_FUNC(getCoordinate, Coordinate, m_cCoordinate);
    CREATE_SET_GET_FUNC(setStatics, getStatics, IngameStatics*, m_pIngameStatics);
    CREATE_GET_FUNC(isTurn, bool, m_bIsTurn);
    CREATE_GET_FUNC(getLandingArena, Arena* , m_pLandingArena);
    CREATE_GET_FUNC(isNotMoving, bool, m_eAction != ChampionAction::MOVING);
    CREATE_GET_FUNC(isCastingSkill, bool, m_eAction == ChampionAction::CASTING_SKILL);
    CREATE_GET_FUNC(getIconSize, Size, m_pIcon->getContentSize());
    CREATE_GET_FUNC(isRepresentPlayer, bool, m_bIsRepresentPlayer);
    CREATE_GET_FUNC(isDeath, bool, m_eStatus == ChampionStatus::DEATH);
    CREATE_GET_FUNC(getAvatar, ZYSprite*, m_pAvatar);

    bool isValidTurn();

public:
    bool initWithProperties(ChampionUI *pUI, Dice* pDice, SkillManager* vSkillDeck);

    void autoFlip();

    //// IN UPDATE LOOP
    void lifeCheck();
    void onDeath();
    void onDying();
    void respawn();

    void setLandingArena(Arena *pArena);
    void reloadDataFromMemory(int nRound);
    void addChampChild(ChampionInGame *pChild);
    void setParent(ChampionInGame *pParent);
    std::string getChildsString(int nTab);
    std::string toStringHelper(int nTab = 2, bool bIsShowParent = true);

    void onLand(bool attack = true);
    void endLand();

    void applyEffectToSelf(std::vector<GameEffect*> vEffects);

    //// Attack
    void attack(std::vector<ChampionInGame*>& vChampions);
    void beAttacked(ChampionInGame* attacker);
    void beAttacked(SkillStatics *pStatics, ChampionInGame* attacker);

    /// Self-Button
    bool onTouch(cocos2d::Touch *touch, cocos2d::Event *event);
    bool endTouch(cocos2d::Touch *touch, cocos2d::Event *event);
    void run(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

    /**
     *
     * @param num The number of Dice
     * @warning THIS WILL FORCE CHAMPION TO END THIS CURRENT PHASE.
     */
    void jumpTo(int num);
    /**
     *
     * @param pos
     * @warning THIS WILL CALL endJump() FUNCTION AFTER FINISHING JUMP. DO NOT CALL THIS IF U DONT KNOW WHAT R U DOIN, CALL SetPosition(Point) INSTEAD
     */
    void jumpTo(Point pos);
    void jumpTo(Coordinate coord);
    void jumpTo(Arena* arena);
    void jumpToNextCoord();
    void endJump();

    virtual void startTurn();
    void enterPreDicePhase();
    void endPreDicePhase();
    bool canEnterPostDice();
    void enterPostDicePhase();
    void endPostDicePhase();
    void endTurn();

    void castingSkill(float& manaCost, float& hpCost, float& SpCost);

    void disable();
    void enable();

    void setHUD(bool var);

public:
    /**
     * A small function to enable the dice.
     * The purpose of making this function is to prevent other objects from accessing to the Dice Object.
     */
    void enableDice();

protected:
    /// Container
    std::vector<ChampionInGame*> m_vChilds;                     ///< the array of champion children (children)
    std::vector<ChampionAction> m_vActionMemory;                ///< the array of the champion action

    /// Must declare
    IngameStatics* m_pIngameStatics;                            ///< the pointer to the ingame statics
    Dice* m_pDice;                                              ///< the dice object (child)
    Player *m_pOwner;                                           ///< weak reference to the owner of this champion
    ChampionUI* m_pChampionUI;                                  ///< the UI of the champion (child)
    ChampionHUD* m_pChampionHUD;                                ///< the HUD of the champion (child)
    SkillManager* m_pPreDiceSkillDeck, *m_pPostDiceSkillDeck;   ///< the skill deck (chilren)

    /// Auto declare, has first init value
    Coordinate m_cCoordinate;                                   ///< the coordinate of the champion
    ChampionAction m_eAction;                                   ///< the action of the champion
    ChampionStatus m_eStatus;                                   ///< the status of the champion
    HeadDir m_eHead;                                            ///< the direction of the champion head
    Arena *m_pLandingArena, *m_pMemArena;                       ///< weak reference to the landing arena and the last landed arena
    ChampionTurnPhase m_eTurnPhase;                             ///< the phase of this champion on turn
    ui::Button *m_pSelfButton;                                  ///< the button is the self-image help the client to switching view point

    /// Auto declare, can be nullptr
    ChampionInGame* m_pParent;                                  ///< weak reference to the parent of this champion

    ///
    bool m_bIsRepresentPlayer;                                  ///< mark this champion is represent the player or not
    bool m_bIsTurn, m_bIsEndTurn;                               ///< mark this champion is on turn an is end turn
    bool m_bIsAction;                                           ///< mark if this champion is doing action or not

private:
    int p_nJumpTime, p_nCurrentJump;                            ///< This only use for storing data to use all jumpTo() function

END_CREATE_REFCLASS