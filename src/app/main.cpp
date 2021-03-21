
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

