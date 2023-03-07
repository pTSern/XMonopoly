#include "Coordinate.h"

//Constructor

Coordinate::Coordinate(Dir eDir, int nIndex) :
g_nIndex(nIndex), g_eDir(eDir)
{
    g_bIsFlip = true;
    if((int)g_eDir < 0) g_bIsFlip = false;
}

//Public

void Coordinate::log()
{
    CCLOG("CALL COORDINATE: %s", this->toString().c_str());
}

std::string Coordinate::toString(int nTab)
{
    std::string ts;
    std::string tab = ZY_SP_TAB(nTab);
    ts += (tab + " + Index: " + ZY_SP_NUMBER_TO_STRING(g_nIndex));
    ts += (tab + " + Dir: " + ZY_SP_NUMBER_TO_STRING((int)g_eDir));
    ts += (tab + " + Flip: " + std::to_string(g_bIsFlip));
    return ts;
}

void Coordinate::nextIndex()
{
    g_nIndex++;
}

//Operator
