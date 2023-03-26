#pragma once

#include "../ZyUwU/ZyUwU.h"

USING_NS_ALL;

BEGIN_CREATE_INSTANCE_REFCLASS(User, Ref)

public:
    void loadEconomy();
    void loadAudio();
    void loadGameData();
    void loadInformation();
    void loadIngameUI();
    void loadUI();

protected:

END_CREATE_INSTANCE_REFCLASS