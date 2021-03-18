#include <iostream>
#include "Engine.h"

void Engine::registerMessage(const std::string& name, std::shared_ptr<Message> msg)
{
    if( myMessages.find(name) != myMessages.end() )
    {
        throw std::runtime_error("A message with that name already exists");
    }

    myMessages[name] = msg;
}

void Engine::registerSystem(const std::string& name, std::shared_ptr<System> msg)
{
    if( mySystems.find(name) != mySystems.end() )
    {
        throw std::runtime_error("A system with that name already exists");
    }

    mySystems[name] = msg;
}

void Engine::run(const std::string& entrypoint)
{
    std::cout << myMessages.at("SE3")->asContinuous()->getDimensionName(0) << std::endl;
}

