
#pragma once

#include <tuple>
#include <memory>
#include <string>
#include "DiscreteStorage.h"

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

    virtual bool hasContinuousState() = 0;
    virtual bool hasDiscreteState() = 0;

    virtual int getNumDimensionsOfContinuousState() = 0;
    virtual void computeContinuousStateDerivative(
        DiscreteStoragePtr discrete_state,
        double* continuous_state,
        double** continuous_inputs) = 0;

    virtual DiscreteStoragePtr createDiscreteStateStorage() = 0;
    virtual std::tuple<bool,double> getDiscreteStateDuration(DiscreteStoragePtr discrete_state) = 0;
    /*
    virtual void handleExternalEvent();
    virtual void handleTimeOut();
    */

    virtual int getNumParameters() = 0;
    virtual std::string getParameterName(int i) = 0;
    virtual int getParameterType(int i) = 0;
};

using SystemPtr = std::shared_ptr<System>;

class ComposedSystem : public System
{
public:
};

