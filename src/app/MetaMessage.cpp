#include "MetaMessage.h"

ContinuousMetaMessage::ContinuousMetaMessage(int num_dimensions)
{
    myNumDimensions = num_dimensions;
}

int ContinuousMetaMessage::getNumDimensions() const
{
    return myNumDimensions;
}

