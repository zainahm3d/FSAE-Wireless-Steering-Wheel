#include <SPI.h>  
#include "RF24.h" 

int upPin = 2;
int downPin = 4;

RF24 myRadio (7, 8); 
struct package
{
  int id=0;
  float temperature = 0.0;
  char  text[100] ="empty";
};

byte addresses[][6] = {"0"}; 



typedef struct package Package;
Package data;

void setup() 
{

  pinMode(upPin, OUTPUT);
  pinMode(downPin, OUTPUT);
  
  Serial.begin(115200);
  delay(1000);

  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}


void upShift(){
  Serial.println("Shift up");
        
  digitalWrite(upPin, HIGH);
  delay(220);
  digitalWrite(upPin, LOW);
  delay(50);
}

void downShift(){
  Serial.println("Shift down");
  
  digitalWrite(downPin, HIGH);
  delay(220);
  digitalWrite(downPin, LOW);
  delay(50);
}


void loop()  
{

  if ( myRadio.available()) 
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }
    
    if (data.id == 0){
      downShift();
    }

    else if (data.id == 1) {
      upShift();
    }

  }}
