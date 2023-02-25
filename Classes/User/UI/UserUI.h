#pragma once

#include "../../ZyUwU/ZyUwU.h"
#include "User/Helper.h"

USING_NS_ALL;


BEGIN_CREATE_INSTANCE_REFCLASS(UserUI, Node)

public:
    
public:
    FUNC_REPLACE_UI(setFrame, m_pFrame, p_sFrame);
    FUNC_REPLACE_UI(setAvatar, m_pAvatar, p_sAvatar);

    CREATE_SET_GET_FUNC(setFrame, getFrame, ZYSprite*, m_pFrame);
    CREATE_SET_GET_FUNC(setAvatar, getAvatar, ZYSprite*, m_pAvatar);
protected:



protected:
    ZYSprite *m_pFrame, *m_pAvatar;

private:
    std::string p_sFrame, p_sAvatar;

END_CREATE_INSTANCE_REFCLASS
