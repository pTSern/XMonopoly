#pragma once

#include "../Arena.h"
#include "GameObject/Economy/Economy.h"

USING_NS_ALL;

struct PropertyLevel
{
public:
    bool isUpgradeAble();

protected:
    int m_nMinLevel, m_nMaxLevel;
    Economy m_price;
};

BEGIN_CREATE_REFCLASS(Property, Arena)

public:
    static Property* createWithProperties(const std::string& sTitle, Coordinate &coord, Size rectSize,
                                          Point cLeft, float fPrice, float fSellMultiple, float fIncomeMultiple);

public:
    virtual void update(float dt);
    virtual void onLand(ChampionInGame* pChamp);
    virtual void config();
    virtual bool initWithProperties(const std::string& sTitle, Coordinate &coord, Size rectSize, Point left,
                                    float fPrice, float fSellMultiple, float fIncomeMultiple);

    void upgrade();
public:
    CREATE_SET_GET_FUNC(setOwner, getOwner, Player*, m_pOwner);
    CREATE_GET_FUNC(getTax, float, m_pPrice.getAmount() * m_fIncomeMultiple);
    CREATE_GET_FUNC(getPrice, float, m_pPrice.getAmount());
    CREATE_GET_FUNC(getSellValue, float, m_fSellMultiple*m_pPrice.getAmount());
    CREATE_GET_FUNC(hasOwner, bool, m_pOwner);

/////// PURCHASE
public:
    void purchaseProperty(Player* target);
    void acquireProperty(Player* target);

protected:
    void showPurchasePromptHelper(const std::string& message, const ui::Widget::ccWidgetTouchCallback& yesCallBack, const ui::Widget::ccWidgetTouchCallback& noCallback);
    void showMessageHelper(const std::string& message);
    void showMessageHelper(const std::string& message, const float duration);
    void cancelPurchase(Player* target);
    void confirmPurchase(Player* target);

    ui::Button* createPurchaseButton(const std::string& title, int tag, const Point& pos);
    void onPurchaseButtonPressed(Ref* pSender, ui::Widget::TouchEventType type, bool bIsYes, Player* target);
    void removeAllMarkedChild();

    std::vector<int> m_vRemoveByTagList;                 ///< contain child's tag that will be removed after calling removeAllMarkedChild() func

///////// END PURCHASE
protected:
    Player* m_pOwner;
    Economy m_pPrice;
    ZYLabel* m_pPriceLabel;
    float m_fSellMultiple, m_fIncomeMultiple;


END_CREATE_REFCLASS