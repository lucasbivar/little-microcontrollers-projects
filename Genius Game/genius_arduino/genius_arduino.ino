int redButton = 10;
int redLed = 9;
int yellowButton = 7;
int yellowLed = 6;
int greenButton = 5;
int greenLed = 4;
int whiteButton = 13;
int whiteLed = 2;
int buzzer = 12;
int matchs = 1;
int random_led;
int sequence[50];
int leds[4] = {whiteLed, greenLed, yellowLed, redLed};
int notes[4] = {261, 293,329,349};
int pointer;
int before_match = 0;

bool check_button_pressed(int color, int button, int note){

  if(digitalRead(button) == LOW){
    tone(buzzer, note);
    delay(100);
    digitalWrite(color, HIGH);
    delay(150);
    digitalWrite(color, LOW);
    delay(100); 
    noTone(buzzer);
    return true;
  }
  return false;
}

bool check_all_buttons(){
  if(check_button_pressed(whiteLed,whiteButton, 261) == true){
    return false;
  }
  if(check_button_pressed(greenLed, greenButton, 293) == true){
    return false;
  }
  if(check_button_pressed(yellowLed,yellowButton, 329) == true){
    return false;
  }
  if(check_button_pressed(redLed, redButton, 349) == true){
    return false;
  }
  return true;
}

void blink_led(int led){
    tone(buzzer, notes[led]);
    delay(100);
    digitalWrite(leds[led], HIGH);
    delay(200);  
    digitalWrite(leds[led], LOW);
    delay(100); 
    noTone(buzzer);
}
void led_new_game(){
  bool ok = true;
  while(true){
    
    for(int j = 0; j < 4; j++){
      digitalWrite(leds[j], HIGH);
      if(check_all_buttons() == false){
        ok = false;
      }
      delay(50);
    }
    if(ok == false) break;
    for(int j = 3; j > -1; j--){
      digitalWrite(leds[j], LOW);
      if(check_all_buttons() == false){
        ok = false;
      }
      delay(50);

    }
    if(ok == false) break;
    
  }
  for(int i = 0; i < 3; i++){
    delay(100);
    digitalWrite(leds[0], HIGH);
    digitalWrite(leds[1], HIGH);
    digitalWrite(leds[2], HIGH);
    digitalWrite(leds[3], HIGH);
    delay(100);
    digitalWrite(leds[0], LOW);
    digitalWrite(leds[1], LOW);
    digitalWrite(leds[2], LOW);
    digitalWrite(leds[3], LOW);
    
  }
}

bool check_next_step(int current){
  if(sequence[pointer] == current){
      pointer++;
      if(pointer == matchs){
        before_match += 1;
        matchs++;
        return true;
      }
    }else{
       matchs = 1;
       before_match = 0;
       Serial.println(-3);
       delay(2000);
       return true;
    }
    return false;
  
}
void setup(){
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(whiteLed, OUTPUT);
  pinMode(whiteButton, INPUT_PULLUP);
  pinMode(greenLed, OUTPUT);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(yellowLed, OUTPUT);
  pinMode(yellowButton, INPUT_PULLUP);
  pinMode(redLed, OUTPUT);
  pinMode(redButton, INPUT_PULLUP);
}

void loop(){
  if(matchs == 1){
    Serial.println(-1);
    led_new_game();
    Serial.println(-2);
    delay(4500);
  }
  Serial.println(matchs);
  pointer = 0;
  for(int i = 0; i < matchs; i++){
    if( i > before_match-1){
      random_led = random(0, 4);
      sequence[i] = random_led;
    }
    blink_led(sequence[i]);
    delay(700);
  }
  while(true){
    if (check_button_pressed(whiteLed,whiteButton, 261) == true){
      if(check_next_step(0))break;
    }
    if (check_button_pressed(greenLed, greenButton, 293) == true){
      if(check_next_step(1))break;
    }
    if (check_button_pressed(yellowLed,yellowButton, 329) == true){
      if(check_next_step(2))break;
    }
    if (check_button_pressed(redLed, redButton, 349) == true){
      if(check_next_step(3))break;
    }
  }
  delay(1000);
}
