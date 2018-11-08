/*
 * This is example code to run on the Metro Mini that is outside the chamber 
 * 
 * It receives data from inside the chamber via SoftwareSerial port swSerial and passes this info on
 * via Serial. 
 * Similarly, data input to Serial is passed on to swSerial.
 */

#include <SoftwareSerial.h>
// Pick your own pin pair
SoftwareSerial swSerial(2,3); // RX, TX

void setup() {
  // put your setup code here, to run once:
    swSerial.begin(9600);
    Serial.begin(9600);

    Serial.println("Ready for data...");
}

void loop() {
  // put your main code here, to run repeatedly:
if (swSerial.available()) {
  Serial.write(swSerial.read());
}

if (Serial.available()) {
  swSerial.write(Serial.read());
}
}
