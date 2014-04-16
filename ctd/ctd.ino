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

const int chipSelect = 8;         // Digital pin needed to do chip select on the SPI bus for the SD card
const int ledPin = 13;            // LED used for error indication
const int tempSensorPin = A5;     // The analog pin the temperature sensor's output feeds to.
const int pressureSensorPin = A4; // The analog pin the pressure sensor's output feeds to.
const int conductSensorPin = A3;  // The analog pin the conductivity sensor's output feeds to.

void setup() {
  // Set up the pins
  pinMode(chipSelect,OUTPUT);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW); // Keep the pin from floating.
  
  // Begin Serial
  Serial.begin(9600);
  
  // Prepare the SD card
  Serial.println("Initializing SD Card...");
  
  if(!SD.begin(chipSelect)){
    Serial.println("Card failed or not present.");
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
    Serial.print("error opening data file");
    while(true) {
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
    dataFile.print(readConductivity());
    
    dataFile.close();
    
  }
  else {
    Serial.println("error opening data file");
    while(true) {
      digitalWrite(ledPin,LOW);
      delay(500);
      digitalWrite(ledPin,HIGH);
      delay(500);
    }
  }
}


int readTemp() {
  // Very simple for now, may need more data conditioning later.
  return analogRead(tempSensorPin);
}

int readPressure() {
  // Very simple for now, may need more data conditioning later.
  return analogRead(pressureSensorPin);
}

int readConductivity() {
  // Very simple for now, may need more data conditioning later.
  return analogRead(conductSensorPin);
}
