#include <ArduinoBLE.h>
#include <RingBuf.h>
#define RED 22
#define BLUE 24

int distance_read;
String line;
size_t place;
float distance_inches;

RingBuf<float, 50> myRingBuffer;
BLEService TEST_SERVICE("1101");
BLEService DIST_SERVICE("1102");
BLEUnsignedIntCharacteristic distanceIntChar("2102", BLERead | BLENotify);
BLEUnsignedCharCharacteristic batteryLevelChar("2101", BLERead | BLENotify);

void setup() {

  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial1.begin(115200);

  if (!BLE.begin())
  {
    digitalWrite(RED, HIGH);
    while (1);
  }

  BLE.setLocalName("SocDistDevice");
  BLE.setAdvertisedService(TEST_SERVICE);
  BLE.setAdvertisedService(DIST_SERVICE);
  DIST_SERVICE.addCharacteristic(distanceIntChar);
  TEST_SERVICE.addCharacteristic(batteryLevelChar);
  BLE.addService(TEST_SERVICE);
  BLE.addService(DIST_SERVICE);

  BLE.advertise();
}

float runningAverage() {
  float running_value = 0;
  for (int i = 0; i < myRingBuffer.size(); i++)
  {
    //Serial.println(myRingBuffer[i], 8);
    running_value = running_value + myRingBuffer[i];
  }
  float average = running_value / myRingBuffer.size();
  return average;
}

void push_to_Buff(float value) {
  if (myRingBuffer.isFull())
  {
    float deleted_val;
    myRingBuffer.pop(deleted_val);
  }
  //Serial.println(value, 8);
  if (value != 0)
  {
    myRingBuffer.push(value);
  }
  return;
}

void loop()
{
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, HIGH);
  BLEDevice central = BLE.central();

  if (central) {
    digitalWrite(RED, HIGH);
    digitalWrite(BLUE, LOW);

    while (central.connected()) {

      line = Serial1.readStringUntil('\n');
      place = line.indexOf("Distance : ");
      if (place == 0) {
        distance_read = (line.substring(11, 19)).toFloat();
      }
      //Serial.println(distance_read, 8);
      push_to_Buff(distance_read);
      float avg_distance = runningAverage();
      //Serial.println(avg_distance, 8);
      distance_inches = (int) (-2.98 + 30.9 * (avg_distance) + 0.851 * sq(avg_distance));
      //Serial.println(distance_inches);

      int battery = analogRead(A0);
      int batteryLevel = map(battery, 0, 1023, 0, 100);
      batteryLevelChar.writeValue(batteryLevel);

      //int POT = analogRead(A1);
      distanceIntChar.writeValue(distance_inches);

      delay(20);
    }
  }
}


//***********************BATTERY LEVEL EX. BELOW******************************

//#include <ArduinoBLE.h>
//BLEService batteryService("1101");
//BLEUnsignedCharCharacteristic batteryLevelChar("2101", BLERead | BLENotify);
//
//void setup() {
//Serial.begin(9600);
//while (!Serial);
//
//pinMode(LED_BUILTIN, OUTPUT);
//if (!BLE.begin())
//{
//Serial.println("starting BLE failed!");
//while (1);
//}
//
//BLE.setLocalName("BatteryMonitor");
//BLE.setAdvertisedService(batteryService);
//batteryService.addCharacteristic(batteryLevelChar);
//BLE.addService(batteryService);
//
//BLE.advertise();
//Serial.println("Bluetooth device active, waiting for connections...");
//}
//
//void loop()
//{
//BLEDevice central = BLE.central();
//
//if (central)
//{
//Serial.print("Connected to central: ");
//Serial.println(central.address());
//digitalWrite(LED_BUILTIN, HIGH);
//
//while (central.connected()) {
//
//      int battery = analogRead(A0);
//      int batteryLevel = map(battery, 0, 1023, 0, 100);
//      Serial.print("Battery Level % is now: ");
//      Serial.println(batteryLevel);
//      batteryLevelChar.writeValue(batteryLevel);
//      delay(200);
//
//}
//}
//digitalWrite(LED_BUILTIN, LOW);
//Serial.print("Disconnected from central: ");
//Serial.println(central.address());
//}



//****************************EXAMPLE BELOW****************************************************

///*
//  BLE_Peripheral.ino
//
//  This program uses the ArduinoBLE library to set-up an Arduino Nano 33 BLE
//  as a peripheral device and specifies a service and a characteristic. Depending
//  of the value of the specified characteristic, an on-board LED gets on.
//
//  The circuit:
//  - Arduino Nano 33 BLE.
//
//  This example code is in the public domain.
//*/
//
//#include <ArduinoBLE.h>
//
//enum {
//  GESTURE_NONE  = -1,
//  GESTURE_UP    = 0,
//  GESTURE_DOWN  = 1,
//  GESTURE_LEFT  = 2,
//  GESTURE_RIGHT = 3
//};
//
//const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
//const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
//
//int gesture = -1;
//
//BLEService gestureService(deviceServiceUuid);
//BLEByteCharacteristic gestureCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);
//
//
//void setup() {
//  Serial.begin(9600);
//  while (!Serial);
//
//  pinMode(LEDR, OUTPUT);
//  pinMode(LEDG, OUTPUT);
//  pinMode(LEDB, OUTPUT);
//  pinMode(LED_BUILTIN, OUTPUT);
//
//  digitalWrite(LEDR, HIGH);
//  digitalWrite(LEDG, HIGH);
//  digitalWrite(LEDB, HIGH);
//  digitalWrite(LED_BUILTIN, LOW);
//
//
//  if (!BLE.begin()) {
//    Serial.println("- Starting Bluetooth® Low Energy module failed!");
//    while (1);
//  }
//
//  BLE.setLocalName("Arduino Nano 33 BLE (Peripheral)");
//  BLE.setAdvertisedService(gestureService);
//  gestureService.addCharacteristic(gestureCharacteristic);
//  BLE.addService(gestureService);
//  gestureCharacteristic.writeValue(-1);
//  BLE.advertise();
//
//  Serial.println("Nano 33 BLE (Peripheral Device)");
//  Serial.println(" ");
//}
//
//void loop() {
//  BLEDevice central = BLE.central();
//  Serial.println("- Discovering central device...");
//  delay(500);
//
//  if (central) {
//    Serial.println("* Connected to central device!");
//    Serial.print("* Device MAC address: ");
//    Serial.println(central.address());
//    Serial.println(" ");
//
//    while (central.connected()) {
//      if (gestureCharacteristic.written()) {
//         gesture = gestureCharacteristic.value();
//         writeGesture(gesture);
//       }
//    }
//
//    Serial.println("* Disconnected to central device!");
//  }
//}
//
//void writeGesture(int gesture) {
//  Serial.println("- Characteristic <gesture_type> has changed!");
//
//   switch (gesture) {
//      case GESTURE_UP:
//        Serial.println("* Actual value: UP (red LED on)");
//        Serial.println(" ");
//        digitalWrite(LEDR, LOW);
//        digitalWrite(LEDG, HIGH);
//        digitalWrite(LEDB, HIGH);
//        digitalWrite(LED_BUILTIN, LOW);
//        break;
//      case GESTURE_DOWN:
//        Serial.println("* Actual value: DOWN (green LED on)");
//        Serial.println(" ");
//        digitalWrite(LEDR, HIGH);
//        digitalWrite(LEDG, LOW);
//        digitalWrite(LEDB, HIGH);
//        digitalWrite(LED_BUILTIN, LOW);
//        break;
//      case GESTURE_LEFT:
//        Serial.println("* Actual value: LEFT (blue LED on)");
//        Serial.println(" ");
//        digitalWrite(LEDR, HIGH);
//        digitalWrite(LEDG, HIGH);
//        digitalWrite(LEDB, LOW);
//        digitalWrite(LED_BUILTIN, LOW);
//        break;
//      case GESTURE_RIGHT:
//        Serial.println("* Actual value: RIGHT (built-in LED on)");
//        Serial.println(" ");
//        digitalWrite(LEDR, HIGH);
//        digitalWrite(LEDG, HIGH);
//        digitalWrite(LEDB, HIGH);
//        digitalWrite(LED_BUILTIN, HIGH);
//        break;
//      default:
//        digitalWrite(LEDR, HIGH);
//        digitalWrite(LEDG, HIGH);
//        digitalWrite(LEDB, HIGH);
//        digitalWrite(LED_BUILTIN, LOW);
//        break;
//    }
//}
