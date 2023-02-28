#include "Champion.h"

////Constructor

Champion::Champion() :
m_pStatics(nullptr),
m_pChampionStatics(ChampionStatics::create()),
m_pIcon(ZYSprite::create(m_pProperties->getDeputizeTexture().c_str()))
{

}

////Static

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

////Public+

void Champion::setIcon(std::string sTexture)
{
    if(sTexture != m_pProperties->getDeputizeTexture())
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


