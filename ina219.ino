#include "src/current_sensors.h"

// 0x40 (перемычки не установлены); 0x41 (перемычка A0); 0x44 (перемычка A1); 0x45 (перемычки A0 и A1).
//This is just an example. Ideally, these descriptors would be stored in EEPROM to be configurable through Serial console,
//thus eliminating the need to recompile and reflash the Arduino whenever some addresses or resistors change.
current_sensors::descriptor_t current_sensor_descriptors[CURRENT_SENSORS_NUM] = {
    { 0x40, 1 /*just an example, I don't remember actual resistances*/ },
    { 0x41, 1 },
    { 0x44, 1 },
    { 0x45, 1 }
};

void setup(void)
{
    Serial.begin(9600);
    current_sensors::init(current_sensor_descriptors);
    Serial.println("Measuring voltage, current, and power with INA219 ...");
}

void loop(void)
{
    static String receivedData = ""; //This variable is not needed outside loop(), so declare it as static inside the scope of loop(). Global variables are cancer.

    if (Serial.available() > 0)
    {
        receivedData = Serial.readString();
        receivedData.trim();
        Serial.println("Received data: " + receivedData);
        Serial.flush();
    }

    if (receivedData == "read")
    {
        current_sensors::read_all(); //Since we are using a level of abstraction - the current_sensors namespace - we can/should
        //hide away as much as we can inside it, otherwise what's the purpose of such hierarchy. So we can extract actual reading out of the
        //following loop.
        //And now this loop inside our sketch only has to retrieve the values from memory (that is once again hidden/abstracted) and print them.
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
