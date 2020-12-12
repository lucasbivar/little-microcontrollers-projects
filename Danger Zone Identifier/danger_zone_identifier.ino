int Rpin = 11;
int Gpin = 9;
int Bpin = 10;
int triggerPin = 2;
int echoPin = 3;
float echoTime = 0;
const float speedSound_mps = 340;
const float speedSound_mpus = 0.000340;

void setColor(int red, int green, int blue){
  analogWrite(Rpin, red);
  analogWrite(Gpin, green);
  analogWrite(Bpin, blue);
}


void triggerUltrasonicPulse(){
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
}

float calculatesDistance(float usTime){

  return ((usTime*speedSound_mpus)/2);
  
}
void setup() {
  delay(500);
  pinMode(Rpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
  pinMode (triggerPin, OUTPUT); 
  pinMode (echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
    triggerUltrasonicPulse();
    echoTime = pulseIn(echoPin, HIGH);
    float dist = calculatesDistance(echoTime) * 100;
    Serial.print("Distance in centimeters: "); 
    Serial.println(dist);
    if(dist < 10.0){
      setColor(255, 0 , 0);
    }else if(dist > 10 && dist < 30){
      setColor(255, 255 , 0);
    }else{
      setColor(0, 255, 0);
    }
    delay(10);
}
