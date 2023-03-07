#pragma once

#include "ZyUwU/ZyUwU.h"
#include "ui/CocosGUI.h"

USING_NS_ALL;

class SkillInGame;
class ChampionInGame;
BEGIN_CREATE_REFCLASS(SkillManager, Node)

public:
    static SkillManager* createWithSkillInGame(SkillInGame* sig, ...) CC_REQUIRES_NULL_TERMINATION;
    static SkillManager* createWithVector(std::vector<SkillInGame*>& vectorOfSkills);
    static SkillManager* createWithSkills(SkillInGame* first, va_list args);
    static SkillManager* createWithSkill(SkillInGame* skill);

public:
    bool initWithVector(std::vector<SkillInGame*>& vectorOfSkills);
    CREATE_SET_GET_FUNC(setOwner, getOwner, ChampionInGame*, m_pOwner);
    CREATE_SET_GET_FUNC(setSelectingSkill, getSelectingSkill, SkillInGame*, m_pSelecting);
    virtual void update(float dt);
    void setUseButton(bool var);
    void enable();
    void disable();

public:
    bool onTouch(Touch *touch, Event *event);
    bool endTouch(Touch *touch, Event *event);
    void clickButton(Ref* pSender, ui::Widget::TouchEventType type);
    void unselectSkill();

protected:
    /// Auto declare, can be nullptr
    ChampionInGame* m_pOwner;
    SkillInGame* m_pSelecting;
    std::vector<SkillInGame*> m_vSkillDecks;

    /// Auto declare
    ui::Button* m_pUse;

END_CREATE_REFCLASS
