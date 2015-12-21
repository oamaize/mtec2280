
 #include "pitches.h"

String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete
const int tonePin = 2;
int toneNumber = -1;



void setup() {
// initialize serial:
Serial.begin(9600);
// reserve 200 bytes for the inputString:
inputString.reserve(200);
pinMode(tonePin, OUTPUT);
}
void loop() {
serialEvent(); //call the function
// print the string when a newline arrives:
if (stringComplete) {
inputString.trim();
Serial.println(inputString);
//toneNumber = inputString.toInt();

if(inputString.equals("start")){
  
  int melody[] = {
NOTE_C2, NOTE_F3, NOTE_C3, NOTE_A2,
NOTE_C3, NOTE_F3, NOTE_C3,
NOTE_C3, NOTE_F3, NOTE_C3, NOTE_F3,
NOTE_AS3, NOTE_G3, NOTE_F3, NOTE_E3, NOTE_D3, NOTE_CS3,
NOTE_C3, NOTE_F3, NOTE_C3, NOTE_A2, // the same again
NOTE_C3, NOTE_F3, NOTE_C3,
NOTE_AS3, 0, NOTE_G3, NOTE_F3,
NOTE_E3, NOTE_D3, NOTE_CS3, NOTE_C3};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
4, 4, 4, 4,
4, 4, 2,
4, 4, 4, 4,
3, 8, 8, 8, 8, 8,
4, 4, 4, 4, // the same again
4, 4, 2,
4, 8, 8, 4, 4,
4, 4, 4, 4,
0};

 for (int thisNote = 0; noteDurations[thisNote] != 0; thisNote++) {
// to calculate the note duration, take one second
// divided by the note type.
//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
int noteDuration = 2000/noteDurations[thisNote];
tone(tonePin, melody[thisNote],noteDuration * 0.9);
// to distinguish the notes, set a minimum time between them.
// the note's duration + 30% seems to work well:
//int pauseBetweenNotes = noteDuration * 1.30;
//delay(pauseBetweenNotes);
delay(noteDuration);
}
}
if(inputString.equals("win")){
  int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };
    for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(tonePin, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(tonePin);
  }
  
}

if(inputString.equals("lose")){
  
int melody_nak[] = { NOTE_G5, NOTE_G5, NOTE_G5, NOTE_DS5, NOTE_AS5, NOTE_G5, NOTE_DS5, NOTE_AS5, NOTE_G5};
int noteDurations_nak[] = { 330, 330, 330, 250, 120, 330, 250, 120, 500 };

playMelody(melody_nak, noteDurations_nak, sizeof(melody_nak)/sizeof(melody_nak[0]));

int melody_ack[] = { NOTE_D6, NOTE_A6, NOTE_C7, NOTE_A6 };
int noteDurations_ack[] = { 120, 500, 120, 500 };

playMelody(melody_ack, noteDurations_ack, sizeof(melody_ack)/sizeof(melody_ack[0]));

}


inputString = "";
stringComplete = false;
}
if (toneNumber > -1) {
tone(tonePin, toneNumber, 500);
toneNumber = -1;
}
}
/*
SerialEvent occurs whenever a new data comes in the
hardware serial RX. This routine is run between each
time loop() runs, so using delay inside loop can delay
response. Multiple bytes of data may be available.
*/
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

void toneManual(int pin, int frequency, int duration)
{
  unsigned long period = 1000000/frequency;
  unsigned long length;
  boolean state = false;
  for (length = 0; length < (long) duration * 1000; length += period) {
    state = !state;
    digitalWrite(pin, state);
    /* The 50uS correspond to the time the rest of the loop body takes.
     * It seems about right, but has not been tuned precisely for
     * a 16MHz ATMega. */
    delayMicroseconds(period - 50);
  }
}

void playMelody(int *melody, int *noteDurations, int notes)
{
  int i;
  for (i = 0; i < notes; i++) {
    toneManual(tonePin, melody[i], noteDurations[i]);
    delay(noteDurations[i] * 6/10);
  }
}
