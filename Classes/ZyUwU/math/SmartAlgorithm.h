#pragma once

#include "ZyUwU/platform/ZYMacros.h"
#include <iostream>
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
public:
    typedef SmartAlgorithm SmartAl;
};

NS_ZY_END