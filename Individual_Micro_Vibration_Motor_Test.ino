/* Vibration Motor
 * Power wire (Red) in pin 5
 * Ground wire (Blue) in GND (Ground)
 */

 /* Potentiometer
  * Right Wire (Ground) in GND
  * Middle Wire (Data) in pin A1
  * Left Wire (Power) in 5v pin
  */

int mvm = 5; //microvibration motor is connected with pin number 5 witch is the pwm pin
int vresistor = A1; //potentiometer data pin is A1
int data = 0; //resistance initially starts at 0

void setup() {
  // put your setup code here, to run once:
  pinMode(mvm, OUTPUT); //vibration motor
  pinMode(vresistor, INPUT); //potentiometer
}

void loop() {
  // put your main code here, to run repeatedly:
  data = analogRead(vresistor); //read from potentiometer
  data = map(data, 0, 1023, 0, 255); //Converts resitance to potentiometer values
  analogWrite(mvm, data); //send data from potentiometer to power pin of vibration motor
}
