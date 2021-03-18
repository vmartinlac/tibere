
#pragma once

#include <memory>
#include <string>

class System
{
public:

    virtual ~System() = default;

    virtual int getNumInputPorts() = 0;
    virtual std::string getInputPortName(int i) = 0;
    virtual std::string getInputPortType(int i) = 0;

    virtual int getNumOutputPorts() = 0;
    virtual std::string getOutputPortName(int i) = 0;
    virtual std::string getOutputPortType(int i) = 0;
};

using SystemPtr = std::shared_ptr<System>;

class ContinuousSystem : public System
{
public:

    virtual int getNumStateDimensions() = 0;
    virtual void getDerivative(const double** inputs, const double* state, double* derivative) = 0;
    virtual void getOutputs(const double* state, double** outputs) = 0;
};

class DiscreteSystem : public System
{
public:
};

