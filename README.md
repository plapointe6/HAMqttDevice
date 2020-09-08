# HAMqttDevice

A simple library that allow an easy json generation of MQTT Discovery payloads intended to be sent to Home Assistant.

## How to use

If you are here, you probably already know about MQTT Discovery in Home assistant (https://www.home-assistant.io/docs/mqtt/discovery/).
If you want to implement MQTT Discovery with Home Assistant in your device, this library is for you.

This library is quite simple, it only helps to generate json payload, the communication part is not embeded into it.

So, first you need to create your MQTT Discovery device.

Lets take a look to the constructor : 
```c++
HAMqttDevice(
    const String& name,                         // Name of the device (ex: "My Nice Lamp")
    const DeviceType type,                      // The type of the device (See below)
    const String& haMQTTPrefix = "ha"          // The prefix configured in Home Assistant. ("discovery_prefix" in configuration.yaml)
);
```

Here is the device types : 
```c++
enum DeviceType { ALARM_CONTROL_PANEL, BINARY_SENSOR, CAMERA, COVER, FAN, LIGHT, LOCK, SENSOR, SWITCH, CLIMATE, VACUUM };
```

To create the device (a simple binary sensor in this exemple) :
```c++
HAMqttDevice binarySensor("My Binary Sensor", HAMqttDevice::BINARY_SENSOR);
```

It is possible to register state, command, and attributes topic.
Take note that when registering the state or command topic is mandatory for the device type, it will be done automatically.
```c++
HAMqttDevice& enableCommandTopic();         // If we enable the command topic registration
HAMqttDevice& enableStateTopic();           // If we enable the state topic registration 
HAMqttDevice& enableAttributesTopic();      // If we enable the attribute topic registration
```

Enabling attributes topic.
```c++
binarySensor.enableAttributesTopic();
```

It is also possible to add custom configuration variables (availables config variables for a binary sensor: https://www.home-assistant.io/integrations/sensor.mqtt/)
```c++
binarySensor.addConfigVar("device_class", "door");
binarySensor.addConfigVar("retain", "false");
```

You can now generate the config payload for Home Assistant discovery : 
```c++
Serial.println("Config topic : " + binarySensor.getConfigTopic());
Serial.println("Config payload : " + binarySensor.getConfigPayload());
```

Output :
```
Config topic : ha/binary_sensor/my_binary_sensor/config
Config payload : {"~":"ha/binary_sensor/my_binary_sensor","name":"My Binary Sensor","stat_t":"~/state","json_attr_t":"~/attr","device_class":"door","retain":"false"}
```

## Full blown exemples

I use this library in pair with ESPMQTTClient since more than a year now and I am in a point where everything is stable and functionnal.
You can see this library in action with some of my iot devices from this repo : https://github.com/plapointe6/CustomHADevicesCollection

