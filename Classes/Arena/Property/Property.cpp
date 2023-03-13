#include "Property.h"

//// Factory Registry
//static ArenaTypeRegister<Property> s_register("property");

//// Constructor

Property::Property() :
m_pPrice(Economy::IngameCoin),
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
    auto target = pChamp->getOwner();

    /**
     *  This property does not have owner action
     *  Ask target player to buy this property
     */
    if(!this->hasOwner())
    {
        this->purchaseProperty(target);
        return;
    }

    /**
     *  This property have an owner
     *  Force player to pay this property's tax to its owner
     */
    if(target->doPay(this->getOwner(), this->getTax()))
    {
       target->finishAction();

       /**
        *   Player pay this property's tax
        *   Ask player to repurchase this property
        */
        this->acquireProperty(target);
        return;
    }

    /**
     *  This target player can not pay this property's tax
     *  Force player to sell their property
     */
    if(target->getNetWorth() >= this->getTax())
    {
        this->acquireProperty(target);
    }

    /**
     *  These properties of this target player do not have enough value to sell for this tax.
     *  Force player to lose
     */
    target->lose();
    //pChamp->getOwner()->onLandProperty(this);
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

    this->m_eType = Type::PROPERTY;

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

void Property::purchaseProperty(Player *target)
{
    if(target->getEconomy()->isPayable(this->getPrice()))
    {
        const std::string str = "WOULD YOU LIKE TO BUY THIS\nPROPERTY FOR " + ZYSP_SD(this->getPrice(), 1) + "K";
        this->showPurchasePromptHelper(str, CC_CALLBACK_2(Property::onPurchaseButtonPressed, this, true, target), CC_CALLBACK_2(Property::onPurchaseButtonPressed, this, false, target));
    }
    else
    {
        this->showMessageHelper("YOU DON NOT HAVE ENOUGH MONEY TO BUY THIS", 3);
        target->finishAction();
    }
}

void Property::acquireProperty(Player* target)
{
    target->finishAction();
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

///] Protected

void Property::showMessageHelper(const std::string& message)
{
    auto label = ZYLabel::createWithTTF(message, globalFont, 50);
    label->setTag(77);
    this->m_vRemoveByTagList.emplace_back(label->getTag());
    label->setColor(Color3B::BLUE);
    label->setGlobalZOrder(5);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    label->setPosition(Point(ZYDR_TGVS.width/2, ZYDR_TGVS.height/3*2));
    this->addChild(label);
}

void Property::showMessageHelper(const std::string& message, const float duration)
{
    auto label = ZYLabel::createWithTTF(message, globalFont, 50);
    label->setColor(Color3B::BLUE);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    label->setPosition(Point(ZYDR_TGVS.width/2, ZYDR_TGVS.height/3*2));
    label->setGlobalZOrder(5);
    this->addChild(label);

    auto fade_out = FadeOut::create(duration);
    auto remove = RemoveSelf::create(true);
    auto se = Sequence::create(fade_out, remove, nullptr);
    label->runAction(se);
}

void Property::showPurchasePromptHelper(const std::string& message, const ui::Widget::ccWidgetTouchCallback& yesCallBack, const ui::Widget::ccWidgetTouchCallback& noCallback)
{
    this->showMessageHelper(message);

    auto yes = this->createPurchaseButton("YES", 88, ZYDR_TGVS/4);
    yes->setGlobalZOrder(5);
    yes->addTouchEventListener(yesCallBack);

    auto no = this->createPurchaseButton("NO", 99, Point(ZYDR_TGVS.width/4*3, ZYDR_TGVS.height/4));
    no->setGlobalZOrder(5);
    no->addTouchEventListener(noCallback);

    this->addChild(yes, 5);
    this->addChild(no, 5);
}

ui::Button* Property::createPurchaseButton(const std::string& title, int tag, const Point& pos)
{
    auto button = ui::Button::create("button/n.png", "button/p.png");
    button->setTitleText(title);
    button->setPosition(pos);
    button->setTag(tag);
    this->m_vRemoveByTagList.emplace_back(tag);
    return button;
}

void Property::onPurchaseButtonPressed(Ref* pSender, ui::Widget::TouchEventType type, bool bIsYes, Player* target)
{
    if(type == ui::Widget::TouchEventType::ENDED)
    {
        if(bIsYes) confirmPurchase(target);
        else cancelPurchase(target);
    }
}

void Property::cancelPurchase(Player* target)
{
    this->removeAllMarkedChild();
    target->finishAction();
}

void Property::confirmPurchase(Player* target)
{
    target->getEconomy()->pay(this->getPrice());
    target->addOwnedProperty(this);

    this->setOwner(target);
    this->addDrawRectOrder();
    this->setRectColor(target->getTheColor());

    this->removeAllMarkedChild();
    target->finishAction();
}

void Property::removeAllMarkedChild()
{
    for(int i = m_vRemoveByTagList.size() - 1; i >= 0; i--)
    {
        this->removeChildByTag(m_vRemoveByTagList[i], true);
        m_vRemoveByTagList.erase(m_vRemoveByTagList.begin() + i);
    }
}
