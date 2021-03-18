#include "Message.h"

ContinuousMessage::ContinuousMessage(std::initializer_list<std::string> items)
{
    myDimensionNames.resize(items.size());
    std::copy(items.begin(), items.end(), myDimensionNames.begin());
}

int ContinuousMessage::getNumDimensions() const
{
    return myDimensionNames.size();
}

std::string ContinuousMessage::getDimensionName(int i) const
{
    return myDimensionNames.at(i);
}

