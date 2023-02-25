#include "GlobalArena.h"

GlobalArena* GlobalArena::sp_pInstance = nullptr;

///// GLOBAL ARENA

//Constructor

GlobalArena::GlobalArena()
{

}

//Public

bool GlobalArena::init()
{
    return true;
}

void GlobalArena::log()
{

}

std::string GlobalArena::toString(int nTab)
{
    std::string ts;
    return ts;
}

void GlobalArena::setProperties(int nAmount, Size cSize)
{
    this->g_Size = cSize;
    this->g_nAmount = nAmount;
}
