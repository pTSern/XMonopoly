#include "PlayerAction.h"

#include "Player/Player.h"
#include "Arena/Property/Property.h"
#include "Arena/SpecialArena/SpecialArena.h"

///] PayTaxAction

void PayTaxAction::execute(Player* player, Property* property)
{
    player->pay(property->getOwner(), property->getTax());
}

void PayTaxAction::execute(Player* player, SpecialArena* special)
{

}

///] PurchaseAction

void PurchaseAction::execute(Player* player, Property* property)
{
    player->showPurchasePrompt(property);
}

void PurchaseAction::execute(Player* player, SpecialArena* special)
{

}
