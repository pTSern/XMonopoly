#pragma once

#include "../Arena.h"
#include "GameObject/Economy/Economy.h"

USING_NS_ALL;

struct PropertyEconomy
{
public:
    static PropertyEconomy* create(float basePrice, int minLv, int maxLv,
                                   float baseIncome, float baseSellValue,
                                   float incomePerLv, float sellValuePerLv);

public:
    PropertyEconomy();

public:
    CREATE_SET_GET_FUNC(setMinLevel, getMinLevel, const int, m_nMinLevel);
    CREATE_SET_GET_FUNC(setMaxLevel, getMaxLevel, const int, m_nMaxLevel);
    CREATE_SET_GET_FUNC(setBaseIncome, getBaseIncome, const float, m_fBaseIncomeMulti);
    CREATE_SET_GET_FUNC(setBaseSellValue, getBaseSellValue, const float, m_fBaseSellMulti);
    CREATE_SET_GET_FUNC(setIncomeIncrement, getIncomeIncrement, const float, m_fIncomeIncrement);
    CREATE_SET_GET_FUNC(setSellValueIncrement, getSellValueIncrement, const float, m_fSellValueIncrement);
    CREATE_GET_FUNC(getPrice, float, m_price.getAmount());
    CREATE_GET_FUNC(isUpgradeAble, bool, (m_nCurrentLevel < m_nMaxLevel));

public:
    void setPrice(float fPrice);
    void upgrade(int level = 1);
    void downgrade(int level = 1);
    float getSellValue();
    float getIncomeValue();

protected:
    int m_nCurrentLevel, m_nMinLevel, m_nMaxLevel;      ///< The min and the max level can be upgrade
    float m_fIncomeIncrement, m_fSellValueIncrement;    ///< The increment of Property's sell/income multiple per level
    float m_fBaseSellMulti, m_fBaseIncomeMulti;         ///< The base multiple of Sell value and Income
    Economy m_price;                                    ///< The base price
};

BEGIN_CREATE_REFCLASS(Property, Arena)

public:
    struct SortProperty
    {
        inline bool operator() (Property* l, Property* r)
        {
            return l->getSellValue() < r->getSellValue();
        }
    };
public:
    static Property* createWithProperties(const std::string& sTitle, Coordinate &coord, Size rectSize,
                                          Point cLeft, float fPrice, int minLv, int maxLv,
                                          float baseSellMulti, float baseIncomeMulti,
                                          float sellIncrement, float incomeIncrement);

public:
    virtual void update(float dt);
    virtual void onLand(ChampionInGame* pChamp);
    virtual void config();
    virtual bool initWithProperties(const std::string& sTitle, Coordinate &coord, Size& rectSize,
                                    Point& cLeft, float fPrice, int minLv, int maxLv,
                                    float baseSellMulti, float baseIncomeMulti,
                                    float sellIncrement, float incomeIncrement);

public:
    CREATE_SET_GET_FUNC(setOwner, getOwner, Player*, m_pOwner);
    CREATE_GET_FUNC(getTax, float, m_pEconomy->getIncomeValue());
    CREATE_GET_FUNC(getPrice, float, m_pEconomy->getPrice());
    CREATE_GET_FUNC(getSellValue, float, m_pEconomy->getSellValue());
    CREATE_GET_FUNC(hasOwner, bool, m_pOwner);

/////// PURCHASE
public:
    void purchaseProperty(Player* target);
    void acquireProperty(Player* target);
    void removeAllMarkedChild();
    void upgrade();
    void removeOwner();
    void selfSell();

protected:
    void showPurchasePromptHelper(const std::string& message, const ui::Widget::ccWidgetTouchCallback& yesCallBack, const ui::Widget::ccWidgetTouchCallback& noCallback);
    void showMessageHelper(const std::string& message);
    void showMessageHelper(const std::string& message, const float duration);
    void cancelPurchase(Player* target);
    void confirmPurchase(Player* target);

    ui::Button* createPurchaseButton(const std::string& title, int tag, const Point& pos);
    void onPurchaseButtonPressed(Ref* pSender, ui::Widget::TouchEventType type, bool bIsYes, Player* target);

    std::vector<int> m_vRemoveByTagList;                 ///< contain child's tag that will be removed after calling removeAllMarkedChild() func

///////// END PURCHASE
protected:
    Player* m_pOwner;
    ZYLabel* m_pPriceLabel;
    PropertyEconomy* m_pEconomy;

END_CREATE_REFCLASS