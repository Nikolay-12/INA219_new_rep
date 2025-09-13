#include "src/current_sensors.h"

// 0x40 (перемычки не установлены); 0x41 (перемычка A0); 0x44 (перемычка A1); 0x45 (перемычки A0 и A1).
current_sensors::descriptor_t current_sensor_descriptors[CURRENT_SENSORS_NUM] = {
    { 0x40, 0.1 },
    { 0x41, 0.1 },
    { 0x44, 0.1 }
};

void setup(void)
{
    Serial.begin(9600);
    current_sensors::init(current_sensor_descriptors);
    Serial.println("Measuring current with INA219 ...");
}

void loop(void)
{
    static String receivedData = "";

    if (Serial.available() > 0)
    {
        receivedData = Serial.readString();
        receivedData.trim();
        Serial.println("Received data: " + receivedData);
        Serial.flush();
    }

    if (receivedData == "read")
    {
        current_sensors::read_all(); 
        for (size_t i = 0; i < CURRENT_SENSORS_NUM; i++)
        {
            Serial.print("Current #");
            Serial.print(i);
            Serial.print(":       ");
            Serial.print(current_sensors::get_current_amps(i));
            Serial.println(" mA");
        } 
        delay(1000);
    }

    if (receivedData == "stop")
    {
        receivedData = "";
    }
}
