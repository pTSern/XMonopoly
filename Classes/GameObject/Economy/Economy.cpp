#include "Economy.h"

//Constructor

Economy::Economy(std::string sName)
{
    this->p_sName = sName;
}

//// Public

//Virtual

//bool Economy::init()
//{
//    p_fAmount = 0;
//    return true;
//}

//void Economy::log()
//{
//    ZY_EZ_LOG;
//}
//
//std::string Economy::toString(int nTab)
//{
//    std::string ts;
//    std::string tab = ZY_SP_TAB(nTab);
//    ts += tab + " + Name: " + p_sName;
//    ts += tab + " + Amount: " + ZY_SP_NUMBER_TO_STRING(p_fAmount);
//    return ts;
//}

//Static

Economy Economy::IngameCoin = Economy("Coin");
Economy Economy::SPoint = Economy("SPoint");

