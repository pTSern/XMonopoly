#include <ZyUwU/platform/CCMacrosSupport.h>
#include "ZYSprite.h"
#include "../renderer/backend/Device.h"
#include "../renderer/ccShaders.h"
#include "ZYEffect.h"

NS_ZY_BEGIN
//Nova Sprite
ZYSprite::ZYSprite() :
m_cMemoryPosition(0,0),
m_pEffect(nullptr)
{
	m_vEffects.reserve(2);
}

ZYSprite::~ZYSprite()
{
	for(auto &tuple: m_vEffects)
	{
		std::get<1>(tuple)->release();
	}
	CC_SAFE_RELEASE(m_pEffect);
}

ZYSprite* ZYSprite::create(const char* pFileName, bool bIsScale)
{
	ZYSprite* pElement = new (std::nothrow) ZYSprite();
	if (pElement && pElement->initWithFile(pFileName))
	{
		pElement->autorelease();
        if(bIsScale) pElement->config();
		return pElement;
	}
	CC_SAFE_DELETE(pElement);
	return nullptr;
}

ZYSprite* ZYSprite::create(cocos2d::Texture2D *p)
{
	ZYSprite* pE = new (std::nothrow) ZYSprite();
	if(pE && pE->initWithTexture(p))
	{
		pE->autorelease();
		pE->config();
		return pE;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

void ZYSprite::updateUniforms(backend::ProgramState *programState)
{
	float time = CCDR_GI->getTotalFrames() * CCDR_GI->getAnimationInterval();

	Vec4 uTime(time / 10.0f, time, time * 2.0f, time * 4.0f);
	Vec4 sinTime(time / 8.0f, time / 4.0f, time / 2.0f, sinf(time));
	Vec4 cosTime(time / 8.0f, time / 4.0f, time / 2.0f, cosf(time));

	SET_UNIFORM(programState, "u_Time", uTime);
	SET_UNIFORM(programState, "u_SinTime", sinTime);
	SET_UNIFORM(programState, "u_CosTime", cosTime);
}

//// Public

//virtual

void ZYSprite::setPosition(const cocos2d::Vec2 &pos, cocos2d::Vec2 newAnchor)
{
	auto cDA = getDifferentAnchorPoint(newAnchor);
	auto nPos = cocos2d::Point(pos.x - cDA.x * _contentSize.width, pos.y - cDA.y * _contentSize.height);
	ZYSprite::setPosition(nPos);
}

void ZYSprite::setPosition(const cocos2d::Vec2 &pos)
{
	m_cMemoryPosition = _position;

	cocos2d::Sprite::setPosition(pos);
}

void ZYSprite::setPosition(const float xx, const float yy)
{
	//ZYSprite::setPosition(cocos2d::Point(xx,yy));
	m_cMemoryPosition = _position;

	cocos2d::Sprite::setPosition(xx,yy);
}

std::string ZYSprite::toString(int nTab)
{
	std::string ts;
	std::string tab = ZYSP_T(nTab);
	ts += (tab + " + Size: " + ZYSP_STS(getContentSize()));
	ts += (tab + " + Position: " + ZYSP_VTS(getPosition()));
	ts += (tab + " + Memory Position: " + ZYSP_VTS(m_cMemoryPosition));
	return ts;
}

void ZYSprite::log()
{
	ZY_EZ_LOG;
}

void ZYSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
#if CC_USE_CULLING
	_insideBounds = (flags & FLAGS_TRANSFORM_DIRTY) ? renderer->checkVisibility(transform,
																				_contentSize)
													: _insideBounds;
	if (_insideBounds)
#endif
	{
		int index = 0;
		for (auto &effect: m_vEffects)
		{
			if (std::get<0>(effect) >= 0) break;
			auto *pProgramState = std::get<1>(effect)->getProgramState();
			if (pProgramState)
			{
				QuadCommand &quadCommand = std::get<2>(effect);
				quadCommand.init(_globalZOrder, _texture, _blendFunc, &_quad, 1, transform, flags);
				updateUniforms(pProgramState);
				renderer->addCommand(&quadCommand);
			}
			index++;
		}

		//Normal effect: order = 0
		_trianglesCommand.init(_globalZOrder, _texture, _blendFunc, _polyInfo.triangles, transform,
							   flags);

		updateUniforms(_trianglesCommand.getPipelineDescriptor().programState);
		renderer->addCommand(&_trianglesCommand);

		// positive effects: order >= 0
		for (auto it = std::begin(m_vEffects) + index; it != std::end(m_vEffects); ++it)
		{
			QuadCommand &q = std::get<2>(*it);
			auto *programState = std::get<1>(*it)->getProgramState();
			updateUniforms(programState);
			q.init(_globalZOrder, _texture, _blendFunc, &_quad, 1, transform, flags);
			q.getPipelineDescriptor().programState = programState;
			renderer->addCommand(&q);

			index++;
		}
	}
}
//public

void ZYSprite::setEffect(ZYEffect *pEffect)
{
	if(m_pEffect != pEffect)
	{
		pEffect->castTarget(this);

		CC_SAFE_RELEASE(m_pEffect);
		m_pEffect = pEffect;
		CC_SAFE_RETAIN(pEffect);

		setProgramState(m_pEffect->getProgramState());
	}
}

void ZYSprite::addEffect(ZYEffect *pEffect, ssize_t order)
{
	pEffect->retain();
	pEffect->castTarget(this);

	m_vEffects.push_back(std::make_tuple(order, pEffect,QuadCommand()));

	std::sort(std::begin(m_vEffects), std::end(m_vEffects), tupleSort);
}

bool ZYSprite::config()
{
	this->setScale();
	return true;
}

cocos2d::Point ZYSprite::getContentPositionWithNewAnchorPoint(cocos2d::Point cNewAnchorPoint)
{
	auto DPoint = this->getDifferentAnchorPoint(cNewAnchorPoint);


	auto xx = this->getPositionX() + (this->getContentSize().width * DPoint.x);
	auto yy = this->getPositionY() + (this->getContentSize().height * DPoint.y);

	return cocos2d::Point(xx,yy);
}

cocos2d::Point ZYSprite::getDifferentAnchorPoint(cocos2d::Point cNewAnchorPoint)
{
	if(this->getAnchorPoint() == cNewAnchorPoint) return cocos2d::Point::ZERO;

	cocos2d::Point rep(cNewAnchorPoint.x - this->getAnchorPoint().x, cNewAnchorPoint.y - this->getAnchorPoint().y);
	return rep;
}

cocos2d::Point ZYSprite::getContentPositionMiddleTop()
{
	return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE_TOP);
}

cocos2d::Point ZYSprite::getContentPositionMiddleBottom()
{
	return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE_BOTTOM);
}

cocos2d::Point ZYSprite::getContentPositionTopLeft()
{
	return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_TOP_LEFT);
}

cocos2d::Point ZYSprite::getContentPositionTopRight()
{
	return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_TOP_RIGHT);
}

cocos2d::Point ZYSprite::getContentPositionBottomRight()
{
	return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_BOTTOM_RIGHT);
}

cocos2d::Point ZYSprite::getContentPositionBottomLeft()
{
	return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_BOTTOM_LEFT);
}

cocos2d::Point ZYSprite::getContentPositionMiddle()
{
	return this->getContentPositionWithNewAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE);
}

void ZYSprite::setScale()
{
	cocos2d::Sprite::setContentSize(cocos2d::Size(this->getContentSize().width * ZYDirector::getInstance()->getContentScaleWidth(), this->getContentSize().height * ZYDirector::getInstance()->getContentScaleHeight()));
}

bool ZYSprite::initWithFile(const std::string& filename)
{
	if (!this->isValidFile(filename))
	{
		CCLOG("Call ZYSprite: This file doesn't exist");
		return false;
	}
	return this->cocos2d::Sprite::initWithFile(filename);
}

bool ZYSprite::replaceTexture(ZYSprite *pSprite)
{
	return this->replaceTexture(pSprite->getTexture());
}

bool ZYSprite::replaceTexture(cocos2d::Texture2D *pTexture)
{
	this->setTexture(pTexture);
	return true;
}

bool ZYSprite::replaceTexture(std::string sPath)
{
	if(!cocos2d::FileUtils::getInstance()->isFileExist(sPath)) return false;
	auto p = ZYSprite::create(sPath.c_str());
	return this->replaceTexture(p);
}

bool ZYSprite::replaceSprite(std::string sPath)
{
	if(!cocos2d::FileUtils::getInstance()->isFileExist(sPath)) return false;
	auto ret = ZYSprite::create(sPath.c_str());
	if(ret)
	{
		this->setContentSize(ret->getContentSize());
		this->replaceTexture(ret->getTexture());
		return true;
	}
	CC_SAFE_DELETE(ret);
	return false;
}

void ZYSprite::loadPositionMemory()
{
	auto clone = m_cMemoryPosition;
	this->setPosition(clone);
}

NS_ZY_END