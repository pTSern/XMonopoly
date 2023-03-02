#pragma once

#include "ZyUwU/platform/ZYMacros.h"
#include "cocos2d.h"

USING_NS_CC;

NS_ZY_BEGIN

class ZYSupport2D
{
public:
    Point getContentPositionWithNewAnchorPoint(Point cNewAnchorPoint);

    Point getContentPositionMiddleTop();
    Point getContentPositionMiddleBottom();
    Point getContentPositionTopLeft();
    Point getContentPositionTopRight();
    Point getContentPositionBottomRight();
    Point getContentPositionBottomLeft();
    Point getContentPositionMiddle();

    Point getDifferentAnchorPoint(Point cNewAnchorPoint);

public:
    virtual const Vec2& getAnchorPoint() const = 0;
    virtual float getPositionX() const = 0;
    virtual float getPositionY() const = 0;
    virtual const Size& getContentSize() const = 0;

};

NS_ZY_END