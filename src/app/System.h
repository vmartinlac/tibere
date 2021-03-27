
#pragma once

#include <algorithm>
#include <vector>
#include <tuple>
#include <memory>
#include <string>
#include "MetaMessage.h"

class System
{
public:

    System() = default;
    virtual ~System() = default;

    virtual std::string getName() = 0;

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

    virtual void initializeDiscreteState(
        DiscreteStoragePtr state) = 0;

    virtual std::tuple<bool,double> getDiscreteStateDuration(DiscreteStoragePtr discrete_state) = 0;

    virtual void handleExternalEvent(
        double** continous_inputs,
        double* continuous_state,
        DiscreteStoragePtr discrete_state) = 0;

    virtual void handleTimeOut(
        double** continous_inputs,
        double* continuous_state,
        DiscreteStoragePtr discrete_state,
        int& port,
        DiscreteStoragePtr& message) = 0;
};

using SystemPtr = std::shared_ptr<System>;

class ComposedSystem : public System
{
public:

    ComposedSystem(const std::string& name)
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

    std::string getInputPortType(int i) override
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

    std::string getOutputPortType(int i) override
    {
        return std::get<1>(myOutputs.at(i));
    }

    bool hasContinuousState() override
    {
        return std::any_of(mySystems.begin(), mySystems.end(), [] (SystemPtr& x) { return x->hasContinuousState(); });
    }

    bool hasDiscreteState() override
    {
        return std::any_of(mySystems.begin(), mySystems.end(), [] (SystemPtr& x) { return x->hasDiscreteState(); });
    }

    int getNumDimensionsOfContinuousState() override
    {
        int ret = 0;
        for(SystemPtr& s : mySystems)
        {
            ret += s->getNumDimensionsOfContinuousState();
        }
        return ret;
    }

    void computeContinuousStateDerivative(
        double time,
        DiscreteStoragePtr discrete_state,
        double* continuous_state,
        double** continuous_inputs,
        double* derivative) override
    {
        // TODO
    }

    /*
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
    */

    DiscreteStoragePtr createStorageForDiscreteState() override
    {
        DiscreteStorageImpl<State>* ret = new DiscreteStorageImpl<State>;

        State& s = *ret->as<State>();

        for(SystemPtr& x : mySystems)
        {
            if(x->hasDiscreteState())
            {
                s.states.push_back(x->createStorageForDiscreteState());
            }
        }

        return DiscreteStoragePtr(ret);
    }

    void initializeDiscreteState(
        DiscreteStoragePtr state) override
    {
        State& s = *state->as<State>();

        int i = 0;
        for(SystemPtr& x : mySystems)
        {
            if(x->hasDiscreteState())
            {
                x->initializeDiscreteState(s.states[i]);
                i++;
            }
        }
    }

    std::tuple<bool,double> getDiscreteStateDuration(DiscreteStoragePtr discrete_state) override
    {
        std::tuple<bool,double> ret;
        State& s = *discrete_state->as<State>();

        int i = 0;
        for(SystemPtr& x : mySystems)
        {
            if(x->hasDiscreteState())
            {
                std::tuple<bool,double> tmp = x->getDiscreteStateDuration(s.states[i]);
                if(std::get<0>(tmp))
                {
                    std::get<0>(ret) = true;
                    std::get<1>(ret) = std::min(std::get<1>(ret), std::get<1>(tmp));
                }
                i++;
            }
        }

        return ret;
    }

    /*
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
    */

public:

    struct State
    {
        std::vector<DiscreteStoragePtr> states;
    };

public:

    std::string myName;
    std::vector< SystemPtr > mySystems;
    std::vector< std::tuple<std::string, std::string> > myInputs;
    std::vector< std::tuple<std::string, std::string> > myOutputs;
    std::vector< std::tuple<int,int,int,int> > myInternalConnections;
    std::vector< std::tuple<int,int,int> > myInputConnections;
    std::vector< std::tuple<int,int,int> > myOutputConnections;
};

