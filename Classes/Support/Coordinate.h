#pragma once

#include "../ZyUwU/ZyUwU.h"
#include "Enum.h"

USING_NS_ALL;

class Coordinate
{
public:
    static Coordinate UNKNOWN;

public:
    Coordinate(Dir eDir, int nIndex);

public:
    CREATE_SET_GET_FUNC(setDir, getDir, Dir, g_eDir);
    CREATE_SET_GET_FUNC(setIndex, getIndex, int, g_nIndex);
    CREATE_SET_GET_FUNC(setFlip, getFlip, bool, g_bIsFlip);
    void nextIndex();
    void prevIndex();

    /**
     *
     * @param dir The direction of the index.
     * @note Input NEGATIVE number to go to PREVIOUS index
     * @note Input POSITIVE number to go to NEXT index
     */
    void moveIndex(int dir);

public:
    void log();
    std::string toString(int nTab = 2);

public:
    bool operator== (Coordinate& target);

public:
    Dir g_eDir;
    int g_nIndex;
    bool g_bIsFlip;
};