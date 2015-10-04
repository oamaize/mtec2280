/*
mode 1: // red or white persist @ varying brightness
pot + red fade in, white fade out
pot - red fade out, white fade in

mode 2: // light up one after another in sequence
pot + speed up cycle
pot - slow down cycle

mode 3: //red lights vs. white lights alternating constant brightness
pot + speed up cycle
pot - slow down cycle

mode 4: //random lights
pot + speed up cycle
pot - slow down cycle
*/

const int RLED1 = 11;
const int RLED2 = 10;
const int RLED3 = 9;
const int WLED1 = 6;
const int WLED2 = 5;


const int BUTTON = 2;
boolean lastButton = LOW;
boolean currentButton = LOW;
int ledMode = 0;
int potValue = 0;


void setup() {
  // put your setup code here, to run once:
pinMode(RLED1, OUTPUT);
pinMode(RLED2, OUTPUT);
pinMode(RLED3, OUTPUT);
pinMode(WLED1, OUTPUT);
pinMode(WLED2, OUTPUT);
pinMode(BUTTON, INPUT);

Serial.begin(9600);
}

boolean debounce(boolean last){
 boolean current = digitalRead(BUTTON);
  if (last != current){
   delay(5);
    current = digitalRead(BUTTON);
  } 
}

void setMode(int mode){
 if(mode == 1){
   potValue = analogRead(A0);
   int newPotValueR = map(potValue,0,1023,0,255);
   int newPotValueW = 255-newPotValueR;
    analogWrite(RLED1, newPotValueR);
    analogWrite(RLED2, newPotValueR);
    analogWrite(RLED3, newPotValueR);
    analogWrite(WLED1, newPotValueW);
    analogWrite(WLED2, newPotValueW);
 }
 else if(mode == 2){
   potValue = analogRead(A0);
   digitalWrite(RLED1, HIGH);
   digitalWrite(RLED2, LOW);
   digitalWrite(RLED3, LOW);
   digitalWrite(WLED1, LOW);
   digitalWrite(WLED2, LOW);
   delay(potValue);
   digitalWrite(RLED1, LOW);
   digitalWrite(RLED2, LOW);
   digitalWrite(RLED3, LOW);
   digitalWrite(WLED1, HIGH);
   digitalWrite(WLED2, LOW);
   delay(potValue);
   digitalWrite(RLED1, LOW);
   digitalWrite(RLED2, HIGH);
   digitalWrite(RLED3, LOW);
   digitalWrite(WLED1, LOW);
   digitalWrite(WLED2, LOW);
   delay(potValue);
   digitalWrite(RLED1, LOW);
   digitalWrite(RLED2, LOW);
   digitalWrite(RLED3, LOW);
   digitalWrite(WLED1, LOW);
   digitalWrite(WLED2, HIGH);
   delay(potValue);
   digitalWrite(RLED1, LOW);
   digitalWrite(RLED2, LOW);
   digitalWrite(RLED3, HIGH);
   digitalWrite(WLED1, LOW);
   digitalWrite(WLED2, LOW);
   delay(potValue);

 }
 else if(mode == 3){
   potValue = analogRead(A0);
   digitalWrite(RLED1, HIGH);
   digitalWrite(RLED2, HIGH);
   digitalWrite(RLED3, HIGH);
   digitalWrite(WLED1, LOW);
   digitalWrite(WLED2, LOW);
   delay(potValue);
   digitalWrite(RLED1, LOW);
   digitalWrite(RLED2, LOW);
   digitalWrite(RLED3, LOW);
   digitalWrite(WLED1, HIGH);
   digitalWrite(WLED2, HIGH);
   delay(potValue);
 }
else if(mode == 4){
  potValue = analogRead(A0);

  int rand = random(5);
  if(rand == 0){
   digitalWrite(RLED1, HIGH);
   digitalWrite(RLED2, LOW);
   digitalWrite(RLED3, LOW);
   digitalWrite(WLED1, LOW);
   digitalWrite(WLED2, LOW);
   delay(potValue);
  }else if(rand == 1){
   digitalWrite(RLED1, LOW);
   digitalWrite(RLED2, HIGH);
   digitalWrite(RLED3, LOW);
   digitalWrite(WLED1, LOW);
   digitalWrite(WLED2, LOW);
   delay(potValue);
  }else if(rand == 2){
   digitalWrite(RLED1, LOW);
   digitalWrite(RLED2, LOW);
   digitalWrite(RLED3, HIGH);
   digitalWrite(WLED1, LOW);
   digitalWrite(WLED2, LOW);
   delay(potValue);
  }else if(rand == 3){
   digitalWrite(RLED1, LOW);
   digitalWrite(RLED2, LOW);
   digitalWrite(RLED3, LOW);
   digitalWrite(WLED1, HIGH);
   digitalWrite(WLED2, LOW);
   delay(potValue);
  }else{
   digitalWrite(RLED1, LOW);
   digitalWrite(RLED2, LOW);
   digitalWrite(RLED3, LOW);
   digitalWrite(WLED1, LOW);
   digitalWrite(WLED2, HIGH);
   delay(potValue);
  }
 }
else{
   digitalWrite(RLED1, LOW);
   digitalWrite(RLED2, LOW);
   digitalWrite(RLED3, LOW);
   digitalWrite(WLED1, LOW);
   digitalWrite(WLED2, LOW);
 }
}

void loop() {
  // put your main code here, to run repeatedly:
currentButton = debounce(lastButton);
if(lastButton == LOW && currentButton == HIGH){
  ledMode++;
}
lastButton = currentButton;
if(ledMode == 5) ledMode = 0;
setMode(ledMode);

}
