#include "BotPlayer.h"
#include "Arena/Property/Property.h"
#include "ChampionInGame/AI/BotChampion.h"

///] Constructor

BotPlayer::BotPlayer()
{

}

///] Virtual

bool BotPlayer::init()
{
    if(!Player::init()) return false;

    //auto champ = TesterBot::create();
    this->setTheColor(Color4F::RED);
    this->setName("BOT PLAYER");
    //this->addChampion(champ);

    return true;
}

void BotPlayer::log()
{
    ZY_EZ_LOG;
}

std::string BotPlayer::toString(int nTab)
{
    return Player::toString(nTab);
}

void BotPlayer::purchaseProperty(Property* property)
{
    const auto price = property->getPrice();
    if(m_pEconomy->isPayable(price))
    {
        Player::onPurchaseButtonPressed(this, ui::Widget::TouchEventType::ENDED, true, property);
    }
    else
    {
        showMessageHelper(getName() + " DO NOT HAVE ENOUGH MONEY TO BUY THIS PROPERTY", 1.0f);
    }
}

void BotPlayer::acquireProperty(Property* property)
{
    const auto sell_value = property->getSellValue();
    if(m_pEconomy->isPayable(sell_value))
    {
        Player::onAcquireButtonPressed(this, ui::Widget::TouchEventType::ENDED, true, property);
    }
    else
    {
        this->showMessageHelper(getName() + " DO NOT HAVE ENOUGH MONEY TO REPURCHASE THIS", 1.0f);
    }
}

void BotPlayer::upgradeProperty(Property* property)
{
    const auto upgrade_value = property->getPrice();
    if(m_pEconomy->isPayable(upgrade_value))
    {
        Player::onUpgradeButtonPressed(this, ui::Widget::TouchEventType::ENDED, true, property);
    }
    else
    {
        this->showMessageHelper(getName() + " YOU DON NOT HAVE ENOUGH MONEY TO UPGRADE THIS", 1.0f);
    }
}
