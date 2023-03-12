#pragma once

#include "ZyUwU/ZyUwU.h"

USING_NS_ALL;

#define BEGIN_CREATE_PLAYER_ACTION_REFCLASS(__NAME__)           \
class __NAME__ : public PlayerAction                            \
{                                                               \
public:                                                         \
static __NAME__* create()                                       \
{                                                               \
    auto ret = new (std::nothrow) __NAME__();                   \
    if(ret && ret->init())                                      \
    {                                                           \
        return ret;                                             \
    }                                                           \
    CC_SAFE_DELETE(ret);                                        \
    return nullptr;                                             \
}                                                               \
virtual bool init();                                            \
virtual void execute(Player* player, Property* property);       \
virtual void execute(Player* player, SpecialArena* special);    \

#define END_CREATE_PLAYER_ACTION_REFCLASS };



class Player;
class SpecialArena;
class Property;
class PlayerAction
{
public:
    virtual ~PlayerAction(){}
    virtual bool init() = 0;
    virtual void execute(Player* player, Property* property) = 0;
    virtual void execute(Player* player, SpecialArena* special) = 0;
};

BEGIN_CREATE_PLAYER_ACTION_REFCLASS(PayTaxAction)
END_CREATE_PLAYER_ACTION_REFCLASS

BEGIN_CREATE_PLAYER_ACTION_REFCLASS(PurchaseAction)
END_CREATE_PLAYER_ACTION_REFCLASS
