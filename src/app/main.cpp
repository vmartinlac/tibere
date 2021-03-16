#include <memory>
#include <map>
#include <vector>

class Message
{
public:

};

class MetaMessage
{
public:

    std::shared_ptr<Message> createMessage();
};

class ContinuousMessage
{
public:

    int getNumDimensions() const;
    std::string getDimensionName(int i) const;
    const std::vector<double>& getData() const;
    std::vector<double>& getData();

protected:

    std::vector<double> myData;
};

class DiscreteMessage
{
public:


protected:
};

class System
{
public:

    virtual int getNumInputPorts() = 0;
    virtual std::string getInputPortName(int i) = 0;
    virtual std::string getInputPortType(int i) = 0;

    virtual int getNumOutputPorts() = 0;
    virtual std::string getOutputPortName(int i) = 0;
    virtual std::string getOutputPortType(int i) = 0;
};

class ComposedSystem : public System
{
public:

protected:

};

class Engine
{
public:

    using MetaMessageMap = std::map<std::string, std::shared_ptr<MetaMessage> >;
    using SystemMap = std::map<std::string, std::shared_ptr<System> >;

public:

    void run(const MetaMessageMap& meta_messages, const SystemMap& systems);

protected:

};

int main(int num_args, char** args)
{
    return 0;
}

/*
<tibere>
    <composition name="">
        <component type="radar_processor" name="radar_processor" />
        <component type="radar_simulator" name="radar_simulator" />
        <component type="flight_dynamics" name="flight_dynamics" />
        <connection component_from="radar_simulator" port_from="signal" component_to="radar_processor" port_to="signal" />
        <input component_to="" port_to="" name="" />
        <output component_from="" port_from="" name="" />
    </composition>
    <composition name="main">
    </composition>
</tibere>
*/

