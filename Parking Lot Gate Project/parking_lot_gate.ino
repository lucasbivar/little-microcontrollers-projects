#include <Servo.h>
#include <IRremote.h>

int redLedPin = 7;
int greenLedPin = 10;
int servoPin = 5;
int servoPosition = 0;
int IRPin = 11;
bool greenLed = false, redLed = true, parkingLotGateState = false;

IRrecv irrecv(IRPin);
decode_results results;
Servo servo1;

void changeLedState(){
  redLed = !redLed;
  digitalWrite(redLedPin, redLed);
  greenLed = !greenLed;
  digitalWrite(greenLedPin, greenLed);
  delay(100); 
}

void setup(){
  Serial.begin(9600);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  digitalWrite(redLedPin, redLed);
  servo1.attach(servoPin);
  servo1.write(90);
  irrecv.enableIRIn();
}

void loop(){

  if(irrecv.decode(&results)){  
    
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
  
  if(results.value == 0xBDA857){
    
    if(parkingLotGateState == false){
      
      changeLedState(); 
      for(servoPosition = 89; servoPosition > 1; servoPosition--){
        servo1.write(servoPosition);
        delay(20);
      }
      delay(1000);
      parkingLotGateState = true;
      
    }else{
      
      changeLedState();
      for(servoPosition = 0; servoPosition < 90; servoPosition++){
        servo1.write(servoPosition);
        delay(20);
      }
      delay(1000);
      parkingLotGateState = false;
    } 
       
   }
}
