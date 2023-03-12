#include "ZYSupport2D.h"

NS_ZY_BEGIN

Point ZYSupport2D::getContentPositionWithNewAnchorPoint(cocos2d::Point cNewAnchorPoint)
{
    auto DPoint = this->getDifferentAnchorPoint(cNewAnchorPoint);

    auto xx = this->getPositionX() + (this->getContentSize().width * DPoint.x);
    auto yy = this->getPositionY() + (this->getContentSize().height * DPoint.y);
    return cocos2d::Point(xx, yy);
}

Point ZYSupport2D::getDifferentAnchorPoint(cocos2d::Point cNewAnchorPoint)
{
    if(this->getAnchorPoint() == cNewAnchorPoint) return cocos2d::Point::ZERO;
    Point rep(cNewAnchorPoint.x - this->getAnchorPoint().x, cNewAnchorPoint.y - this->getAnchorPoint().y);
    return rep;
}

Point ZYSupport2D::getContentPositionMiddleTop()
{
    return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE_TOP);
}

Point ZYSupport2D::getContentPositionMiddleBottom()
{
    return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE_BOTTOM);
}

Point ZYSupport2D::getContentPositionMiddleRight()
{
    return this->getContentPositionWithNewAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
}

Point ZYSupport2D::getContentPositionMiddleLeft()
{
    return this->getContentPositionWithNewAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
}

    Point ZYSupport2D::getContentPositionTopLeft()
{
    return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_TOP_LEFT);
}

Point ZYSupport2D::getContentPositionTopRight()
{
    return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_TOP_RIGHT);
}

Point ZYSupport2D::getContentPositionBottomRight()
{
    return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_BOTTOM_RIGHT);
}

Point ZYSupport2D::getContentPositionBottomLeft()
{
    return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_BOTTOM_LEFT);
}

Point ZYSupport2D::getContentPositionMiddle()
{
    return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE);
}

NS_ZY_END