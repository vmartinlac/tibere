
#pragma once

#include <vector>
#include <memory>
#include <string>
#include "DiscreteStorage.h"

class ContinuousMetaMessage;
class DiscreteMetaMessage;

class MetaMessage
{
public:

    MetaMessage(const std::string& name) : myName(name)
    {
    }

    virtual ~MetaMessage() = default;

    std::string getName() const { return myName; }

    bool isContinuous() const { return asContinuous() != nullptr; }
    bool isDiscrete() const { return asDiscrete() != nullptr; }

    virtual ContinuousMetaMessage* asContinuous() = 0;
    virtual DiscreteMetaMessage* asDiscrete() = 0;

    virtual const ContinuousMetaMessage* asContinuous() const = 0;
    virtual const DiscreteMetaMessage* asDiscrete() const = 0;

    virtual bool operator==(const MetaMessage& other) const = 0;

private:

    std::string myName;
};

using MetaMessagePtr = std::shared_ptr<MetaMessage>;

class DiscreteMetaMessage : public MetaMessage
{
public:

    DiscreteMetaMessage(const std::string& name) : MetaMessage(name)
    {
    }

    ContinuousMetaMessage* asContinuous() override { return nullptr; }
    DiscreteMetaMessage* asDiscrete() override { return this; }
    const ContinuousMetaMessage* asContinuous() const override { return nullptr; }
    const DiscreteMetaMessage* asDiscrete() const override { return this; }

    virtual DiscreteStoragePtr createStorage() = 0;

    bool operator==(const MetaMessage& other) const override;
};

template<typename T>
class DiscreteMetaMessageImpl : public DiscreteMetaMessage
{
public:

    DiscreteMetaMessageImpl(const std::string& name) : DiscreteMetaMessage(name)
    {
    }

    DiscreteStoragePtr createStorage() override
    {
        return DiscreteStoragePtr(new DiscreteStorageImpl<T>());
    }
};

class ContinuousMetaMessage : public MetaMessage
{
public:

    ContinuousMetaMessage(const std::string& name, int num_dimensions) : MetaMessage(name), myNumDimensions(num_dimensions)
    {
    }

    ContinuousMetaMessage* asContinuous() override { return this; }
    DiscreteMetaMessage* asDiscrete() override { return nullptr; }
    const ContinuousMetaMessage* asContinuous() const override { return this; }
    const DiscreteMetaMessage* asDiscrete() const override { return nullptr; }

    int getNumDimensions() const { return myNumDimensions; }

    bool operator==(const MetaMessage& other) const override;

private:

    int myNumDimensions;
};

