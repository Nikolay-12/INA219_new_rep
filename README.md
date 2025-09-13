ina219.ino is the main program that is loaded onto the Arduino microcontroller. In this file, the user configures the addresses and shunt resistances of the sensors 
from which he want to read the current value.

The src folder containes auxiliary files for working with sensors.
ina219_driver.cpp: this file describes a set of methods for working with the INA219 module via the I2C bus.
ina219_driver.h: this file describes the settings for the current sensor and a list of methods for working with it.
current_sensors.cpp: this file describes the functionality of methods that allow you to poll multiple INA219 sensors located on the same bus.
current_sensors.h: This file describes the creation of structures that represent sensors and their parameters (address and shunt resistance). 
It also provides a list of methods for working with a sensor array.
