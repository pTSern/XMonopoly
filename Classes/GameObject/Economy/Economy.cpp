#include "Economy.h"

//Constructor

Economy::Economy(std::string sName) :
p_sName(sName), p_fAmount(0)
{
}

//// Public

void Economy::addMoney(float fAmount)
{
    this->p_fAmount += fAmount;
}

void Economy::reduceMoney(float fAmount)
{
    this->p_fAmount -=fAmount;
}

bool Economy::payable(float fAmount)
{
    return this->p_fAmount >= fAmount;
}
//// Static

Economy Economy::IngameCoin = Economy("Coin");
Economy Economy::SPoint = Economy("SPoint");

