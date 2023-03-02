#include "WarpType.h"

//// Constructor

WarpType::WarpType() :
p_eType(Type::NONE)
{
    memset(&_field, 0, sizeof(_field));
}

WarpType::WarpType(NoTarget* ret) :
p_eType(Type::NO_TARGET)
{
    _field.pNoTarget = ret;
}