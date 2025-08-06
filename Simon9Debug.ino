/*
Simon on the Arduino
by Tristan Clawson
rev: 0.91 - Debug
red date:  7/12/2025
 */


//pins: 2,3,4,5
const int ledPin2 = 2;    // LED connected to digital pin 2
const int ledPin3 = 3;    // LED connected to digital pin 3
const int ledPin4 = 4;    // LED connected to digital pin 4
const int ledPin5 = 5;    // LED connected to digital pin 5

//buttonPress: 8,9,10,11
const int buttonPin8 = 8; //RED
const int buttonPin9 = 9; //YELLOW
const int buttonPin10 = 10; //Green
const int buttonPin11 = 11; //BLUE

//
int button8State;
int button9State;
int button10State;
int button11State;

int randNumber = 0;  //sets a random value that will corispond to a color in void setupLoop();
int trackerArraySetup = 0;
//int i;  //iteration of the game loop
int position; // position of the tracker during void setupLoop();
int x;  //iteration of the display loop
int k;  //rotation of the display loop
int n; //reset loop
int m; //input loop
// int i; //TEMP replaced by sequence position

int printing = 0; //print position of void printLoop()

//int buttonPress = 0; //input for the buttons
int test = 0;
int var = 0;
int light = 0;    //
int gameLoop = 0;   //iterate the input loop
int gameTurn = 0; //tracks the game turn in void loop()//iterate the input loop
int sequencePosition = 0; //checks if the user inputed a specific right sequense value in void inputLoop()  //array position to go through the users input in void inputLoop()
int compaireLoop = 0;  //counter variable for IF statements void checkLoop()
//Note sequencePosition becomes equal to compaireLoop in void checkLoop()
int inputtest[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ; //Initial setup of all 0's, will set random values in setupLoop
int tracker[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;  //Initial setup of all 0's, will set random values in setupLoop



//AI______________________
// Debounce parameters
//int ledState = LOW;  
const unsigned long debounceDelay = 50;  // ms

// State tracking per button
const int numButtons        = 4;
int  lastReadState[numButtons];
int  stableState[numButtons];
unsigned long lastDebounceTime[numButtons];

// Press event log
const int maxPresses = 20;
int   pressEvents[maxPresses];
int   pressCount = 0;
//________________________

// failState() variables
int whipeLight;
int failLight;

void setupLoop();
void printLoop();
void failState();
void inputLoop();
void checkLoop();
void inputLoop();
void(* resetFunc) (void) = 0;  // function pointer to address 0

void setup() 
{
Serial.begin(9600);
randomSeed(analogRead(0));  // Better randomness that doesn't start at the same point
  // set the digital pin as output:
  pinMode(ledPin2, OUTPUT); //keeps the LED lit up
                      //digitalWrite (ledPin2, HIGH);
  pinMode(ledPin3, OUTPUT); //keeps the LED lit up
                       //digitalWrite (ledPin3, HIGH);
  pinMode(ledPin4, OUTPUT); //keeps the LED lit up
                       //digitalWrite (ledPin4, HIGH);
  pinMode(ledPin5, OUTPUT); //keeps the LED lit up
                       //digitalWrite (ledPin5, HIGH);
  pinMode(buttonPin8, INPUT_PULLUP);  //Now your buttons will read HIGH when unpressed, and LOW when pressed. That’s what you want.
  pinMode(buttonPin9, INPUT_PULLUP);
  pinMode(buttonPin10, INPUT_PULLUP);
  pinMode(buttonPin11, INPUT_PULLUP);
  

  /*
  pinMode(buttonPin8, INPUT);
  pinMode(buttonPin9, INPUT);
  pinMode(buttonPin10, INPUT);
  pinMode(buttonPin11, INPUT); 
  */
}


//________________________________________________________________________________________ 


//Don't use letter variables
//Print statements after every iteration

void loop() //
{
Serial.println("S T A R T   O F   L O O P"); 
// setting up the random array
setupLoop();

//________________________________________________________________________________________ 

//gameTurn
// while bool is true?  when to check,  else fail
gameTurn = 0;
gameLoop = 0;

while ( gameTurn < 21 ){
printLoop();
inputLoop();                                                                                                                                                                             
//inputLoop();
checkLoop();
//counting
//      x = 0; //<< upper error
//      k = 0;
gameTurn ++; //increases the game turn
gameLoop ++; //increases the length of each challenge
Serial.println("End Of GameTurn_______________________________________________"); 
}
failState();
//restart put in failstate,  or breakout / break
          m++; 

                             
Serial.println("E N D   O F   L O O P");                             
} 


//________________________________________________________________________________________    

void setupLoop(){
  // Setup loop
       Serial.println("     Start of array setup"); 
trackerArraySetup = 0;
position = 0;
  while (trackerArraySetup < 21 ){
  randNumber = random(2,6); // generate random number between 2 to 5  (Includes 2, but not 5?)
  tracker[position] = randNumber;   
    Serial.print("TrackerArraySetup Value " );
    Serial.println(tracker[position]);
   trackerArraySetup++;
   position ++;
    //Serial.print("Tracker step:" );
    //Serial.println(trackerArraySetup);
  }
   Serial.println("     End of array setup"); 
   Serial.println(" ");
}


void printLoop(){
printing = gameLoop;

Serial.println("- STARTING PRINTLOOP -" ); 
Serial.print("printLoop print = ");
Serial.println(printing);
Serial.print("printLoop gameLoop = ");
Serial.println(gameLoop);
Serial.print("printLoop gameTurn = ");
Serial.println(gameTurn);


//get to print the loop
int asdf = 0;
asdf = asdf + printing;
while (asdf < 20){
            Serial.print("Tracker Array ");
            Serial.println(tracker[asdf]);
  asdf++;
}


while (printing > -1){

  
//while ( printing < gameTurn ){
//problem with printing here
Serial.print("INSIDE while printing ");
Serial.println(printing);
if (  tracker[printing] == 2 )
      {
            digitalWrite(ledPin2, HIGH);
            delay (900);
            Serial.println("TRACKER printLoop RED ledPin2 ButtonPin8 ");
            digitalWrite(ledPin2, LOW);
            delay (500);
       }

else if (  tracker[printing] == 3 )
      {
            digitalWrite(ledPin3, HIGH);
            delay (900);
            Serial.println("TRACKER printLoop YELLOW ledPin3 ButtonPin9 ");
            digitalWrite(ledPin3, LOW);
            delay (500);            
       }

else if (  tracker[printing] == 4 )
      {
            digitalWrite(ledPin4, HIGH);
            delay (900);
            Serial.println("TRACKER printLoop GREEN ledPin4 ButtonPin10 ");
            digitalWrite(ledPin4, LOW);
            delay (500);
       }

else if (  tracker[printing] == 5 )
      {
            digitalWrite(ledPin5, HIGH);
            delay(900);
            Serial.println("TRACKER printLoop GREEN ledPin5 ButtonPin11 ");
            digitalWrite(ledPin5, LOW);
            delay (500);
       }

    else {
    Serial.println("SERIOUS printLoop() ERROR" ); 
    Serial.print("tracker[print] " ); 
    Serial.println( tracker[printing] );    

    }

    Serial.print("Tracker Value " );
    Serial.println(tracker[printing]);
    Serial.print("Print Value " );
    Serial.println(printing);

printing --;

  }
delay (500);
//return;

}

//________________________________________________________________________________________   

void inputLoop(){

sequencePosition = 0;
Serial.println("Waiting for input.  ");
// holding pattern

//HOLDINGLOOP: //from the GOTO,  I am not proud of this


  Serial.print("gameLoop in inputLoop()  ");
  Serial.println(gameLoop);
  Serial.print("sequencePosition in inputLoop()  ");
  Serial.println(sequencePosition);

// main input
while (sequencePosition < gameLoop)
    {
      Serial.println("while input.");


//HOLDING
while (digitalRead(buttonPin8) == HIGH && digitalRead(buttonPin9) == HIGH && digitalRead(buttonPin10) == HIGH && digitalRead(buttonPin11) == HIGH) {
  //do nothing FASTER!
  //Serial.print("Waiting for input.  ");
  delay (10);  //does this lock the user out?
}
//__

      button8State  = digitalRead(buttonPin8);
      button9State  = digitalRead(buttonPin9);
      button10State = digitalRead(buttonPin10);
      button11State = digitalRead(buttonPin11);

          Serial.println("States: ");
          Serial.println(button8State);
          Serial.println(button9State);
          Serial.println(button10State);
          Serial.println(button11State);

      //button input
      //duration = pulseIn(buttonPin10, HIGH);
      //duration = pulseIn(buttonPin11, HIGH);  //pulsIn a built in Debounce?
      // debounce?
      //2 button presses problem  stacked IFs?
      // may need some breakout logic


//RED ledPin2 ButtonPin8
      if ( button8State == LOW )
      {
        inputtest[sequencePosition] = 2;
          // Program stays in while loop (Lighting up the button) until the user releases it.  This should help with accadental double taps.
          while (digitalRead(buttonPin8) == LOW) {
            digitalWrite(ledPin2, HIGH); //Light stays on
            delay (10);
            Serial.print("RED ledPin2 ButtonPin8 Value inputed:  ");
            Serial.println(inputtest[sequencePosition]);
          }
          digitalWrite(ledPin2, LOW); //Light off
        }
          // Reset the pin to be read again
          button8State = digitalRead(buttonPin8);


//YELLOW ledPin3 ButtonPin9
      else if ( button9State == LOW )
      {
        inputtest[sequencePosition] = 3;
          // Program stays in while loop (Lighting up the button) until the user releases it.  This should help with accadental double taps.
          while (digitalRead(buttonPin9) == LOW) {
            digitalWrite(ledPin3, HIGH); //Light stays on
            delay (10);
            Serial.print("YELLOW ledPin3 ButtonPin9 Value inputed:  ");
            Serial.println(inputtest[sequencePosition]);
          }
          digitalWrite(ledPin3, LOW); //Light off
        }
          // Reset the pin to be read again
          button9State = digitalRead(buttonPin9);


//GREEN ledPin2 ButtonPin8
      else if ( button10State == LOW )
      {
        inputtest[sequencePosition] = 4;
          // Program stays in while loop (Lighting up the button) until the user releases it.  This should help with accadental double taps.
          while (digitalRead(buttonPin10) == LOW) {
            digitalWrite(ledPin4, HIGH); //Light stays on
            delay (10);
            Serial.print("GREEN ledPin4 ButtonPin10 Value inputed:  ");
            Serial.println(inputtest[sequencePosition]);
          }
          digitalWrite(ledPin4, LOW); //Light off
        }
          // Reset the pin to be read again
          button10State = digitalRead(buttonPin10);



//BLUE ledPin5 ButtonPin11
      else if ( button11State == LOW )
      {
        inputtest[sequencePosition] = 5;
          // Program stays in while loop (Lighting up the button) until the user releases it.  This should help with accadental double taps.
          while (digitalRead(buttonPin11) == LOW) {
            digitalWrite(ledPin5, HIGH); //Light stays on
            delay (10);
            Serial.print("BLUE ledPin5 ButtonPin11 Value inputed: ");
            Serial.println(inputtest[sequencePosition]);
          }
          digitalWrite(ledPin5, LOW); //Light off
        }
          // Reset the pin to be read again
          button11State = digitalRead(buttonPin11);

       
//Error catching
                      else if (buttonPin10 > 11 ) 
                    {
                      Serial.println("Input UPPER bounds error");
                      }  
                    else if (buttonPin11 < 8 ) 
                    {
                      Serial.println("Input LOWER bounds error");
                      }  

    else {
      // Spurious wake‐up? nobody’s actually low.  
      // Skip ahead and wait again.
      continue;
    }                     
//Serial.println("Made it through the input loop +++++++++++++++++++++++++++");
//once the input is done call 

//compaireLoop = sequencePosition;
Serial.println("Got back from checkLoop() and now trying to itterate.");
//then iterate the loop

checkLoop();
sequencePosition ++;

//goto HOLDINGLOOP;  //I'm not proud of this, its at the top of the holding loop.



       }
            
 }             


//________________________________________________________________________________________  


void checkLoop(){
  Serial.println("Made it into the checkloop +++++++++++++++++++++++++++");
// simple check values loop
compaireLoop = sequencePosition;

Serial.println("Starting the array checking process");
Serial.print("compireLoop Value = ");
Serial.println(compaireLoop);

int asdf = 0;
while (asdf < 20){
            Serial.print("inputtest Array! ");
            Serial.println(inputtest[asdf]);
  asdf++;
}

asdf = 0;
while (asdf < 20){
            Serial.print("Tracker Array! ");
            Serial.println(tracker[asdf]);
  asdf++;
}

/*
//First 2 tests see if the numbers are out of bounds.
//Use 0 because that is what the array is initialized to.
if (inputtest[compaireLoop] > 5 || inputtest[compaireLoop] < 0 ){
Serial.println("Error. First.  Something has gone seriously wrong with checking the arrays!");
Serial.println(inputtest[compaireLoop]);
Serial.println(compaireLoop);
failState();
}

//First 2 tests see if the numbers are out of bounds.
if (tracker[compaireLoop] > 5 || tracker[compaireLoop] < 1 ){
Serial.println("Error.  Second.  Something has gone seriously wrong with checking the arrays!");
failState();
}
*/
//equal
if (inputtest[compaireLoop] == tracker[compaireLoop] ){
Serial.println("Color match.  Simon is happy!");
return; // exits checkLoop()
}

//not equal
if (inputtest[compaireLoop] != tracker[compaireLoop] ){
Serial.println("Wrong button pressed! /checkLoop");
Serial.print("inputtest: ");
Serial.println(inputtest[compaireLoop] );
Serial.print("tracker:  ");
Serial.println(tracker[compaireLoop]);
Serial.println(" ");
failState();
}

else {
Serial.println("CheckLoop() Error problem,  Somehow passed both IFs");
}
//inputtest[]
//tracker[] 
//Serial.println("IF statement error");
}


//________________________________________________________________________________________  
// This function flashes the lights to let the player know they have lost
// Will add game restart functionality in later
void failState(){
failLight = 0;

while (failLight < 2){
    digitalWrite (ledPin2, HIGH);
    digitalWrite (ledPin3, HIGH);
    digitalWrite (ledPin4, HIGH);
    digitalWrite (ledPin5, HIGH);
    delay (300);
    digitalWrite (ledPin2, LOW);

    digitalWrite (ledPin3, LOW);
    digitalWrite (ledPin4, LOW);
    digitalWrite (ledPin5, LOW);
    delay (200);

    failLight ++ ;
  }

whipeLight = 0;
  while (whipeLight < 2){
    digitalWrite (ledPin2, HIGH);
    delay (100);
    digitalWrite (ledPin2, LOW); 
    digitalWrite (ledPin3, HIGH);
    delay (100);
    digitalWrite (ledPin3, LOW); 
    digitalWrite (ledPin4, HIGH);
    delay (100);
    digitalWrite (ledPin3, LOW); 
    digitalWrite (ledPin4, HIGH);
    delay (100);
    digitalWrite (ledPin4, LOW);  
    digitalWrite (ledPin5, HIGH);
    delay (100);
    digitalWrite (ledPin5, LOW);   

    whipeLight ++;
  }
//Restart Arduino from mem spot 0
resetFunc();
}
