/***************************************************************************
  This is a library for the AMG88xx GridEYE 8x8 IR camera

  This sketch tries to read the pixels from the sensor

  Designed specifically to work with the Adafruit AMG88 breakout
  ----> http://www.adafruit.com/products/3538

  These sensors use I2C to communicate. The device's I2C address is 0x69

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution

This is example code for use inside the chamber. It is more complicated than
it needs to be in that you can send commands either over Serial or SoftwareSerial.
In the chamber, Serial is not available.

I've included and then commented out 
ChipTemp which measures the internal Metro Mini temperature
There was an announcement about this.  
See this web page if you want thi code:
https://www.avdweb.nl/arduino/measurement/temperature-measurement

  
 ***************************************************************************/
// Optional for Metro Mini internal temperature
// #include <avr/pgmspace.h>
//#include <ChipTemp.h>

#include <Wire.h>
#include <Adafruit_AMG88xx.h>
#include <SoftwareSerial.h>

const byte actuator = 4;
const byte actuatorSense = 5;
Adafruit_AMG88xx amg;

// Optional for Metro Mini internal temperatue
//ChipTemp chipTemp;

SoftwareSerial swSerial(2,3); // RX, TX

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
int incomingByte = 0;
int pinVal = LOW;

void showPixels(void);
void showT(void);

void setup() {
    swSerial.begin(9600);
    Serial.begin(9600);
    Serial.println(F("AMG88xx pixels"));

    pinMode(actuator, OUTPUT);
    pinMode(actuatorSense, INPUT);

    bool status;
    
    // default settings
    status = amg.begin();
    if (!status) {
        Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
        while (1);
    }
    
    Serial.println("-- Pixels Test --");

    Serial.println();

    delay(100); // let sensor boot up
}


void loop() {

  incomingByte = 0;
  
  if (swSerial.available()) {
    incomingByte = swSerial.read();
  }
	else if (Serial.available()) {
    incomingByte = Serial.read();
	}
    switch(incomingByte) {
      case 'D':
      case 'd':
        showPixels();
      break;
      
      case 'T':
      case 't':
        showT();
      break;
      
      case 'V':
      case 'v':
        digitalWrite(actuator, HIGH);
      break;
      
      case 'B':
      case 'b':
        digitalWrite(actuator, LOW);
      break;
      case 'I':
      case 'i':
      // Optional for Metro Mini internal temperatue
        // Serial.println(chipTemp.celsius());
        // swSerial.println(chipTemp.celsius());        
      break;

      case 'c':
      case 'C':
        pinVal = digitalRead(actuatorSense);
        Serial.println(pinVal);
        swSerial.println(pinVal);        
      break;

      case 'P':
      case 'p':
        delay(1000);
      break;
      
      default:
      break;
    }

  //delay
  delay(100);
}


void showPixels(void){
    //read all the pixels
    amg.readPixels(pixels);

    Serial.println("[");
    swSerial.println("[");
    
    for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
      Serial.print(pixels[i-1]);
      swSerial.print(pixels[i-1]);
    
      Serial.print(", ");
      swSerial.print(", ");
      
      if( i%8 == 0 ) {
        Serial.println();
        swSerial.println();      
      }
    }
    Serial.println("]");
    swSerial.println("]");
    
    Serial.println();
    swSerial.println();

}
void showT(void){
    int temp;
    temp = amg.readThermistor();
    Serial.print("Thermistor Temperature = ");
    swSerial.print("Thermistor Temperature = ");
    
    Serial.print(temp);
    swSerial.print(temp);
    
    Serial.println(" *C");
    swSerial.println(" *C");
}
