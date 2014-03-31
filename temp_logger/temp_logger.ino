#include <RWM.h>
#include <SPI.h>

#define DATA_BUFFER_SIZE  2

RWM rwm = RWM();

int tempPin = 2;
unsigned int databuffer[DATA_BUFFER_SIZE];
unsigned long count = 20;
unsigned long address = 0;


void setup(){
 Serial.begin(115200);
}


void loop(){
  /*while(count > 20) {
    logdata();
    count--;
    Serial.println(count);
  }*/
  if(!Serial) {}
  
  address = 0;
  for(count=20;count>0;count--) {
    databuffer[0] = millis()/1000;
    databuffer[1] = analogRead(tempPin);
    rwm.EEPROMwriteInts(address, DATA_BUFFER_SIZE, databuffer);
    Serial.print(databuffer[0]);
    Serial.print(",");
    Serial.print(databuffer[1]);
    Serial.print(" written to ");
    Serial.println(address);
    address += DATA_BUFFER_SIZE;
    delay(1000);
  }
  
  address = 0;
  for(count=20;count>0;count--) {
    databuffer[0] = rwm.EEPROMreadInt(address);
    address+=1;
    databuffer[1] = rwm.EEPROMreadInt(address);
    address += 1;
    Serial.print(databuffer[0]);
    Serial.print(",");
    Serial.print(databuffer[1]);
    Serial.print(" read from ");
    Serial.println(address);
  }
  
  Serial.println("Done.");
  //Serial.println(.0049*analogRead(tempPin)*100.0);
  //delay(1000);
}
