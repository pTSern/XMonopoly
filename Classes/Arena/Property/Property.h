#pragma once

#include "../Arena.h"
#include "GameObject/Economy/Economy.h"

USING_NS_ALL;

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
public:
    CREATE_SET_GET_FUNC(setOwner, getOwner, Player*, m_pOwner);
    CREATE_GET_FUNC(getTax, float, m_pTax.getAmount() * m_fIncomeMultiple);
    CREATE_GET_FUNC(getPrice, float, m_pPrice.getAmount());
    CREATE_GET_FUNC(getSellValue, float, m_fSellMultiple*m_pPrice.getAmount());
    CREATE_GET_FUNC(hasOwner, bool, m_pOwner);

public:

protected:
    Player* m_pOwner;
    Economy m_pPrice, m_pTax, m_pValue;
    ZYLabel* m_pPriceLabel;
    float m_fSellMultiple, m_fIncomeMultiple;


END_CREATE_REFCLASS