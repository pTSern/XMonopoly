#pragma once

#include "ZyUwU/platform/ZYMacros.h"
#include <iostream>

USING_NS_CC;
NS_ZY_BEGIN

class SmartAlgorithm
{
public:
    static int findGCD(int nFirst, int nSecond);

    /**
     * Calculate the Least Common Multiple with list of numbers
     *
     * @pragma list of numbers
     * @return the LCM of the number's list
     * @WARNING MUST input NULL at the end of function
     */
    static int findLCM(int nNum,...)  CC_REQUIRES_NULL_TERMINATION;
    static int findLCMWithVector(std::vector<int> vList);
    static bool checkPointOnLine(Point A, Point B, Point M);
    static float triangleArena(Point A, Point B, Point C);
    static bool isPointInside4Point(Point A, Point B, Point C, Point D, Point M);
    static bool isPointInsideMultiPoints(std::vector<Point>& vList, Point M);
public:
    typedef SmartAlgorithm SmartAl;
};

NS_ZY_END