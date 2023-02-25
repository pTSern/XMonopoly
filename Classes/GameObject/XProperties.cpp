#include "XProperties.h"

//// Constructor

XProperties::XProperties() :
p_sName("X-Properties"),
p_nPriority(0),
p_nLocalZOrder(0),
p_nGlobalZOrder(0),
p_sDeputizeTexture("NULL/null.png")
{

}

// Destructor

XProperties::~XProperties()
{
    CCLOG("CALL XPROPERTIES: SELF_DESTRUCT: %s", p_sName.c_str());
}

//// Static
XProperties* XProperties::create()
{
    auto ret = new (std::nothrow) XProperties();
    if(ret && ret->init())
    {
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
//// Public

XProperties* XProperties::clone()
{
    auto ret = XProperties::create();
    if(ret)
    {
        ret->setName(this->p_sName);
        ret->setPriority(this->p_nPriority);
        return ret;
    }
    delete ret;
    return nullptr;
}

//Virtual

bool XProperties::init()
{
    return true;
}

void XProperties::log()
{

}

std::string XProperties::toString(int nTab)
{
    std::string ts;
    std::string tab = ZY_SP_TAB(nTab);
    ts += (tab + " + Name: " + p_sName);
    ts += (tab + " + Priority: " + ZYSP_NTS(p_nPriority));
    ts += (tab + " + Deputize Texture: " + p_sDeputizeTexture);
    return ts;
}
