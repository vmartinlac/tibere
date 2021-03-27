#include <iostream>
#include "MetaMessage.h"

int main(int num_args, char** args)
{
    MetaMessagePtr a(new ContinuousMetaMessage("hello", 10));
    MetaMessagePtr b(new DiscreteMetaMessageImpl<int>("world"));
    MetaMessagePtr c(new DiscreteMetaMessageImpl<int>("world"));
    return 0;
}

