#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
const int buttonPin2 = 2; // the number of the pushbutton pin
const int buttonPin3 = 3; // the number of the pushbutton pin
int buttonPushCounter2 = -1; // counter for the number of button presses
int buttonState2 = 0; // current state of the button
int lastButtonState2 = 0; // previous state of the button
int buttonPushCounter3 = 0; // counter for the number of button presses
int buttonState3 = 0; // current state of the button
int lastButtonState3 = 0; // previous state of the button
int gameState = -1;
int doorWithPrize = -1;
int wouldSwitchTo = -1;
int pickedDoor = -1;
void setup() {
// set up the LCD's number of columns and rows:
lcd.begin(16, 2);

pinMode(buttonPin2, INPUT);
pinMode(buttonPin3, INPUT);
Serial.begin(9600);
doorWithPrize = int(random(3));
//doorWithPrize = 2;
Serial.println("prize door: ");
Serial.println(doorWithPrize);
}
void loop() {
  switch(gameState){
  case -1:
    start();
    break;
  case 0:
    case0();
    break;
  case 1:
    case1();
    break;
  case 2:
    case2();
    break;
  case 3:
    case3();
  }
}
void start(){
lcd.setCursor(0, 0);
lcd.print("Press any button");
lcd.setCursor(0, 1);
lcd.print("to start...");
buttonState2 = digitalRead(buttonPin2);
buttonState3 = digitalRead(buttonPin3);
if(buttonState2 != lastButtonState2 || buttonState3 != lastButtonState3){
if(buttonState2 == HIGH) { lcd.clear(); gameState++;}
if(buttonState3 == HIGH) { lcd.clear(); gameState++;}
}
lastButtonState2 = buttonState2;
lastButtonState3 = buttonState3;
// Serial.println("prize door: ");
// Serial.println(doorWithPrize);

}
void case0(){
  if(buttonPushCounter2 == -1){
    lcd.setCursor(0, 0);
    lcd.print("Pick a door!");
    lcd.setCursor(0, 1);
    lcd.print("A, B, or C");
    buttonPushCounter2++;
  }
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  if(buttonState2 != lastButtonState2){
    if(buttonState2 == HIGH) {
      lcd.clear();
      if(buttonPushCounter2 % 3 == 0){ lcd.setCursor(0,0); lcd.print("I Pick A!"); lcd.setCursor(0, 1); lcd.print("Hit C to confirm.");}
      if(buttonPushCounter2 % 3 == 1){ lcd.setCursor(0,0); lcd.print("I Pick B!"); lcd.setCursor(0, 1); lcd.print("Hit C to confirm.");}
      if(buttonPushCounter2 % 3 == 2){ lcd.setCursor(0,0); lcd.print("I Pick C!"); lcd.setCursor(0, 1); lcd.print("Hit C to confirm.");}
      buttonPushCounter2++;
    }
  }
  if(buttonState3 != lastButtonState3 && (buttonPushCounter2 - 1) != -1 ){
    if(buttonState3 == HIGH){
       lcd.clear();
        gameState++;
    }
  }
  lastButtonState2 = buttonState2;
  lastButtonState3 = buttonState3;
}
void case1(){
  pickedDoor = (buttonPushCounter2 - 1) % 3;
  if(pickedDoor == 0){ lcd.setCursor(0,0); lcd.print("You picked A!");
    if(doorWithPrize == pickedDoor){
      lcd.setCursor(0,1);
      lcd.print("Prize not in B!");
      wouldSwitchTo = 2; // lose
    }else{
      if(doorWithPrize == 1){ lcd.setCursor(0,1); lcd.print("Prize not in C!"); wouldSwitchTo = 1;} //win
      if(doorWithPrize == 2){ lcd.setCursor(0,1); lcd.print("Prize not in B!"); wouldSwitchTo = 2;} //win
    }
  }
  
  if(pickedDoor == 1){ lcd.setCursor(0,0); lcd.print("You picked B!");
    if(doorWithPrize == pickedDoor){
      lcd.setCursor(0,1);
      lcd.print("Prize not in C!");
      wouldSwitchTo = 0; // lose
    }else{
      if(doorWithPrize == 0){ lcd.setCursor(0,1); lcd.print("Prize not in C!"); wouldSwitchTo = 0;} //win
      if(doorWithPrize == 2){ lcd.setCursor(0,1); lcd.print("Prize not in A!"); wouldSwitchTo = 2;} //win
    }
  }
  
  if(pickedDoor == 2){ lcd.setCursor(0,0); lcd.print("You picked C!");
    if(doorWithPrize == pickedDoor){
      lcd.setCursor(0,1);
      lcd.print("Prize not in A!");
      wouldSwitchTo = 1; //lose
    }else{
      if(doorWithPrize == 0){ lcd.setCursor(0,1); lcd.print("Prize not in B!"); wouldSwitchTo = 0;}
      if(doorWithPrize == 1){ lcd.setCursor(0,1); lcd.print("Prize not in A!"); wouldSwitchTo = 1;}
    }
  }
  
  buttonState3 = digitalRead(buttonPin3);
  
  if(buttonState3 != lastButtonState3){
    if(buttonState3 == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Do you want");
      lcd.setCursor(0,1);
      lcd.print("to switch? Y/N");
      buttonPushCounter2 = 0;
      gameState++;
    }
  }    
  lastButtonState3 = buttonState3;
}

void case2(){
  
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  
  if(buttonState2 != lastButtonState2){
    if(buttonState2 == HIGH) {
      lcd.clear();
  if(buttonPushCounter2 % 2 == 0){ lcd.setCursor(0,0); lcd.print("Yes, Switch!"); lcd.setCursor(0, 1); lcd.print("Hit C to confirm.");}
  if(buttonPushCounter2 % 2 == 1){ lcd.setCursor(0,0); lcd.print("No, Keep Door!"); lcd.setCursor(0, 1); lcd.print("Hit C to confirm.");}
    buttonPushCounter2++;
  }
  }
  if(buttonState3 != lastButtonState3){
    if(buttonState3 == HIGH){
      lcd.clear();
      int yesOrNo = (buttonPushCounter2 - 1) % 2;
    if(yesOrNo == 0){
      if(wouldSwitchTo == doorWithPrize){ lcd.clear(); lcd.setCursor(0,0); lcd.print("You Win!"); lcd.setCursor(0, 1); lcd.print("Hit C to restart.");}
        else{ lcd.clear(); lcd.setCursor(0,0); lcd.print("You Lose!"); lcd.setCursor(0, 1); lcd.print("Hit C to restart.");}
     }else if(yesOrNo == 1){
        if(pickedDoor == doorWithPrize){ lcd.clear(); lcd.setCursor(0,0); lcd.print("You Win!"); lcd.setCursor(0, 1); lcd.print("Hit C to restart.");}
        else{ lcd.clear(); lcd.setCursor(0,0); lcd.print("You Lose!"); lcd.setCursor(0, 1); lcd.print("Hit C to restart.");}
     }
      gameState++;
    }
  }
  lastButtonState2 = buttonState2;
  lastButtonState3 = buttonState3;
}

void case3(){
  buttonState3 = digitalRead(buttonPin3);

  if(buttonState3 != lastButtonState3){
    if(buttonState3 == HIGH){
      lcd.clear();
      buttonPushCounter2 = -1;
      gameState = -1;
      doorWithPrize = int(random(3));
//doorWithPrize = 2;
      Serial.println("prize door: ");
      Serial.println(doorWithPrize);
    }
  }
  lastButtonState3 = buttonState3;
}
