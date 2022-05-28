
#include <ArduinoBLE.h>
#define ON 1
#define OFF 0

// Defining the services
BLEService VALUES_SERVICE("1101");
BLEService SETTINGS_SERVICE("1102");

// Defining the characteristics
BLEUnsignedIntCharacteristic distanceIntChar("2101", BLERead | BLENotify); // Real time value
BLEUnsignedCharCharacteristic batteryLevelChar("2102", BLERead | BLENotify); // Real time value
BLEUnsignedIntCharacteristic silentModeChar("2103", BLEWrite); // Setting
//BLEUnsignedIntCharacteristic volumeChar("2104", BLEWrite); // Setting

// Initializing the settings of the device.
//int32_t silentMode = OFF;
//int32_t volume = 10;


void setupBLESystem() {
  BLE.begin();
  
  // Initialize the bluetooth device
  BLE.setLocalName("SocDistDevice");

  // Connect the characteristics to their respected services
  BLE.setAdvertisedService(VALUES_SERVICE);
  BLE.setAdvertisedService(SETTINGS_SERVICE);
  VALUES_SERVICE.addCharacteristic(distanceIntChar);
  VALUES_SERVICE.addCharacteristic(batteryLevelChar);
  SETTINGS_SERVICE.addCharacteristic(silentModeChar);
  //SETTINGS_SERVICE.addCharacteristic(volumeChar);
  BLE.addService(VALUES_SERVICE);
  BLE.addService(SETTINGS_SERVICE);

  // Advertise the services
  BLE.advertise();
}

//Assuming already connected
//reads distance, current state, and volume
//stores in variable
void getInfo(int distance) {
  BLEDevice central = BLE.central();

  if(central) {
    if (central.connected()) {
      Serial.println("CONNECTED\n");
      // Read the battery percentage of the device and store it in a variable AND characteristic.
      int battery = analogRead(BATTERY_PIN);
      int batteryLevel = map(battery, 0, 1023, 0, 100);
      batteryLevelChar.writeValue(batteryLevel);
  
      // Get the "Distance" and store it in a variable AND characteristic.
      distanceIntChar.writeValue(distance);
  
      // Read the silent mode state and store it in a variable.
      silentModeChar.readValue(silentMode);
  
      // Read the volume level and store it in a variable.
      //volumeChar.readValue(volume);
    }
  }
}
