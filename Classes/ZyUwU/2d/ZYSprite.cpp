#include <ZyUwU/platform/CCMacrosSupport.h>
#include "ZYSprite.h"
#include "../renderer/backend/Device.h"
#include "../renderer/ccShaders.h"
#include "ZYEffect.h"

NS_ZY_BEGIN
//Nova Sprite
ZYSprite::ZYSprite() :
m_cMemoryPosition(0,0)
//m_pEffect(nullptr)
{
	//m_vEffects.reserve(2);
}

ZYSprite::~ZYSprite()
{
	ZY_EZ_DE_LOG;
}

ZYSprite* ZYSprite::create(const std::string& pFileName, bool bIsScale)
{
	auto pElement = new (std::nothrow) ZYSprite();
	if (pElement && pElement->Sprite::initWithFile(pFileName))
	{
		pElement->autorelease();
		pElement->setName("ZYSPRITE");
		if(bIsScale) pElement->setScale();
		return pElement;
	}
	CC_SAFE_DELETE(pElement);
	return nullptr;
}

ZYSprite* ZYSprite::create(const char* pFileName, bool bIsScale)
{
	auto pElement = new (std::nothrow) ZYSprite();
	if (pElement && pElement->Sprite::initWithFile(pFileName))
	{
		pElement->autorelease();
		pElement->setName("ZYSPRITE");
		if(bIsScale) pElement->setScale();
		return pElement;
	}
	CC_SAFE_DELETE(pElement);
	return nullptr;
}
ZYSprite* ZYSprite::create(const std::string& filename, const Rect& rect, bool bIsScale)
{
	auto pRet = new (std::nothrow) ZYSprite();
	if(pRet && pRet->Sprite::initWithFile(filename, rect))
	{
		pRet->autorelease();
		pRet->setName("ZYSPRITE");
		if(bIsScale) pRet->setScale();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}

ZYSprite* ZYSprite::create(cocos2d::Texture2D *p)
{
	auto pE = new (std::nothrow) ZYSprite();
	if(pE && pE->initWithTexture(p))
	{
		pE->autorelease();
		pE->setName("ZYSPRITE");
		pE->config();
		return pE;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
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

	//m_vEffects.push_back(std::make_tuple(order, pEffect,QuadCommand()));
	m_vEffects.emplace_back(std::make_tuple(order, pEffect, QuadCommand()));

	std::sort(std::begin(m_vEffects), std::end(m_vEffects), tupleSort);
}

void ZYSprite::removeEffect()
{
	this->setEffect(ZYNullEffect::create());
}

bool ZYSprite::config()
{
	this->setScale();
	return true;
}

void ZYSprite::setScale()
{
	cocos2d::Sprite::setContentSize(cocos2d::Size(this->getContentSize().width * ZYDirector::getInstance()->getContentScaleWidth(), this->getContentSize().height * ZYDirector::getInstance()->getContentScaleHeight()));
}

bool ZYSprite::replaceTexture(ZYSprite *pSprite)
{
	if (!pSprite) return false;
	return this->replaceTexture(pSprite->getTexture());
}

bool ZYSprite::replaceTexture(Sprite *pSprite)
{
	if (!pSprite) return false;
	return this->replaceTexture(pSprite->getTexture());
}

bool ZYSprite::replaceTexture(cocos2d::Texture2D *pTexture)
{
	this->setTexture(pTexture);
	return true;
}

bool ZYSprite::replaceTexture(const std::string& sPath)
{
	if(!cocos2d::FileUtils::getInstance()->isFileExist(sPath)) return false;
	auto p = ZYSprite::create(sPath.c_str());
	return this->replaceTexture(p);
}

bool ZYSprite::replaceSprite(const std::string& sPath)
{
	if(!cocos2d::FileUtils::getInstance()->isFileExist(sPath)) return false;
	auto ret = ZYSprite::create(sPath.c_str());
	return replaceSprite(ret);
}

bool ZYSprite::replaceSprite(ZYSprite *pSprite)
{
	if(pSprite)
	{
		this->_fileName = pSprite->getResourceName();
		return this->replaceSprite(pSprite->getTexture());
	}
	return false;
}

bool ZYSprite::replaceSprite(Sprite *pSprite)
{
	if(!pSprite) return false;
	this->_fileName = pSprite->getResourceName();
	return this->replaceSprite(pSprite->getTexture());
}

bool ZYSprite::replaceSprite(Texture2D *pTexture)
{
	if(pTexture)
	{
		this->setContentSize(pTexture->getContentSize());
		this->replaceTexture(pTexture);
		return true;
	}
	return false;
}

void ZYSprite::loadPositionMemory()
{
	auto clone = m_cMemoryPosition;
	this->setPosition(clone);
}

ZYSprite* ZYSprite::clone()
{
	auto ret = ZYSprite::create("NULL/null.png");
	if(ret)
	{
		ret->replaceSprite(this);
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

NS_ZY_END