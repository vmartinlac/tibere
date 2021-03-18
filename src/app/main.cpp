#include "Engine.h"

struct RadarSignal
{
    std::vector<double> data;
};

int main(int num_args, char** args)
{
    Engine engine;

    MessagePtr SE3Message(new ContinuousMessage({"object_to_world_x", "object_to_world_y", "object_to_world_z", "object_to_world_qx", "object_to_world_qy", "object_to_world_qz", "object_to_world_qw"}));

    MessagePtr Sim2Message(new ContinuousMessage({"object_to_world_x", "object_to_world_y", "scale", "theta"}));

    MessagePtr RadarMessage(new DiscreteMessage<RadarSignal>());

    engine.registerMessage("SE3", SE3Message);
    engine.registerMessage("Sim2", Sim2Message);
    engine.registerMessage("RadarSignal", RadarMessage);

    engine.run();
    DiscreteMessageStoragePtr storage = RadarMessage->asDiscrete()->createStorage();
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

