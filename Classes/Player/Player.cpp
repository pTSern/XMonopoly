#include "Player.h"
#include "Arena/Arena.h"
#include "Support/GameConstant.h"
#include "Arena/Property/Property.h"
#include "GameMaster/GameMaster.h"

//// Constructor

Player::Player() :
m_pEconomy(Economy::IngameCoin),
m_pSelectingObject(nullptr),
m_eType(SelectType::NONE),
m_Color(Color4F::RED),
m_eAction(PlayerAction::IDLE)
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

    m_pEconomy.setAmount(5000);
    m_pMoney = ZYLabel::createWithTTF("", globalFont, 30);
    m_pMoney->setColor(Color3B::GREEN);
    this->addChild(m_pMoney);
    m_pMoney->setPosition(Point(ZYDR_GVS/6));
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
    m_pMoney->setString("$: " + ZYSP_SD(m_pEconomy.getAmount(), 1) + "K");
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

bool Player::buyingProperty(Property *pro)
{

}

bool Player::yesOrNoSelector(std::string sMessage)
{
    return true;
}

void Player::onLandArena(Arena* arena)
{
    auto pro = dynamic_cast<Property*>(arena);
    if(pro)
    {
        if(!pro->hasOwner())
        {
            if(m_pEconomy.payable(pro->getPrice()))
            {
                std::string s = "WOULD U LIKE TO PURCHASE THIS PROPERTY\nFOR " + ZYSP_SD(pro->getPrice(), 1) + "K";
                auto font = ZYLabel::createWithTTF(s, globalFont, 50);
                font->setTag(77);
                font->setColor(Color3B::BLUE);
                this->addChild(font);
                font->setPosition(Point(ZYDR_GVS.width/2, ZYDR_GVS.height/3*2));
                font->setHorizontalAlignment(TextHAlignment::CENTER);

                auto button = ui::Button::create("button/n.png", "button/p.png");
                button->setTitleText("YES");
                this->addChild(button);
                button->setTag(88);
                button->setPosition(Point(ZYDR_GVS.width/4, ZYDR_GVS.height/4));

                auto no = ui::Button::create("button/n.png", "button/p.png");
                no->setTitleText("NO");
                no->setPosition(Point(ZYDR_GVS.width/4*3, ZYDR_GVS.height/4));
                this->addChild(no);
                no->setTag(99);

                button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
                                              {
                                                  if (type == ui::Widget::TouchEventType::ENDED)
                                                  {
                                                      auto prop = dynamic_cast<Property*>(this->m_pControllingChampion->getLandingArena());
                                                      if(prop)
                                                      {
                                                          this->m_pEconomy.reduceMoney(prop->getPrice());
                                                          this->moneyIndicator(prop->getPrice(), true);
                                                          this->m_vOwn.push_back(prop);
                                                          prop->setOwner(this);
                                                          prop->addDrawRectOrder();
                                                          prop->setRectColor(m_Color);
                                                      }

                                                      auto b = this->getChildByTag(88);
                                                      auto n = this->getChildByTag(99);
                                                      auto f = this->getChildByTag(77);
                                                      b->removeFromParentAndCleanup(true);
                                                      n->removeFromParentAndCleanup(true);
                                                      f->removeFromParentAndCleanup(true);
                                                      this->finishAction();
                                                  }
                                              });
                no->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
                                          {
                                              if (type == ui::Widget::TouchEventType::ENDED)
                                              {
                                                  auto b = this->getChildByTag(88);
                                                  auto n = this->getChildByTag(99);
                                                  auto f = this->getChildByTag(77);
                                                  b->removeFromParentAndCleanup(true);
                                                  n->removeFromParentAndCleanup(true);
                                                  f->removeFromParentAndCleanup(true);
                                                  this->finishAction();
                                              }
                                          });
            }
        }
        else
        {
            if(m_pEconomy.payable(pro->getTax()))
            {
                this->pay(pro->getOwner(), pro->getTax());
                this->finishAction();
            }
            else this->lose();
        }
        //if(pro->hasOwner()) this->pay(pro->getOwner(), pro->getTax());
        return;
    }
    this->finishAction();
}

void Player::pay(Player* player, float money)
{
    if(m_pEconomy.payable(money))
    {
        this->m_pEconomy.reduceMoney(money);
        this->moneyIndicator(money, true);

        player->receiveMoney(money);
    }
}

void Player::receiveMoney(float fAmount)
{
    this->m_pEconomy.addMoney(fAmount);
    this->moneyIndicator(fAmount, false);
}

void Player::addChampion(ChampionInGame* pChamp)
{
    if(pChamp)
    {
        m_vChampions.push_back(pChamp);
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
    ///> disable money label
    this->m_pMoney->setVisible(false);

    ///> disable controlling champion
    if(m_pControllingChampion)
    {
        this->m_pControllingChampion->disable();
        //this->m_pControllingChampion = nullptr;
    }
}

void Player::enable()
{
    this->m_pMoney->setVisible(true);
}

void Player::lose()
{

}

void Player::moneyIndicator(float money, bool isPay)
{
    auto color = Color3B::GREEN;
    std::string text = "$" + ZYSP_SD(money, 1) + "K";
    std::string pre = "+";
    if(isPay)
    {
        color = Color3B::RED;
        pre = "-";
    }
    auto font = ZYLabel::createWithTTF(pre + text, globalFont, 20);
    font->setColor(color);
    this->addChild(font, 5);
    font->setPosition(m_pControllingChampion->getPosition());
    auto moveby = MoveBy::create(0.5, Point(0, m_pControllingChampion->getIcon()->getContentSize().height));
    auto fadeout = FadeOut::create(0.5);
    auto remove = RemoveSelf::create(true);
    auto seq = Sequence::create(moveby, fadeout, remove, nullptr);
    font->runAction(seq);
}

void Player::startTurn(ChampionInGame* child)
{
    this->setControlChampion(child);
    this->setChampionViewPoint(child);
}

void Player::endTurn()
{
}