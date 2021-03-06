//Emmilein die kleine Spinne...
//Hier läuft alles zusammen.


#include "Servotor32.h" // call the servotor32 Library
Servotor32 hexy;

//Global Variables
//Do not touch...
unsigned long millisekunden = 0; //replace of millis() for calculate sine.
unsigned long previousMillis = 0; //Used for virtual Timer

//***************************************************SET UP RUNNING-PARAMETER HERE**************************************************************

long interval = 20; //How often the Servos should be updated... Here 1000/20 = 50 times per Second ^= 50Hz. This is the normal update speed for normal servos.

//Change only for finetuning speed and/or if legs hit each other.
const int schrittweiteMin = 1300;
const int schrittweiteMax = 1900;

//Change for finetuning and/or for moving over higher objects.
const int beinHoeheMin = 2000; //Kleiner -> Höher
const int beinHoeheMax = 2350; //Größer -> Tiefer

//Change if the foot isn't high enough to move over objects.
const int fussHoeheMin = 900;
const int fussHoeheMax = 1400;

int frequenz = 1; //Frequency of the sine. Change for more or less speed. If you change this value while running it's cogging. So spd is used for changing speed. Negative frequency causes reversal.


//****************************************************Programmvariablen**************************************************************************
     
int richtung = 0; //0 Geradeaus, 90 ^= 90Grad rechts, -90 ^= -90Grad links
int spd = 0;//This is the running speed of hexy. It's used for counting up milliseconds, so higher spd causes faster running but to high causes cogging.

void setup() {
  hexy.begin();
  //standUp();

}

void loop() {
  update(); //Check if Servos have to be updated
  parseSerial(); //Look for new commands
}







