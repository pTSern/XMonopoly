#pragma once

#include "../ZyUwU/ZyUwU.h"
#include "ui/CocosGUI.h"
#include "GameObject/GameObject.h"
#include "GameMaster/GameMaster.h"
#include "Map/Map.h"

USING_NS_ALL;

BEGIN_CREATE_REFCLASS(Dice, GameObject)

public:
    static Dice* createWithProperties(const std::string& sPath);

public:
    virtual void config();
    virtual void update(float dt) {};
    virtual ~Dice();

public:
    CREATE_GET_FUNC(getLastestDiceNum, int, m_vDiceMemory.back());
    CREATE_GET_FUNC(isRolled, bool, !this->m_pButton->isVisible());

    const Size& getDiceButtonSize();

    int rollDice();
    bool initWithProperties(const std::string& sPath );
    void loadElement(const std::string& path);
    void disableDice();
    void enableDice();
    void disable();
    void enable();

    bool onTouch(cocos2d::Touch *touch, cocos2d::Event *event);
    bool endTouch(cocos2d::Touch *touch, cocos2d::Event *event);
    void run(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    void setDiceButtonPosition(const Vec2& pos);

protected:
    ZYSprite* m_pDice;
    ui::Button* m_pButton;
    int m_nDiceNum;
    Rect m_centerRect;
    std::vector<int> m_vDiceMemory;

private:
    Size diceSize;

END_CREATE_REFCLASS;