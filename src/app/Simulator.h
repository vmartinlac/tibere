
#pragma once

#include <map>
#include "System.h"
#include "MetaMessage.h"

class Simulator
{
public:

    void simulate(
        std::map<std::string,MetaMessagePtr>& meta_messages,
        SystemPtr system);
};

