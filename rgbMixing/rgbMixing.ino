const int BLED = 9;
const int GLED = 10;
const int RLED = 11;

const int BUTTON = 2;
boolean lastButton = LOW;
boolean currentButton = LOW;
int ledMode = 0;


void setup() {
  // put your setup code here, to run once:
pinMode(BLED, OUTPUT);
pinMode(RLED, OUTPUT);
pinMode(GLED, OUTPUT);
pinMode(BUTTON, INPUT);
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
   //digitalWrite(RLED, HIGH);
   //digitalWrite(GLED, LOW);
   //digitalWrite(BLED, LOW);
   
   for(int i = 0; i < 255; i++){
     analogWrite(RLED, i);
     delay(10);
 }
    for(int i = 255; i > 0; i--){
     analogWrite(RLED, i);
     delay(10); 
 }
 }
 else if(mode == 2){
   digitalWrite(RLED, LOW);
   digitalWrite(GLED, HIGH);
   digitalWrite(BLED, LOW);
 }
 else if(mode == 3){
   digitalWrite(RLED, LOW);
   digitalWrite(GLED, LOW);
   digitalWrite(BLED, HIGH);
 }
else if(mode == 4){
   analogWrite(RLED, 127);
   analogWrite(GLED, 0);
   analogWrite(BLED, 127);
 }
 else if(mode == 5){
   analogWrite(RLED, 0);
   analogWrite(GLED, 127);
   analogWrite(BLED, 127);
 }
 else if(mode == 6){
   analogWrite(RLED, 127);
   analogWrite(GLED, 127);
   analogWrite(BLED, 0);
 }
 else if(mode == 7){
   analogWrite(RLED, 255);
   analogWrite(GLED, 255);
   analogWrite(BLED, 255);
 }
 else{
   digitalWrite(RLED, LOW);
   digitalWrite(GLED, LOW);
   digitalWrite(BLED, LOW);
 }
}

void loop() {
  // put your main code here, to run repeatedly:
currentButton = debounce(lastButton);
if(lastButton == LOW && currentButton == HIGH){
  ledMode++;
}
lastButton = currentButton;
if(ledMode == 8) ledMode = 0;
setMode(ledMode);

}
