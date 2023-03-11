#include "ViewPoint.h"

#include "Player/Player.h"

//// Constructor

ViewPoint::ViewPoint()
{

}

//// Virtual

bool ViewPoint::init()
{
    return true;
}

void ViewPoint::log()
{

}

std::string ViewPoint::toString(int nTab)
{
    std::string ts;
    return ts;
}

//// Public

void ViewPoint::setViewPointPlayer(Player* player)
{
    this->disableCurrentViewPoint();

    this->m_pViewPointPlayer = player;
}

void ViewPoint::disableCurrentViewPoint()
{
    this->m_pViewPointPlayer->disable();
}

