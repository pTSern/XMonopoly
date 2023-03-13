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
    m_pEconomy->setAmount(500);
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

    ///> disable controlling champion
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

void Player::showMessageHelper(const std::string& message)
{
    auto label = ZYLabel::createWithTTF(message, globalFont, 50);
    label->setTag(77);
    this->m_vRemoveByTagList.emplace_back(label->getTag());
    label->setColor(Color3B::BLUE);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    label->setPosition(Point(ZYDR_TGVS.width/2, ZYDR_TGVS.height/3*2));
    this->addChild(label);
}

void Player::showMessageHelper(const std::string& message, const float duration)
{
    auto label = ZYLabel::createWithTTF(message, globalFont, 50);
    label->setColor(Color3B::BLUE);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    label->setPosition(Point(ZYDR_TGVS.width/2, ZYDR_TGVS.height/3*2));
    this->addChild(label);

    auto fade_out = FadeOut::create(duration);
    auto remove = RemoveSelf::create(true);
    auto se = Sequence::create(fade_out, remove, nullptr);
    label->runAction(se);
}

void Player::showPurchasePromptHelper(const std::string& message, const ui::Widget::ccWidgetTouchCallback& yesCallBack, const ui::Widget::ccWidgetTouchCallback& noCallback)
{
    this->showMessageHelper(message);

    auto yes = this->createPurchaseButton("YES", 88, ZYDR_TGVS/4);
    yes->addTouchEventListener(yesCallBack);

    auto no = this->createPurchaseButton("NO", 99, Point(ZYDR_TGVS.width/4*3, ZYDR_TGVS.height/4));
    no->addTouchEventListener(noCallback);

    this->addChild(yes, 5);
    this->addChild(no, 5);
}

ui::Button* Player::createPurchaseButton(const std::string& title, int tag, const Point& pos)
{
    auto button = ui::Button::create("button/n.png", "button/p.png");
    button->setTitleText(title);
    button->setPosition(pos);
    button->setTag(tag);
    this->m_vRemoveByTagList.emplace_back(tag);
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
    if(m_pEconomy->isPayable(property->getPrice()))
    {
        const std::string str = "WOULD YOU LIKE TO BUY THIS\nPROPERTY FOR " + ZYSP_SD(property->getPrice(), 1) + "K";
        this->showPurchasePromptHelper(str, CC_CALLBACK_2(Player::onPurchaseButtonPressed, this, true, property), CC_CALLBACK_2(Player::onPurchaseButtonPressed, this, false, property));
    }
    else
    {
        this->showMessageHelper("YOU DON NOT HAVE ENOUGH MONEY TO BUY THIS", 3);
        this->finishAction();
    }
}
