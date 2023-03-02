#include "SkillType.h"

//// Constructor

SkillType::SkillType() :
m_eType(Type::PASSIVE)
{

}

SkillType::SkillType(Type type) : m_eType(type)
{

}

//// Static

SkillType* SkillType::createWithProperties(Type type)
{
    auto ret = new (std::nothrow) SkillType(type);
    if(ret && ret->init())
    {
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//// Virtual

bool SkillType::init()
{
    return true;
}

void SkillType::log()
{
    ZY_EZ_LOG;
}

std::string SkillType::toString(int nTab)
{
    std::string ts;
    return ts;
}

//// Public

std::string SkillType::toDescription()
{
    std::string td;
    switch (m_eType) {
        case Type::ACTIVE:
            td = "ACTIVE";
            break;
        case Type::PASSIVE:
            td = "PASSIVE";
            break;
        case Type::TOGGLE:
            td = "TOGGLE";
            break;
    }
    return td;
}