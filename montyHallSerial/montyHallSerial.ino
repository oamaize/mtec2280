//This is my implementation of the Monty Hall game using text Serial Input function!


/*

Comment out lines 18, 19, 147 and 148 if you don't want the player to know 
which box (0,1,or2) has the prize! 

OR, Keep them uncommented to make sure 
game results are accurate. :)

*/

int gameState = -1;
int doorWithPrize = -1;
int wouldSwitchTo = -1;
int pickedDoor = -1;

String inputString = "";
boolean stringComplete = false;
boolean enterSelection = false;
int pickedVal = 0;

void setup() {

Serial.begin(9600);
doorWithPrize = int(random(3));
Serial.println("prize door: ");
Serial.println(doorWithPrize);
Serial.println("Please enter start");
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

if(stringComplete == true){
  if(inputString.equals("start")){
    inputString = "";
    stringComplete = false;
    enterSelection = false;
    gameState++;
  }else{
    inputString = "";
    stringComplete = false;
    Serial.println("Please enter start");
  }
}
}
void case0(){
  
  if(enterSelection == false){
    Serial.println("Pick a door: 0, 1, or 2");
    enterSelection = true;    
  }
  if(stringComplete == true){
    pickedVal = inputString.toInt();
    if(pickedVal >= 0 && pickedVal <= 2){
    inputString = "";
    stringComplete = false;
    gameState++;
    }else{
    stringComplete = false;
    inputString = "";
    Serial.println("Wrong Input! Please try again");
    }
  } 
}
void case1(){  
  if(pickedVal == 0){ 
    Serial.println("You picked 0!");
    if(doorWithPrize == pickedVal){
      Serial.println("Prize not in 1!");
      wouldSwitchTo = 2; // lose
    }else{
      if(doorWithPrize == 1){ Serial.println("Prize not in 2!"); wouldSwitchTo = 1;} //win
      if(doorWithPrize == 2){ Serial.println("Prize not in 1!"); wouldSwitchTo = 2;} //win
    }
  }
  
  if(pickedVal == 1){ 
    Serial.println("You picked 1!");
    if(doorWithPrize == pickedVal){
      Serial.println("Prize not in 2!");
      wouldSwitchTo = 0; // lose
    }else{
      if(doorWithPrize == 0){  Serial.println("Prize not in 2!"); wouldSwitchTo = 0;} //win
      if(doorWithPrize == 2){  Serial.println("Prize not in 0!"); wouldSwitchTo = 2;} //win
    }
  }
  
  if(pickedVal == 2){ 
    Serial.println("You picked 2!");
    if(doorWithPrize == pickedVal){

      Serial.println("Prize not in 0!");
      wouldSwitchTo = 1; //lose
    }else{
      if(doorWithPrize == 0){ Serial.println("Prize not in 1!"); wouldSwitchTo = 0;}
      if(doorWithPrize == 1){ Serial.println("Prize not in 0!"); wouldSwitchTo = 1;}
    }
  }
  Serial.println("Do you want to switch? Y/N");
  stringComplete = false;
  gameState++;

}

void case2(){
  
  if(stringComplete == true){
    if(inputString.equals("Y")){
      if(wouldSwitchTo == doorWithPrize){ 
        Serial.println("You Win! (hit any key to restart)");
    }
        else{ 
        Serial.println("You Lose! (hit any key to restart)");
      }
      stringComplete = false;
     gameState++; 
    }else if (inputString.equals("N")){
      if(pickedVal == doorWithPrize){
      Serial.println("You Win! (hit any key to restart)");
    }
        else{ 
        Serial.println("You Lose! (hit any key to restart)");
      }
      stringComplete = false;
      gameState++;
    } else{
    stringComplete = false;
    inputString = "";
    Serial.println("Wrong Input! Please try again");
    }
  }
}

void case3(){
  if(stringComplete == true){
  gameState = -1;
  doorWithPrize = int(random(3));
  Serial.println("prize door: ");
  Serial.println(doorWithPrize);
  }

}
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    //inputString += inChar;


    if (inChar != '\n') {
      inputString += inChar;
    }

    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
