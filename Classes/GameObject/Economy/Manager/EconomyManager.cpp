#include "EconomyManager.h"
#include "Support/GameConstant.h"

///] Constructor

IngameEconomyManager::IngameEconomyManager() :
m_economy(Economy::IngameCoin),
m_pLabel(nullptr),
m_pIcon(nullptr),
m_bIsExecuteIndicator(false)
{

}

///] Static

IngameEconomyManager* IngameEconomyManager::createIngameEconomy()
{
    auto ret = new (std::nothrow) IngameEconomyManager();
    if(ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

///] Virtual

bool IngameEconomyManager::init()
{
    auto config = TTFConfig(defaultTTFConfig);
    config.bold = true;
    config.fontSize = 30;

    this->m_pLabel = ZYLabel::createWithTTF(config, "", TextHAlignment::CENTER);

    if(!m_pLabel) return false;

    this->addChild(m_pLabel);
    m_economy = Economy::IngameCoin;

    m_pIcon = ZYSprite::create("ui/economy/icon.png");
    this->addChild(m_pIcon);

    this->scheduleUpdate();
    return true;
}

void IngameEconomyManager::log()
{
    ZY_EZ_LOG;
}

std::string IngameEconomyManager::toString(int nTab)
{
    std::string ts;
    return ts;
}

void IngameEconomyManager::update(float dt)
{
    this->m_pLabel->setString("$: " + ZYSP_SRF(m_economy.getAmount(), 2)  + " ");
    auto pos = (m_pLabel->getContentPositionMiddleRight());
    this->m_pIcon->setPosition(Point(pos.x + m_pIcon->getContentSize().width/2, pos.y));
}

///] Public

// Struct

IgEcoMng::MoveDirection::MoveDirection(MoveHDirection hDir, MoveVDirection vDir)
{
    this->g_eHDir = hDir;
    this->g_eVDir = vDir;
}

void IngameEconomyManager::setPosition(const float xx, const float yy)
{
    this->m_pLabel->setPosition(xx, yy);
}

void IngameEconomyManager::setPosition(Point pos)
{
    this->m_pLabel->setPosition(pos);
}

void IngameEconomyManager::executeIndicator(const float& money, const bool& isPay)
{
    if(m_pLabel->isVisible())
    {
        const auto pos = this->m_pLabel->getPosition();

        auto config = TTFConfig(defaultTTFConfig);
        config.fontSize = 25;

        std::string text = "$" + ZYSP_SD(money, 1) + "K";
        auto pre = isPay ? "-" : "+";
        auto color = isPay ? Color3B::RED : Color3B::GREEN;

        auto font = ZYLabel::createWithTTF(config, pre + text);
        font->setColor(color);
        this->addChild(font);
        font->setPosition(m_pLabel->getPosition());

        if(m_bIsExecuteIndicator)
        {
            font->setVisible(false);
            const auto delay = DelayTime::create(animation_indicator_duration/9);
            const auto remove = RemoveSelf::create(true);
            const auto recall = CallFunc::create(
                    [&, money, isPay]()
                    {
                        this->executeIndicator(money, isPay);
                    }
            );
            const auto seq = Sequence::create(delay, recall, remove, nullptr);
            font->runAction(seq);
            return;
        }

        //const auto size = m_pLabel->getContentSize();
        const auto size = 20;
        auto move_dir = autoSelectMoveDirection();
        const auto move_by = MoveBy::create(animation_indicator_duration/3, Point(size * move_dir.hDirectionToFloat() * 1,
                                                                                  size * move_dir.vDirectionToFloat() * 3));
        auto callback = CallFunc::create(
                [&]()
                {
                    this->m_bIsExecuteIndicator = false;
                }
        );
        const auto fadeout = FadeOut::create(animation_indicator_duration/3*2);
        const auto remove = RemoveSelf::create(true);

        const auto seq = Sequence::create(move_by, fadeout, callback, remove, nullptr);
        font->runAction(seq);

        m_bIsExecuteIndicator = true;
    }
}

void IngameEconomyManager::setAmount(float amount)
{
    this->m_economy.setAmount(amount);
}

bool IngameEconomyManager::pay(IngameEconomyManager *target, float money, bool animate)
{
    if(!this->pay(money, animate)) return false;

    target->receive(money, animate);
    return true;
}


void IngameEconomyManager::receive(float money, bool animate)
{
    this->m_economy.addMoney(money);
    if(animate ) this->executeIndicator(money, false);
}

bool IngameEconomyManager::isPayable(float money)
{
    return this->m_economy.payable(money);
}

bool IngameEconomyManager::pay(float money, bool animate)
{
    if(!this->isPayable(money)) return false;

    this->m_economy.reduceMoney(money);
    if(animate) this->executeIndicator(money, true );

    return true;
}

void IngameEconomyManager::disable()
{
    //this->m_pLabel->setVisible(false);
    //this->m_pIcon->setVisible(false);
    this->setVisible(false);
}

void IngameEconomyManager::enable()
{
    //this->m_pLabel->setVisible(true);
    //this->m_pIcon->setVisible(true);
    this->setVisible(true);
}

///] Protected

IgEcoMng::MoveDirection IngameEconomyManager::autoSelectMoveDirection()
{
    const auto& labelPos = this->m_pLabel->getPosition();
    const bool isLeftHalf = labelPos.x <= ZYDR_TGVS.width / 2;
    const bool isTopHalf = labelPos.y <= ZYDR_TGVS.height / 2;
    return {(isLeftHalf ? MoveHDirection::NONE : MoveHDirection::LEFT),
            (isTopHalf ? MoveVDirection::TOP : MoveVDirection::NONE)};
}
