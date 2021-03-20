#include <iostream>
#include "Engine.h"

void Engine::registerMetaMessage(const std::string& name, std::shared_ptr<MetaMessage> msg)
{
    if( myMetaMessages.find(name) != myMetaMessages.end() )
    {
        throw std::runtime_error("A message with that name already exists");
    }

    myMetaMessages[name] = msg;
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
}

