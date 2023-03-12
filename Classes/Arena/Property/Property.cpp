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
    ts += tab + " + Price: " + ZYSP_NTS(m_fIncomeMultiple * m_pPrice.getAmount());
    ts += tab + " + Sell Multiple: " + ZY_SP_NUMBER_TO_STRING(m_fSellMultiple);
    ts += tab + " + Income Multiple: " + ZY_SP_NUMBER_TO_STRING(m_fIncomeMultiple);
    ts += tab + " + Title: " + m_pTitle->toString(nTab + 1);
    return ts;
}

void Property::update(float dt)
{
    Arena::update(dt);
    if(m_fIncomeMultiple*m_pPrice.getAmount() >= 0 && m_pOwner) {
        m_pPriceLabel->setString(ZYSP_SD(m_fIncomeMultiple * m_pPrice.getAmount(), 1) + "K");
    }
}

void Property::onLand(ChampionInGame *pChamp)
{
    Arena::onLand(pChamp);

    auto owner = pChamp->getOwner();
    //owner->buyingProperty(this);

}
void Property::config()
{
    Arena::config();

    m_bIsBuyAble = true;

    int x = 1;
    if ((int)m_Coord.g_eDir < 0) x = -1;

    m_pTitle->setRotationSkewX(x*MAP_MNG_GI->getAngleVertical());
    m_pTitle->setRotationSkewY(x*MAP_MNG_GI->getAngleHorizon());

    m_pPriceLabel->setRotationSkewX(m_pTitle->getRotationSkewX());
    m_pPriceLabel->setRotationSkewY(m_pTitle->getRotationSkewY());
    m_pPriceLabel->setColor(Color3B::BLACK);
    m_pPriceLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    m_pPriceLabel->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    auto mid = m_Bottom.getMidpoint(m_Right);
    auto mid2 = m_Left.getMidpoint(m_Bottom);
    auto size = MAP_MNG_GI->getTileMap()->getTileSize();

    switch (m_Coord.g_eDir) 
    {
        // -2
        case Dir::NW:
            m_pTitle->setPosition(Point(mid.x - size.width*2, mid.y + size.height*2));
            m_pPriceLabel->setPosition(mid.x - size.width*0.5, mid.y + size.height*0.5);
            break;
        // 2
        case Dir::WS:
            m_pTitle->setPosition(mid2 + size*2);
            m_pPriceLabel->setPosition(mid2 + size*0.5);
            break;
        // 1
        case Dir::NE:
            m_pTitle->setPosition(mid2 + size*2);
            m_pPriceLabel->setPosition(mid2 + size*0.5);
            break;
        // -1
        case Dir::ES:
            m_pTitle->setPosition(Point(mid.x - size.width*2, mid.y + size.height*2));
            m_pPriceLabel->setPosition(mid.x - size.width*0.5, mid.y + size.height*0.5);
            break;
        default:
            break;
    }

    this->addChild(m_pPriceLabel);

    this->scheduleUpdate();
}
bool Property::initWithProperties(const std::string& sTitle, Coordinate &coord, Size rectSize, Point left,
                                float fPrice, float fSellMultiple, float fIncomeMultiple)
{
    if(!Arena::initWithProperties(sTitle, coord, rectSize, left)) return false;

    this->setName("PROPERTY");
    this->m_pPrice.setAmount(fPrice);
    this->m_fIncomeMultiple = fIncomeMultiple;
    this->m_fSellMultiple = fSellMultiple;
    m_pPriceLabel = ZYLabel::createWithTTF(m_pTitle->getTTFConfig(), "");

    this->config();
    return true;
}

//// Static

Property* Property::createWithProperties(const std::string& sTitle, Coordinate &coord, Size rectSize,
                                      Point cLeft, float fPrice, float fSellMultiple, float fIncomeMultiple)
{
    auto ret = new (std::nothrow) Property();
    if (ret->initWithProperties(sTitle, coord, rectSize, cLeft, fPrice, fSellMultiple, fIncomeMultiple))
    {
        ret->autorelease();
        return ret;
    };
    CC_SAFE_DELETE(ret);
    return nullptr;
}
