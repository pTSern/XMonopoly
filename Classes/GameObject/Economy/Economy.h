#pragma once

#include "../../ZyUwU/ZyUwU.h"

USING_NS_ALL;


class Economy
{
public:
    Economy(std::string sName);

public:
    static Economy IngameCoin;
    static Economy SPoint;

public:
    CREATE_GET_FUNC(getName, std::string, p_sName);

    CREATE_SET_GET_FUNC(setAmount, getAmount, float, p_fAmount);

private:
    float p_fAmount;
    std::string p_sName;
};