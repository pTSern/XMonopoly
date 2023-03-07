#pragma once

#include "../../ZyUwU/ZyUwU.h"
#include "../../GameObject/GameObject.h"
#include "../../Support/GameConstant.h"
#include "../../Support/Macros.h"
#include "ui/CocosGUI.h"

class SkillInGame;
BEGIN_CREATE_REFCLASS(SkillCard, GameObject)

#define SET_SPRITE_HELPER(__FUNC_NAME__, __SET_VAR__)                   \
void __FUNC_NAME__(std::string sPath)                                   \
{                                                                       \
    if(FILE_CHECKER(sPath)) __SET_VAR__->replaceSprite(sPath.c_str());  \
}                                                                       \

#define SET_LABEL_HELPER(__FUNC_NAME__, __SET_VAR__) \
void __FUNC_NAME__(std::string sString)              \
{                                                    \
    __SET_VAR__->setString(sString);                 \
}                                                    \

#define SET_FULL_SPRITE(__ACTION__)          \
p_pShapeSprite->__ACTION__;                  \
p_pNameSprite->__ACTION__;                   \
p_pIconSprite->__ACTION__;                   \
p_pManaCostSprite->__ACTION__;               \
p_pSkillPointCostSprite->__ACTION__;         \
p_pDescriptionSprite->__ACTION__;            \
p_pCoolDownSprite->__ACTION__;               \
p_pButton->__ACTION__;                       \


#define SET_FULL_LABEL(__ACTION__)    \
p_pNameLabel->__ACTION__;             \
p_pDescriptionLabel->__ACTION__;      \
p_pManaCostLabel->__ACTION__;         \
p_pSkillPointCostLabel->__ACTION__;   \
p_pCoolDownLabel->__ACTION__;         \


#define SET_FULL_VARIABLE(__ACTION__) \
SET_FULL_SPRITE(__ACTION__)           \
SET_FULL_LABEL(__ACTION__)            \

#define PRESET_FULL_SPRITE(__ACTION__, ...)                 \
__ACTION__(p_pShapeSprite, ##__VA_ARGS__);                  \
__ACTION__(p_pNameSprite, ##__VA_ARGS__);                   \
__ACTION__(p_pIconSprite, ##__VA_ARGS__);                   \
__ACTION__(p_pManaCostSprite, ##__VA_ARGS__);               \
__ACTION__(p_pSkillPointCostSprite, ##__VA_ARGS__);         \
__ACTION__(p_pDescriptionSprite, ##__VA_ARGS__);            \
__ACTION__(p_pCoolDownSprite, ##__VA_ARGS__);               \
__ACTION__(p_pButton, ##__VA_ARGS__);                       \


#define PRESET_FULL_LABEL(__ACTION__, ...) \
__ACTION__(p_pNameLabel, ##__VA_ARGS__);             \
__ACTION__(p_pDescriptionLabel, ##__VA_ARGS__);      \
__ACTION__(p_pManaCostLabel, ##__VA_ARGS__);         \
__ACTION__(p_pSkillPointCostLabel, ##__VA_ARGS__);   \
__ACTION__(p_pCoolDownLabel, ##__VA_ARGS__);         \

#define PRESET_FULL_VARIABLE(__ACTION__, ...)           \
PRESET_FULL_SPRITE(__ACTION__, ##__VA_ARGS__)           \
PRESET_FULL_LABEL(__ACTION__, ##__VA_ARGS__)            \


public:
    static SkillCard* createWithProperties(std::string sIconSprite, std::string sShapeSprite, std::string sNameSprite,
                                           std::string sManaCostSprite, std::string sSkillPointCostSprite, std::string sDescriptionSprite,
                                           std::string sCoolDownSprite, std::string sNameLabel, std::string sManaCostLabel,
                                           std::string sSKillPointCostLabel, std::string sCoolDownLabel, std::string sDescriptionLabel);
    static SkillCard* createDefault();

public:
    virtual void setOpacity(uint8_t opacity);
    virtual void setPosition(const cocos2d::Point &position);
    virtual void update(float dt);
    //virtual Action* runAction(Action* action);
    virtual ~SkillCard();
    virtual Action* runAction(Action* action);

public:
    SET_SPRITE_HELPER(setIconSprite, p_pIconSprite);
    SET_SPRITE_HELPER(setShapeSprite, p_pShapeSprite);
    SET_SPRITE_HELPER(setNameSprite, p_pNameSprite);
    SET_SPRITE_HELPER(setManaCostSprite, p_pManaCostSprite);
    SET_SPRITE_HELPER(setSkillPointCostSprite, p_pSkillPointCostSprite);
    SET_SPRITE_HELPER(setDescriptionSprite, p_pDescriptionSprite);
    SET_SPRITE_HELPER(setCoolDownSprite, p_pCoolDownSprite);

    SET_LABEL_HELPER(setNameLabel, p_pNameLabel);
    SET_LABEL_HELPER(setManaCostLabel, p_pManaCostLabel);
    SET_LABEL_HELPER(setSkillPointCostLabel, p_pSkillPointCostLabel);
    SET_LABEL_HELPER(setCoolDownLabel, p_pCoolDownLabel);

    CREATE_SET_GET_FUNC(setOwner, getOwner, SkillInGame*, p_pOwner);

    void setDescriptionLabel(std::string sDescription);

    void config();
    void selfRepair();
    Vec2 getShapePosition();

    CREATE_GET_FUNC(getShapeSize, Size, p_pShapeSprite->getContentSize());

    void onSelect();
    void onUnselect();

    bool onTouch(cocos2d::Touch *touch, cocos2d::Event *event);
    bool endTouch(cocos2d::Touch *touch, cocos2d::Event *event);
    void run(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

    void disable();
    void enable();
    void unSelectable();
    void selectable();

protected:
    bool initWithProperties(std::string sIconSprite, std::string sShapeSprite, std::string sNameSprite,
                            std::string sManaCostSprite, std::string sSkillPointCostSprite, std::string sDescriptionSprite,
                            std::string sCoolDownSprite, std::string sNameLabel, std::string sManaCostLabel,
                            std::string sSKillPointCostLabel, std::string sCoolDownLabel, std::string sDescriptionLabel);

    void setDescriptionLabelHelper();

private:
    zy::ZYSprite *p_pIconSprite, *p_pShapeSprite, *p_pNameSprite,
        *p_pManaCostSprite, *p_pSkillPointCostSprite, *p_pDescriptionSprite,
        *p_pCoolDownSprite;

    zy::ZYLabel *p_pNameLabel, *p_pDescriptionLabel, *p_pManaCostLabel,
        *p_pSkillPointCostLabel, *p_pCoolDownLabel;

    ui::Button *p_pButton;
    bool p_bSelected, p_bSelectable;

    SkillInGame* p_pOwner;

private:
    int const pc_nNameSize = 24, pc_nDescriptionSize = 12, pc_nManaCostSize = 14;
    int const pc_nSkillPointSize = 14, pc_nCoolDown = 14;


END_CREATE_REFCLASS
