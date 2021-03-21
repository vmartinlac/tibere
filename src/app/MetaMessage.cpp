#include "MetaMessage.h"

ContinuousMetaMessage::ContinuousMetaMessage(const std::string& name, int num_dimensions)
{
    myNumDimensions = num_dimensions;
    myName = name;
}

int ContinuousMetaMessage::getNumDimensions() const
{
    return myNumDimensions;
}

