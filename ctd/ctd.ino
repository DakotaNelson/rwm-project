#include <SD.h>

/*

SD card attached to SPI bus:
  * MOSI - pin 11
  * MISO - pin 12
  * CLK - pin 13
  * CS - pin 8
  
*/

int readTemp();

const int chipSelect = 8;     // Digital pin needed to do chip select on the SPI bus for the SD card
const int tempSensorPin = A5; // The analog pin the temperature sensor's output feeds to.
const int ledPin = 13;        // LED used for error indication


void setup() {
  // Set up the pins
  
  // Begin Serial
  Serial.begin(9600);
  
  // Prepare the SD card
  Serial.println("Initializing SD Card...");
  pinMode(chipSelect,OUTPUT);
  pinMode(ledPin,OUTPUT);
  
  if(!SD.begin(chipSelect)){
    Serial.println("Card failed or not present.");
    return;
  }
  
  File dataFile = SD.open("data.csv", FILE_WRITE);
  if(dataFile) {
    dataFile.println("Timestamp,Temperature,Pressure,Conductivity");
  }
  else {
    Serial.print("error opening data.csv");
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
    dataFile.println(readTemp());
    
    dataFile.close();
    
  }
  else {
    Serial.println("error opening data.log");
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
