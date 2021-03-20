
#pragma once

#include <memory>

class DiscreteStorage
{
public:

    virtual ~DiscreteStorage() = default;

    template<typename T>
    T* as();
};

using DiscreteStoragePtr = std::shared_ptr<DiscreteStorage>;

template<typename T>
class DiscreteStorageImpl : public DiscreteStorage
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
T* DiscreteStorage::as()
{
    DiscreteStorageImpl<T>* impl = dynamic_cast<DiscreteStorageImpl<T>*>(this);

    if(impl == nullptr)
    {
        return nullptr;
    }
    else
    {
        return &impl->refData();
    }
}

