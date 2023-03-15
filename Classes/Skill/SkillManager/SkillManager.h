#pragma once

#include "ZyUwU/ZyUwU.h"
#include "ui/CocosGUI.h"

USING_NS_ALL;

class SkillInGame;
class ChampionInGame;
BEGIN_CREATE_REFCLASS(SkillManager, Node)

public: // Quick create func
    static SkillManager* createWithSkillInGame(SkillInGame* sig, ...) CC_REQUIRES_NULL_TERMINATION;
    static SkillManager* createWithVector(std::vector<SkillInGame*>& vectorOfSkills);
    static SkillManager* createWithSkills(SkillInGame* first, va_list args);

public: // Initialize Function
    bool initWithVector(std::vector<SkillInGame*>& vectorOfSkills);

public: // Public function that use to use
    CREATE_SET_GET_FUNC(setOwner, getOwner, ChampionInGame*, m_pOwner);
    CREATE_SET_GET_FUNC(setSelectingSkill, getSelectingSkill, SkillInGame*, m_pSelecting);
    const Vec2& getUseButtonPosition();

    /**
     *  Call this function to automatic un-select the selecting skill.
     */
    void unselectSkill();

    /**
     *  Turn this object's USE button to be On/Off.
     *  @prama var TRUE: turn on the button, false otherwise
     */
     /**
      *
      * @param var
      */
    void setUseButton(bool var);

public: // Schedule Handle
    virtual void update(float dt);

public: // Handle to turn on/off this object.
    void enable();
    void disable();

public: // Handle Touch Event
    bool onTouch(Touch *touch, Event *event);
    bool endTouch(Touch *touch, Event *event);
    void clickButton(Ref* pSender, ui::Widget::TouchEventType type);

protected:
    /// Auto declare, can be nullptr
    ChampionInGame* m_pOwner;
    SkillInGame* m_pSelecting;
    std::vector<SkillInGame*> m_vSkillDecks;

    /// Auto declare
    ui::Button* m_pUse;

END_CREATE_REFCLASS
