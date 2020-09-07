#include "HAMqttDevice.h"

HAMqttDevice binarySensor("My Binary Sensor", HAMqttDevice::BINARY_SENSOR);

void setup()
{
    Serial.begin(115200);

    binarySensor
        .addConfigVar("device_class", "door")
        .addConfigVar("retain", "false");

    Serial.println("Config topic : " + binarySensor.getConfigTopic());
    Serial.println("Config payload : " + binarySensor.getConfigPayload());
}

void loop()
{

}