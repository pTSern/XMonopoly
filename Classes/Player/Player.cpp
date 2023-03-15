#include "Player.h"
#include "Arena/Arena.h"
#include "Support/GameConstant.h"
#include "Arena/Property/Property.h"
#include "Arena/SpecialArena/SpecialArena.h"
#include "GameMaster/GameMaster.h"
#include "Action/PlayerAction.h"

//// Constructor

Player::Player() :
m_pEconomy(nullptr),
m_pSelectingObject(nullptr),
m_eType(SelectType::NONE),
m_Color(Color4F::RED),
m_eAction(TheAction::IDLE)
{

}

//// Virtual

bool Player::init()
{
    if(!Layer::init()) return false;

    // Init Event Listener
    //m_pEventListener = EventListenerTouchOneByOne::create();
    //m_pEventListener->onTouchBegan = CC_CALLBACK_2(Player::onTouch, this);
    //m_pEventListener->onTouchEnded = CC_CALLBACK_2(Player::endTouch, this);

    m_pEconomy = IgEcoMng::create();
    m_pEconomy->setAmount(5000);
    this->addChild(m_pEconomy);
    m_pEconomy->setPosition(Point(ZYDR_GVS/6));
    this->scheduleUpdate();

    return true;
}

std::string Player::toString(int nTab)
{
    std::string ts;
    return ts;
}

void Player::log()
{

}

void Player::update(float dt)
{
}

//// Public

bool Player::onTouch(Touch *touch, Event *event)
{
    return true;
}
bool Player::endTouch(Touch *touch, Event *event)
{
    return true;
}

void Player::setControlChampion(ChampionInGame* champ)
{
    this->m_pControllingChampion = champ;
}

void Player::setChampionViewPoint(ChampionInGame *pChampion)
{

}

void Player::onLandProperty(Property* property)
{
    if(!property->hasOwner())
    {
        this->purchaseProperty(property);
    }
    else
    {
        this->pay(property->getOwner(), property->getTax());
    }
}

void Player::onLandSpecialArena(SpecialArena* special)
{
    this->finishAction();
}

void Player::addChampion(ChampionInGame* pChamp)
{
    if(pChamp)
    {
        pChamp->disable();
        m_vChampions.emplace_back(pChamp);
        m_vChampions.back()->setOwner(this, true);
        this->addChild(pChamp);
    }
}

void Player::finishAction()
{
    //m_pControllingChampion->endTurn();
    if(!m_pControllingChampion->isTurn())
    {
        this->disable();
    }
    GM_GI->calculateNewTurn();
}

void Player::disable()
{
    ///> disable economy node
    this->m_pEconomy->disable();

    ///> disable all owned champion
    if(m_pControllingChampion)
    {
        this->m_pControllingChampion->disable();
        //this->m_pControllingChampion = nullptr;
    }
}

void Player::enable()
{
    this->m_pEconomy->enable();
}

void Player::lose()
{
    finishAction();
}

void Player::startTurn(ChampionInGame* child)
{
    this->setControlChampion(child);
    this->setChampionViewPoint(child);
}

void Player::endTurn()
{
}

bool Player::doPay(Player* target, float money)
{
    return (m_pEconomy->pay(target->m_pEconomy, money));
}

void Player::receiveMoney(float money)
{
    this->m_pEconomy->receive(money);
}

void Player::addOwnedProperty(Property* property)
{
    this->m_vOwn.push_back(property);
}

void Player::removeOwnedProperty(Property *property)
{
    for(int i = 0; i < m_vOwn.size(); i ++)
    {
        if(m_vOwn[i] == property)
        {
            m_vOwn.erase(m_vOwn.begin() + i);
            break;
        }
    }
}

float Player::getTotalPropertyValue()
{
    float total = 0;
    for (auto &x : m_vOwn)
    {
        total += x->getSellValue();
    }
    return total;
}

//////////////////////////////////////////////////////////////////////////

void Player::pay(Player* target, float money)
{
    if(m_pEconomy->pay(target->m_pEconomy, money))
    {
        this->finishAction();
    }
    else
    {
        this->lose();
    }
}

///] Protected

void Player::showMessageHelper(const std::string& message, const float& duration)
{
    auto config = defaultTTFConfig;
    config.fontSize = 60;
    config.bold = true;
    auto label = ZYLabel::createWithTTF(config, message, TextHAlignment::CENTER, ZYDR_TGVS.width/2);
    label->setColor(Color3B::WHITE);
    label->setPosition(Point(ZYDR_TGVS.width/2, ZYDR_TGVS.height/3*2));
    this->addChild(label);
    label->setGlobalZOrder(5);

    auto fade_out = FadeOut::create(duration);
    auto remove = RemoveSelf::create(true);
    auto se = Sequence::create(fade_out, remove, nullptr);
    label->runAction(se);
}

void Player::showTheMessageHelper(const std::string& message, Vec2& pos, const float& fontSize)
{
    auto config = defaultTTFConfig;
    config.fontSize = fontSize;
    config.bold = true;
    auto label = ZYLabel::createWithTTF(config, message, TextHAlignment::CENTER, ZYDR_TGVS.width/2);
    label->setColor(Color3B::BLACK);
    markChildToRemove(label, 11);
    label->setPosition(pos);
    label->setGlobalZOrder(6);
    this->addChild(label );
}

ZYSprite* Player::showMessageWithBackgroundHelper(const std::string& message)
{
    auto background = ZYSprite::create(sr_background);
    background->setPosition(ZYDR_TGVS/2);
    this->markChildToRemove(background, 66);
    this->addChild(background);
    background->setGlobalZOrder(4);

    auto config = defaultTTFConfig;
    config.fontSize = 30;
    config.bold = true;
    auto label = ZYLabel::createWithTTF(config, message, TextHAlignment::CENTER, ZYDR_TGVS.width/2);
    label->setColor(Color3B::BLACK);
    this->markChildToRemove(label, 77);
    label->setPosition(background->getContentPositionWithNewAnchorPoint(Vec2(0.5, 0.5 - 0.5*Fraction::toFloat(1,6))));
    this->addChild(label, 1);
    label->setGlobalZOrder(5);

    return background;
}

void Player::showPurchasePromptHelper(const std::string& message, const std::string& message2, const ui::Widget::ccWidgetTouchCallback& yesCallBack, const ui::Widget::ccWidgetTouchCallback& noCallback)
{
    //this->showMessageHelper(message);
    const auto bg = this->showMessageWithBackgroundHelper(message);

    const auto yyV = 0.5 - 0.5*Fraction::toFloat(3, 6);
    auto yes = this->createPurchaseButton("YES", 88, bg->getContentPositionWithNewAnchorPoint(Vec2(0.25, yyV)));
    yes->addTouchEventListener(yesCallBack);

    auto no = this->createPurchaseButton("NO", 99, bg->getContentPositionWithNewAnchorPoint(Vec2(0.75, yyV)));
    no->addTouchEventListener(noCallback);

    this->addChild(yes );
    no->setGlobalZOrder(6);
    this->addChild(no );
    yes->setGlobalZOrder(6);

    auto pos = bg->getContentPositionWithNewAnchorPoint(Vec2(0.5, 0.5-0.5*Fraction::toFloat(5,6)));
    this->showTheMessageHelper(message2, pos, 30);
}

ui::Button* Player::createPurchaseButton(const std::string& title, int tag, const Point& pos)
{
    auto button = ui::Button::create(sr_button_default, sr_button_clicked);
    button->setTitleText(title);
    button->setPosition(pos);
    CCUB_SSTFSP(button, 0.3f);
    markChildToRemove(button, tag);
    return button;
}

void Player::onPurchaseButtonPressed(Ref* pSender, ui::Widget::TouchEventType type, bool bIsYes, Property* target)
{
    if(type == ui::Widget::TouchEventType::ENDED)
    {
        if(bIsYes) confirmPurchase(target);
        else cancelPurchase(target);
    }
}

void Player::cancelPurchase(Property* property)
{
    this->removeAllMarkedChild();
    this->finishAction();
}

void Player::confirmPurchase(Property* property)
{
    m_pEconomy->pay(property->getPrice());
    m_vOwn.push_back(property);
    property->setOwner(this);
    property->addDrawRectOrder();
    property->setRectColor(m_Color);
    this->removeAllMarkedChild();
    this->finishAction();
}

void Player::onAcquireButtonPressed(Ref* pSender, ui::Widget::TouchEventType type, bool bIsYes, Property* target)
{
    if(type == ui::Widget::TouchEventType::ENDED)
    {
        if(bIsYes) confirmAcquire(target);
        else cancelAcquire(target);
    }
}

void Player::cancelAcquire(Property* property)
{
    this->removeAllMarkedChild();
    this->finishAction();
}

void Player::confirmAcquire(Property* property)
{
    const auto target = property->getOwner();
    this->doPay(target, property->getSellValue());
    target->removeOwnedProperty(property);
    this->m_vOwn.push_back(property);
    property->setOwner(this);
    property->setRectColor(m_Color);
    this->removeAllMarkedChild();
    this->finishAction();
}

void Player::onUpgradeButtonPressed(Ref* pSender, ui::Widget::TouchEventType type, bool bIsYes, Property* target)
{
    if(type == ui::Widget::TouchEventType::ENDED)
    {
        if(bIsYes) confirmUpgrade(target);
        else cancelUpgrade(target);
    }
}

void Player::confirmUpgrade(Property* property)
{
    m_pEconomy->pay(property->getPrice());
    property->upgrade();
    this->removeAllMarkedChild();
    this->finishAction();
}

void Player::cancelUpgrade(Property* property)
{
    this->removeAllMarkedChild();
    this->finishAction();
}
void Player::markChildToRemove(Node* target, int tag)
{
    target->setTag(tag);
    this->m_vRemoveByTagList.emplace_back(tag);
}

void Player::removeAllMarkedChild()
{
    for(int i = m_vRemoveByTagList.size() - 1; i >= 0; i--)
    {
        this->removeChildByTag(m_vRemoveByTagList[i], true);
        m_vRemoveByTagList.erase(m_vRemoveByTagList.begin() + i);
    }
}

void Player::purchaseProperty(Property *property)
{
    const auto price = property->getPrice();
    if(m_pEconomy->isPayable(price))
    {
        const std::string str = "Purchase property for: " + ZYSP_SD(price, 1) + "K";
        const std::string rm = "Remaining balance: " + ZYSP_SD(this->m_pEconomy->getAmount() - price, 1) + "K";
        this->showPurchasePromptHelper(str, rm, CC_CALLBACK_2(Player::onPurchaseButtonPressed, this, true, property),
                                       CC_CALLBACK_2(Player::onPurchaseButtonPressed, this, false, property));
    }
    else
    {
        this->showMessageHelper("YOU DON NOT HAVE ENOUGH MONEY TO BUY THIS", 3);
        this->finishAction();
    }
}

void Player::acquireProperty(Property* property)
{
    const auto sell_value = property->getSellValue();
    if(m_pEconomy->isPayable(sell_value))
    {
        const std::string str = "Repurchase property for: " + ZYSP_SD(sell_value, 1) + "K";
        const std::string rm = "Remaining balance: " + ZYSP_SD(this->m_pEconomy->getAmount() - sell_value, 1) + "K";
        this->showPurchasePromptHelper(str, rm ,CC_CALLBACK_2(Player::onAcquireButtonPressed, this, true, property),
                                       CC_CALLBACK_2(Player::onAcquireButtonPressed, this, false, property));
    }
    else
    {
        this->showMessageHelper("YOU DON NOT HAVE ENOUGH MONEY TO REPURCHASE THIS", 3);
        this->finishAction();
    }
}

void Player::upgradeProperty(Property *property)
{
    const auto upgrade_value = property->getPrice();
    if(m_pEconomy->isPayable(upgrade_value))
    {
        const std::string str = "UPGRADE THIS PROPERTY FOR " + ZYSP_SD(upgrade_value, 1) + "K";
        const std::string rm = "Remaining balance: " + ZYSP_SD(this->m_pEconomy->getAmount() - upgrade_value, 1) + "K";
        this->showPurchasePromptHelper(str, rm, CC_CALLBACK_2(Player::onUpgradeButtonPressed, this, true, property),
                                       CC_CALLBACK_2(Player::onUpgradeButtonPressed, this, false, property));
    }
    else
    {
        this->showMessageHelper("YOU DON NOT HAVE ENOUGH MONEY TO UPGRADE THIS", 3);
        this->finishAction();
    }
}

void Player::sellPropertyForTax(Property* property)
{
    this->finishAction();
}

void Player::autoSellPropertyForTax(Property* property)
{

}
