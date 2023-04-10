#include "Coordinate.h"
#include "GameMaster/GameMaster.h"

//Constructor

Coordinate::Coordinate(Dir eDir, int nIndex) :
g_nIndex(nIndex), g_eDir(eDir)
{
    g_bIsFlip = true;
    if((int)g_eDir < 0) g_bIsFlip = false;
}

///] Static

Coordinate Coordinate::UNKNOWN(Dir::UK, -1);

///] Public

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
    if(g_nIndex > GM_GI->getMaxCoordIndex())
    {
        g_nIndex -= (GM_GI->getMaxCoordIndex() + 1);
    }
}

void Coordinate::prevIndex()
{
    g_nIndex--;
    if(g_nIndex < 0)
    {
        g_nIndex += (GM_GI->getMaxCoordIndex() + 1);
    }
}

void Coordinate::moveIndex(int dir)
{
    if(dir < 0)
    {
        prevIndex();
    } else
    {
        nextIndex();
    }
}

///] Operator

bool Coordinate::operator==(Coordinate& target)
{
    if(&target == this) return true;
    if(target.g_eDir == this->g_eDir && target.g_nIndex == this->g_nIndex) return true;
    return false;
}
