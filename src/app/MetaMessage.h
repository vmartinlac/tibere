
#pragma once

#include <vector>
#include <memory>
#include <string>
#include "DiscreteStorage.h"

class ContinuousMetaMessageBase;
class DiscreteMetaMessageBase;

class MetaMessage
{
public:

    virtual ~MetaMessage() = default;

    bool isContinuous() { return asContinuous() != nullptr; }
    bool isDiscrete() { return asDiscrete() != nullptr; }

    virtual ContinuousMetaMessageBase* asContinuous() = 0;
    virtual DiscreteMetaMessageBase* asDiscrete() = 0;
};

using MetaMessagePtr = std::shared_ptr<MetaMessage>;

class DiscreteMetaMessageBase : public MetaMessage
{
public:

    ContinuousMetaMessageBase* asContinuous() override { return nullptr; }
    DiscreteMetaMessageBase* asDiscrete() override { return this; }

    virtual DiscreteStoragePtr createStorage() = 0;
};

template<typename T>
class DiscreteMetaMessage : public DiscreteMetaMessageBase
{
    DiscreteStoragePtr createStorage() override
    {
        return DiscreteStoragePtr(new DiscreteStorageImpl<T>());
    }
};

class ContinuousMetaMessageBase : public MetaMessage
{
public:

    ContinuousMetaMessageBase* asContinuous() override { return this; }
    DiscreteMetaMessageBase* asDiscrete() override { return nullptr; }

    virtual int getNumDimensions() const = 0;
};

class ContinuousMetaMessage : public ContinuousMetaMessageBase
{
public:

    ContinuousMetaMessage(int num_dimensions);
    int getNumDimensions() const override;

protected:

    int myNumDimensions;
};

