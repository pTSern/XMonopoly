#pragma once

#include "../TargetType.h"
#include "ZyUwU/ZyUwU.h"

USING_NS_ALL;

class NoTarget : public TargetType
{
public:
    NoTarget();

public:
    virtual bool init();
    virtual void log();
    virtual std::string toString(int nTab = 2);

protected:

};