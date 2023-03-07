#pragma once

#include "../ZyUwU/ZyUwU.h"
#include "Enum.h"

USING_NS_ALL;

class Coordinate
{
public:
    Coordinate(Dir eDir, int nIndex);


public:
    CREATE_SET_GET_FUNC(setDir, getDir, Dir, g_eDir);
    CREATE_SET_GET_FUNC(setIndex, getIndex, int, g_nIndex);
    CREATE_SET_GET_FUNC(setFlip, getFlip, bool, g_bIsFlip);
    void nextIndex();
public:
    void log();
    std::string toString(int nTab = 2);

public:
    Dir g_eDir;
    int g_nIndex;
    bool g_bIsFlip;
};