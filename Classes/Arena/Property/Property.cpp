#include "Property.h"

//// Factory Registry
//static ArenaTypeRegister<Property> s_register("property");

//// Constructor

Property::Property() :
m_pPrice(Economy::IngameCoin),
m_pTax(Economy::IngameCoin),
m_pValue(Economy::IngameCoin),
m_fSellMultiple(1),
m_fIncomeMultiple(1),
m_pOwner(nullptr)
{

}

//// Public

//Virtual

bool Property::init()
{
    return true;
}

void Property::log()
{
    ZY_EZ_LOG;
}

std::string Property::toString(int nTab)
{
    std::string ts;
    std::string tab = ZY_SP_TAB(nTab);
    ts = Arena::toString();
    ts += tab + " + Income: " + ZYSP_NTS(m_fIncomeMultiple * m_pPrice.getAmount());
    ts += tab + " + Sell Multiple: " + ZY_SP_NUMBER_TO_STRING(m_fSellMultiple);
    ts += tab + " + Income Multiple: " + ZY_SP_NUMBER_TO_STRING(m_fIncomeMultiple);
    ts += tab + " + Title: " + m_pTitle->toString(nTab + 1);
    return ts;
}

void Property::update(float dt)
{
    Arena::update(dt);
    if(m_fIncomeMultiple*m_pPrice.getAmount() >= 0) {
        m_pPriceLabel->setString(ZYSP_NTS(m_fIncomeMultiple * m_pPrice.getAmount()));
    }
}

void Property::onLand(ChampionInGame *pChamp)
{
    Arena::onLand(pChamp);

    auto owner = pChamp->getOwner();
    if(!m_pOwner)
    {
        owner->buyingProperty(owner);
    }

}
void Property::config()
{
    Arena::config();

    m_bIsBuyAble = true;

    this->addChild(m_pPriceLabel);
    m_pPriceLabel->setRotation(m_pTitle->getRotation());

    m_pTitle->setPosition(Point(m_Left.x, m_Left.y));

    this->scheduleUpdate();
}
bool Property::initWithProperties(const std::string& sTitle, Coordinate &coord,
                                float fPrice, float fSellMultiple, float fIncomeMultiple)
{
    if(!Arena::initWithProperties(sTitle, coord)) return false;

    this->setName("PROPERTY");
    this->m_pPrice.setAmount(fPrice);
    this->m_fIncomeMultiple = fIncomeMultiple;
    this->m_fSellMultiple = fSellMultiple;
    m_pPriceLabel = ZYLabel::createWithTTF(m_pTitle->getTTFConfig(), "");

    this->config();
    return true;
}

//Static

Property* Property::createWithProperties(const std::string& sTitle, Coordinate &coord, Size rectSize,
                                      Point cLeft, float fPrice, float fSellMultiple, float fIncomeMultiple)
{
    auto ret = new (std::nothrow) Property();
    ret->setRectPoint(cLeft, rectSize);
    if (ret->initWithProperties(sTitle, coord, fPrice, fSellMultiple, fIncomeMultiple))
    {
        ret->autorelease();
        return ret;
    };
    CC_SAFE_DELETE(ret);
    return nullptr;
}
