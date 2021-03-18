
#pragma once

#include <vector>
#include <memory>
#include <string>

class ContinuousMessageBase;
class DiscreteMessageBase;

class Message
{
public:

    virtual ~Message() = default;

    bool isContinuous() { return asContinuous() != nullptr; }
    bool isDiscrete() { return asDiscrete() != nullptr; }

    virtual ContinuousMessageBase* asContinuous() = 0;
    virtual DiscreteMessageBase* asDiscrete() = 0;
};

using MessagePtr = std::shared_ptr<Message>;

class DiscreteMessageStorage
{
public:

    virtual ~DiscreteMessageStorage() = default;

    template<typename T>
    T* as();
};

using DiscreteMessageStoragePtr = std::shared_ptr<DiscreteMessageStorage>;

template<typename T>
class DiscreteMessageStorageImpl : public DiscreteMessageStorage
{
public:

    T& refData()
    {
        return myData;
    }

    const T& refData() const
    {
        return myData;
    }

protected:

    T myData;
};

template<typename T>
T* DiscreteMessageStorage::as()
{
    DiscreteMessageStorageImpl<T>* impl = dynamic_cast<DiscreteMessageStorageImpl<T>*>(this);

    if(impl == nullptr)
    {
        return nullptr;
    }
    else
    {
        return &impl->refData();
    }
}

class DiscreteMessageBase : public Message
{
public:

    ContinuousMessageBase* asContinuous() override { return nullptr; }
    DiscreteMessageBase* asDiscrete() override { return this; }

    virtual DiscreteMessageStoragePtr createStorage() = 0;
};

template<typename T>
class DiscreteMessage : public DiscreteMessageBase
{
    DiscreteMessageStoragePtr createStorage() override
    {
        return DiscreteMessageStoragePtr(new DiscreteMessageStorageImpl<T>());
    }
};

class ContinuousMessageBase : public Message
{
public:

    ContinuousMessageBase* asContinuous() override { return this; }
    DiscreteMessageBase* asDiscrete() override { return nullptr; }

    virtual int getNumDimensions() const = 0;
    virtual std::string getDimensionName(int i) const = 0;
};

class ContinuousMessage : public ContinuousMessageBase
{
public:

    ContinuousMessage(std::initializer_list<std::string> items);
    int getNumDimensions() const override;
    std::string getDimensionName(int i) const override;

protected:

    std::vector<std::string> myDimensionNames;
};

