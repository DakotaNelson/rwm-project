#include <RWM.h>
#include <SPI.h>

void dumpData();

RWM rwm = RWM();

static int tempPin = 2;
static int interval = 3; // in seconds
/*
 Given a 128 kbyte EEPROM and 2 bytes per record, 
 this lets us log 3 second intervals for ~ 2 days and 5 hours.
 At 5 seconds, memory will hold out for ~ 3 days, 16 hours and some change.
*/

int databuffer;
unsigned long count;
unsigned long address = 0;
unsigned long temp_address = 0;


void setup(){
 Serial.begin(115200);
}


void loop(){
  
  while(millis() < 30000) { // leave a 30 second bootup time during which to connect serial
    if(Serial) { // if serial is connected during this time, dump the stored logs
      dumpData();
      while(true); // block forever, we only want to dump data this run, not log
    } // else start logging
  }
  
  address = 1; // leave an int to store the number of records
  while(true) { // log until unplugged
    databuffer = analogRead(tempPin);
    rwm.EEPROMwriteInt(address, databuffer); // log a record
    rwm.EEPROMwriteInt(0,address); // at address 0, write the number of records we've logged so far
    address += 1;
    delay(interval*1000); // delay some seconds
  }
}

void dumpData() {
  temp_address = 1; // start from one, we don't want to output the number of records
  address = rwm.EEPROMreadInt(0); // at address 0 the number of records is stored
  Serial.print("Number of records: ");
  Serial.println(address);
  for(count=address;count>0;count--) {
    databuffer = rwm.EEPROMreadInt(temp_address);
    temp_address+=1;
    Serial.print(databuffer); // output everything in more or less a csv format
    Serial.print(",");
    delay(1); // don't scare the EEPROM
  }
}
