#include <SPI.h>
#include <RWM.h>

#define DATA_BUFFER_SIZE  16

RWM rwm = RWM();

int tempPin = 2;
int count = 20;
unsigned long interval = 1;
unsigned long samples = 1000;
unsigned long address = 0;


void logdata() {
  byte i;
  int databuffer[DATA_BUFFER_SIZE];
  unsigned long t0, t;

  t0 = millis()+interval;
  i = 0;
  address = 0;
  while (address<65534) {
    t = millis();
    if (t>=t0) {
      databuffer[i++] = analogRead(tempPin);
      if (i==DATA_BUFFER_SIZE) {
        rwm.EEPROMwriteInts(address, DATA_BUFFER_SIZE, databuffer);
        address += DATA_BUFFER_SIZE;
        i = 0;        
      }
      t0 = t+interval;
    }
  }
}


void dumpdata() {
  unsigned long t;

  t = 0;
  interval = (long(rwm.EEPROMreadByte(0x1FFFF))<<16)|long(word(rwm.EEPROMreadByte(0x1FFFE), rwm.EEPROMreadByte(0x1FFFD)));
  for (address = 0; address<65534; address++) {
    Serial.print(t);
    Serial.print(",");
    Serial.println(rwm.EEPROMreadInt(address));
    t += interval;
  }
}

void setup(){
 Serial.begin(115200);
 
}

void loop(){
  while(count > 20) {
    logdata();
    count--;
    Serial.println(count);
  }
  dumpdata();
  Serial.println("Done.");
  //Serial.println(.0049*analogRead(tempPin)*100.0);
  //delay(1000);
}
