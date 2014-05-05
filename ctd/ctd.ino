#include <SD.h>

/*

SD card attached to SPI bus:
  * MOSI - pin 11
  * MISO - pin 12
  * CLK - pin 13
  * CS - pin 8
  
*/

int readTemp();
int readPressure();
int readConductivity();

static int chipSelect = 8;         // Digital pin needed to do chip select on the SPI bus for the SD card
static int ledPin = 13;            // LED used for error indication
static int tempSensorPin = 5;     // The analog pin the temperature sensor's output feeds to.
static int pressureSensorPin = 4; // The analog pin the pressure sensor's output feeds to.
static int conductSensorPin = 3;  // The analog pin the conductivity sensor's output feeds to.

void setup() {
  // Set all pins to OUTPUT LOW to save power as per http://forum.arduino.cc/index.php/topic,28357.0.html
  for(int i = 2;i<14;i++) {
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
  
  // Set up the pins we use
  pinMode(chipSelect,OUTPUT);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW); // Keep the LED pin from floating.
  
  // Begin Serial (for debugging only)
  //Serial.begin(9600);
  
  // Prepare the SD card
  //Serial.println("Initializing SD Card...");
  
  if(!SD.begin(chipSelect)){
    //Serial.println("Card failed or not present.");
    while(true) {
      digitalWrite(ledPin,LOW);
      delay(500);
      digitalWrite(ledPin,HIGH);
      delay(500);
    }
  }
  
  File dataFile = SD.open("data.csv", FILE_WRITE);
  if(dataFile) {
    dataFile.println("Timestamp,Temperature,Pressure,Conductivity");
    dataFile.close();
  }
  else {
    //Serial.print("error opening data file");
    while(true) { // Blink the LED so people know something's wrong.
      digitalWrite(ledPin,LOW);
      delay(500);
      digitalWrite(ledPin,HIGH);
      delay(500);
    }
  }
}


void loop() {
  
  File dataFile = SD.open("data.csv", FILE_WRITE);
  
  if (dataFile) {
    
    dataFile.print(millis());
    dataFile.print(",");
    dataFile.print(readTemp());
    dataFile.print(",");
    dataFile.print(readPressure());
    dataFile.print(",");
    dataFile.println(readConductivity());
    
    /*
    Serial.print(millis());
    Serial.print(",");
    Serial.print(readTemp());
    Serial.print(",");
    Serial.print(readPressure());
    Serial.print(",");
    Serial.println(readConductivity());
    */
    
    dataFile.close();
    
  }
  else {
    //Serial.println("error opening data file");
    while(true) { // Blink the LED so people know something's wrong.
      digitalWrite(ledPin,LOW);
      delay(500);
      digitalWrite(ledPin,HIGH);
      delay(500);
    }
  }
}


int readTemp() {
  int scratch = analogRead(tempSensorPin);
  return scratch;
}

int readPressure() {
  int scratch = analogRead(pressureSensorPin);
  return scratch;
}

int readConductivity() {
  int scratch = analogRead(conductSensorPin);
  return scratch;
}
