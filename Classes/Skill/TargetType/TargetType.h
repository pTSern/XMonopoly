#pragma once

#include "ZyUwU/ZyUwU.h"

USING_NS_ALL;


class TargetType
{
public:

public:
    TargetType();

public:
    virtual void log();
    virtual bool init();
    virtual std::string toString(int nTab = 2);

};