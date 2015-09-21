const int LED = 9;
const int BUTTON = 2;
boolean lastButton = LOW;
boolean currentButton = LOW;
boolean ledOn = false;


void setup() {
  // put your setup code here, to run once:
pinMode(LED, OUTPUT);
pinMode(BUTTON, INPUT);
}

boolean debounce(boolean last){
 boolean current = digitalRead(BUTTON);
  if (last != current){
   delay(5);
    current = digitalRead(BUTTON);
  } 
}

void loop() {
  // put your main code here, to run repeatedly:
currentButton = debounce(lastButton);
if(lastButton == LOW && currentButton == HIGH){
  ledOn = !ledOn;
}
lastButton = currentButton;
digitalWrite(LED, ledOn);

}
