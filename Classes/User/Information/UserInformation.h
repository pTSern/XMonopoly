#pragma once

#include "../../ZyUwU/ZyUwU.h"

USING_NS_ALL;

BEGIN_CREATE_REFCLASS(UserInformation, Ref)

public:
    CREATE_SET_GET_FUNC(setName, getName, std::string, m_sName);
    CREATE_SET_GET_FUNC(setEmail, getEmail, std::string, m_sEmail);
    CREATE_SET_GET_FUNC(setPhoneNumber, getPhoneNumber, std::string, m_sPhoneNumber);

    CREATE_GET_FUNC(getId, int, m_nId);
    CREATE_GET_FUNC(isNew, bool, m_bIsNew);
    CREATE_GET_FUNC(isBanned, bool, m_bIsBanned);

protected:
    int m_nId;
    std::string m_sName, m_sEmail, m_sPhoneNumber;
    bool m_bIsNew, m_bIsBanned;

END_CREATE_REFCLASS