#include <SPI.h>  
#include "RF24.h"

int shiftUp = 2;
int shiftDown = 4;

int lastUp = false;
int lastDown = false;

RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};

struct package
{
  int id=0;
};


typedef struct package Package;
Package data;


void setup()
{
  Serial.begin(115200);
  delay(1000);
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);

  pinMode(shiftUp, INPUT_PULLUP);
  pinMode(shiftDown, INPUT_PULLUP);
  delay(1000);
}

void loop()
{
  if ((digitalRead(shiftUp) == 0) && (lastUp == false)) {
  data.id = 1;
  myRadio.write(&data, sizeof(data));
  lastUp = true;
  delay(200);
  }

  if ((digitalRead(shiftDown) == 0) && (lastDown == false)) {
  data.id = 0;
  myRadio.write(&data, sizeof(data));
  lastDown = true;
  delay(200);
  }

if (digitalRead(shiftUp) == 1) {
  lastUp = false;
  delay(30);
}

if (digitalRead(shiftDown) == 1) {
  lastDown = false;
  delay(30);
}
  
}
