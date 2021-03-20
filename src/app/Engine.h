
#pragma once

#include <map>
#include <memory>
#include "MetaMessage.h"
#include "System.h"

class Engine
{
public:

    void registerMetaMessage(const std::string& name, std::shared_ptr<MetaMessage> msg);

    void registerSystem(const std::string& name, std::shared_ptr<System> msg);

    void run(const std::string& entrypoint="main");

protected:

    std::map<std::string, SystemPtr> mySystems;
    std::map<std::string, MetaMessagePtr> myMetaMessages;
};
