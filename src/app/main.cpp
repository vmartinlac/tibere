#include "Engine.h"

struct RadarSignal
{
    std::vector<double> data;

    std::string toString()
    {
        return "";
    }
};

int main(int num_args, char** args)
{
    Engine engine;

    MetaMessagePtr SE3MetaMessage(new ContinuousMetaMessage(7));

    MetaMessagePtr Sim2MetaMessage(new ContinuousMetaMessage(4));

    MetaMessagePtr RadarMetaMessage(new DiscreteMetaMessage<RadarSignal>());

    engine.registerMetaMessage("SE3", SE3MetaMessage);
    engine.registerMetaMessage("Sim2", Sim2MetaMessage);
    engine.registerMetaMessage("RadarSignal", RadarMetaMessage);

    engine.run();
    DiscreteStoragePtr storage = RadarMetaMessage->asDiscrete()->createStorage();
    storage->as<RadarSignal>()->data;

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

