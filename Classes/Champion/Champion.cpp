#include "Champion.h"

////Constructor

Champion::Champion() :
m_pStatics(nullptr),
m_pChampionStatics(ChampionStatics::create()),
//m_pIcon(ZYSprite::create(m_pProperties->getDeputizeTexture().c_str()))
m_pIcon(ZYSprite::create(m_sDeputizeTexture))
{

}

////Static

Champion* Champion::createWithProperties(const std::string& icon, Statics* pStatics, ChampionStatics* pChampStatics)
{
    auto ret = new (std::nothrow) Champion();
    if(ret && ret->init() && CC_FILEUTILS_GI->isFileExist(icon) && pStatics && pChampStatics)
    {
        ret->setDeputizeTexture(icon);
        ret->autorelease();
        ret->m_pIcon = ZYSprite::create(icon.c_str());
        auto str = "avatar/" + icon;
        ret->m_pAvatar = ZYSprite::create(str.c_str());
        ret->m_pChampionStatics = pChampStatics;
        ret->m_pStatics = pStatics;
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return ret;
}

////Public+

Champion* Champion::clone()
{
    auto ret = Champion::create();
    if(ret)
    {
        ret->m_pIcon = this->m_pIcon;
        ret->m_pChampionStatics = this->m_pChampionStatics;
        ret->m_pStatics = this->m_pStatics;

        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void Champion::setIcon(std::string sTexture)
{
    //if(sTexture != m_pProperties->getDeputizeTexture())
    if(sTexture != m_sDeputizeTexture)
    {
        setDeputizeTexture(sTexture);
        m_pIcon->replaceSprite(getDeputizeTexture());
    }
}

void Champion::setIconPosition(Point pos)
{
    m_pIcon->setPosition(pos);
}

//Virtual

bool Champion::init()
{
    if(!GameObject::init()) return false;
    //this->addChild(m_pIcon, m_pProperties->getLocalZOrder());
    return true;
}

void Champion::config()
{
    this->addChild(m_pIcon);
}

void Champion::log()
{
    ZY_EZ_LOG;
}

std::string Champion::toString(int nTab)
{
    std::string ts = GameObject::toString(nTab);
    std::string tab = ZY_SP_TAB(nTab);
    ZY_TSHP(ts, tab, nTab, " > Statics: ", m_pStatics);
    ZY_TSHP(ts, tab, nTab, " > Champion Statics: ", m_pChampionStatics);
    return ts;
}

void Champion::update(float dt)
{

}


