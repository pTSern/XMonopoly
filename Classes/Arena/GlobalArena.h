#pragma once

#include "ZyUwU/ZyUwU.h"

USING_NS_ALL;

BEGIN_CREATE_INSTANCE_REFCLASS(GlobalArena, cocos2d::Ref)

public:
    static GlobalArena globalRightArena;
    static GlobalArena globalLefArena;
public:
    void setProperties(int nAmount, Size cSize);

    CREATE_GET_FUNC(getGlobalArenaSize, Size, g_Size);
    CREATE_GET_FUNC(getNumberArenaPerRow, int, g_nAmount);

public:
    Size g_Size;
    int g_nAmount;

END_CREATE_INSTANCE_REFCLASS
