
#pragma once

#include <map>
#include <memory>
#include "Message.h"
#include "System.h"

class Engine
{
public:

    void registerMessage(const std::string& name, std::shared_ptr<Message> msg);

    void registerSystem(const std::string& name, std::shared_ptr<System> msg);

    void run(const std::string& entrypoint="main");

protected:

    std::map<std::string, SystemPtr> mySystems;
    std::map<std::string, MessagePtr> myMessages;
};
