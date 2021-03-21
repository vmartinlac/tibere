
#pragma once

#include <algorithm>
#include <vector>
#include <tuple>
#include <memory>
#include <string>
#include "MetaMessage.h"

class MetaSystem
{
public:

    virtual ~MetaSystem() = default;

    virtual std::string getName() = 0;

    virtual int getNumInputPorts() = 0;
    virtual std::string getInputPortName(int i) = 0;
    virtual MetaMessagePtr getInputPortType(int i) = 0;

    virtual int getNumOutputPorts() = 0;
    virtual std::string getOutputPortName(int i) = 0;
    virtual MetaMessagePtr getOutputPortType(int i) = 0;

    virtual bool hasContinuousState() = 0;
    virtual bool hasDiscreteState() = 0;

    virtual int getNumDimensionsOfContinuousState() = 0;

    virtual void computeContinuousStateDerivative(
        double time,
        DiscreteStoragePtr discrete_state,
        double* continuous_state,
        double** continuous_inputs,
        double* derivative) = 0;

    virtual void computeContinuousOutputs(
        DiscreteStoragePtr discrete_state,
        double* continuous_state,
        double** continuous_outputs) = 0;

    virtual bool detectContinuousEvent(
        DiscreteStoragePtr discrete_state,
        double* continuous_state) = 0;

    virtual void handleContinuousEvent(
        DiscreteStoragePtr discrete_state,
        double* continuous_state) = 0;

    virtual DiscreteStoragePtr createStorageForDiscreteState() = 0;

    virtual std::tuple<bool,double> getDiscreteStateDuration(DiscreteStoragePtr discrete_state) = 0;

    virtual void handleExternalEvent(
        double** continous_inputs,
        double* continuous_state,
        DiscreteStoragePtr discrete_state);

    virtual void handleTimeOut(
        double** continous_inputs,
        double* continuous_state,
        DiscreteStoragePtr discrete_state,
        int& port,
        DiscreteStoragePtr& message);
};

using MetaSystemPtr = std::shared_ptr<MetaSystem>;

class ComposedMetaSystem : public MetaSystem
{
public:

    ComposedMetaSystem(const std::string& name)
    {
        myName = name;
    }

    std::string getName() override
    {
        return myName;
    }

    int getNumInputPorts() override
    {
        return myInputs.size();
    }

    std::string getInputPortName(int i) override
    {
        return std::get<0>(myInputs.at(i));
    }

    MetaMessagePtr getInputPortType(int i) override
    {
        return std::get<1>(myInputs.at(i));
    }

    int getNumOutputPorts() override
    {
        return myOutputs.size();
    }

    std::string getOutputPortName(int i) override
    {
        return std::get<0>(myOutputs.at(i));
    }

    MetaMessagePtr getOutputPortType(int i) override
    {
        return std::get<1>(myOutputs.at(i));
    }

    bool hasContinuousState() override
    {
        return std::any_of(myMetaSystems.begin(), myMetaSystems.end(), [] (std::tuple<std::string,MetaSystemPtr>& x) { return std::get<1>(x)->hasContinuousState(); });
    }

    bool hasDiscreteState() override
    {
        return std::any_of(myMetaSystems.begin(), myMetaSystems.end(), [] (std::tuple<std::string,MetaSystemPtr>& x) { return std::get<1>(x)->hasDiscreteState(); });
    }

protected:

    std::string myName;
    std::vector< std::tuple<std::string,MetaSystemPtr> > myMetaSystems;
    std::vector< std::tuple<std::string,MetaMessagePtr> > myInputs;
    std::vector< std::tuple<std::string,MetaMessagePtr> > myOutputs;
    std::vector< std::tuple<int,int,int,int> > myInternalConnections;
    std::vector< std::tuple<int,int,int> > myInputConnections;
    std::vector< std::tuple<int,int,int> > myOutputConnections;
};

