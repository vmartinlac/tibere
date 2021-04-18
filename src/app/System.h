
#pragma once

#include <set>
#include <map>
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
        double* continuous_state,
        DiscreteStoragePtr discrete_state,
        double** continous_inputs,
        int port,
        DiscreteStoragePtr message) = 0;

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

        s.continuous_state_offset.resize(mySystems.size());

        {
            int i = 0;
            int offset = 0;
            for(SystemPtr& x : mySystems)
            {
                s.continuous_state_offset[i] = offset;

                if(x->hasContinuousState())
                {
                    offset += x->getNumDimensionsOfContinuousState();
                }

                i++;
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
        std::tuple<bool,double> ret(false, 0.0);
        State& s = *discrete_state->as<State>();

        int i = 0;

        for(SystemPtr& x : mySystems)
        {
            if(x->hasDiscreteState())
            {
                std::tuple<bool,double> tmp = x->getDiscreteStateDuration(s.states[i]);

                if(std::get<0>(tmp) && (!std::get<0>(ret) || std::get<1>(tmp) < std::get<1>(ret)))
                {
                    std::get<0>(ret) = true;
                    std::get<1>(ret) = std::get<1>(tmp);
                }

                i++;
            }
        }

        return ret;
    }

    void handleExternalEvent(
        double* continuous_state,
        DiscreteStoragePtr discrete_state,
        double** continous_inputs,
        int port,
        DiscreteStoragePtr message)
    {
        State& s = *discrete_state->as<State>();
        auto it = myInputConnections.lower_bound(port);

        while(it != myInputConnections.upper_bound(port))
        {
            const int system_id = std::get<0>(it->second);
            /*
            mySystems[system_id]->handleExternalEvent(
                continuous_state + s.continuous_state_offset[system_id],
                s.states[system_id],
                ,
                ,
                message);
            */
            // TODO
        }
    }

    /*
    virtual void handleTimeOut(
        double** continous_inputs,
        double* continuous_state,
        DiscreteStoragePtr discrete_state,
        int& port,
        DiscreteStoragePtr& message);
    */

    void check()
    {
        // check that system name is unique.
        {
            std::set<std::string> items;
            for(SystemPtr& x : mySystems)
            {
                if(items.find(x->getName()) != items.end()) throw std::runtime_error("internal error");
                items.insert(x->getName());
            }
        }
    }

public:

    struct State
    {
        std::vector<DiscreteStoragePtr> states;
        std::vector<int> continuous_state_offset;
    };

public:

    std::string myName;
    std::vector< SystemPtr > mySystems;
    std::vector< std::tuple<std::string, std::string> > myInputs;
    std::vector< std::tuple<std::string, std::string> > myOutputs;
    std::multimap<int, std::tuple<int,int> > myInputConnections;
    std::multimap<int, std::tuple<int,int> > myOutputConnections;
    std::multimap< std::tuple<int,int>, std::tuple<int,int> > myInternalConnections;
};

