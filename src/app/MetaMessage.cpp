#include "MetaMessage.h"

bool DiscreteMetaMessage::operator==(const MetaMessage& other) const
{
    if(other.isDiscrete())
    {
        return getName() == other.getName() && typeid(*this).hash_code() == typeid(other).hash_code();
    }
    else
    {
        return false;
    }
}

bool ContinuousMetaMessage::operator==(const MetaMessage& other) const
{
    if(other.isContinuous())
    {
        return getName() == other.getName() && myNumDimensions == other.asContinuous()->myNumDimensions;
    }
    else
    {
        return false;
    }
}

