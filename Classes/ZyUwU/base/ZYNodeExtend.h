#pragma once

#include "cocos2d.h"
#include "ZyUwU/platform/ZYMacros.h"
#include "ZyUwU/2d/ZYSprite.h"

USING_NS_CC;

NS_ZY_BEGIN

class ZYNodeExtend : public Node
{
public:
    cocos2d::Point getContentPositionWithNewAnchorPoint(cocos2d::Point cNewAnchorPoint);

    cocos2d::Point getContentPositionMiddleTop();
    cocos2d::Point getContentPositionMiddleBottom();
    cocos2d::Point getContentPositionTopLeft();
    cocos2d::Point getContentPositionTopRight();
    cocos2d::Point getContentPositionBottomRight();
    cocos2d::Point getContentPositionBottomLeft();
    cocos2d::Point getContentPositionMiddle();

    cocos2d::Point getDifferentAnchorPoint(cocos2d::Point cNewAnchorPoint);
private:
    //friend zy::ZYSprite;
};

NS_ZY_END