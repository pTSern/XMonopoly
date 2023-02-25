#include "ZYNodeExtend.h"

NS_ZY_BEGIN

cocos2d::Point ZYNodeExtend::getContentPositionWithNewAnchorPoint(cocos2d::Point cNewAnchorPoint)
{
    auto DPoint = this->getDifferentAnchorPoint(cNewAnchorPoint);


    auto xx = this->getPositionX() + (this->getContentSize().width * DPoint.x);
    auto yy = this->getPositionY() + (this->getContentSize().height * DPoint.y);

    return cocos2d::Point(xx,yy);
}

cocos2d::Point ZYNodeExtend::getDifferentAnchorPoint(cocos2d::Point cNewAnchorPoint)
{
    if(this->getAnchorPoint() == cNewAnchorPoint) return cocos2d::Point::ZERO;

    cocos2d::Point rep(cNewAnchorPoint.x - this->getAnchorPoint().x, cNewAnchorPoint.y - this->getAnchorPoint().y);
    return rep;
}

cocos2d::Point ZYNodeExtend::getContentPositionMiddleTop()
{
    return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE_TOP);
}

cocos2d::Point ZYNodeExtend::getContentPositionMiddleBottom()
{
    return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE_BOTTOM);
}

cocos2d::Point ZYNodeExtend::getContentPositionTopLeft()
{
    return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_TOP_LEFT);
}

cocos2d::Point ZYNodeExtend::getContentPositionTopRight()
{
    return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_TOP_RIGHT);
}

cocos2d::Point ZYNodeExtend::getContentPositionBottomRight()
{
    return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_BOTTOM_RIGHT);
}

cocos2d::Point ZYNodeExtend::getContentPositionBottomLeft()
{
    return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_BOTTOM_LEFT);
}

cocos2d::Point ZYNodeExtend::getContentPositionMiddle()
{
    return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE);
}

NS_ZY_END