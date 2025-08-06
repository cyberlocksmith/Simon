/*
Simon on the Arduino
by Tristan Clawson
rev: 1.01 Final
red date:  7/31/2025
 */


/***********************************************************************************************
Simon is based on the 1978 memory game from Milton Bradley.
The game will display a color, and then ask the user to press the button the light came from.
Then the game will show the first and add a second color for the player to input back.  This
continues until the player makes a mistake.

Note: If the button does not light up when you press it (possibly because it was pressed too
fast) the game will not record the input, and this may lead to a failure.
************************************************************************************************/


/*----------------------------------------------------------------------------------------------
This software is built for an Arduino Uno.  It uses the 5V and ground pins.
Pins 2 - 5 are connected to the LEDs.  
Pins 8 - 11 are connected to the buttons, and will close when pressed.
The program set an array of random numbers between 2 and 5, displays them with the corresponding
light, then waits for the user to enter back the same sequence.  Pin 2 links with 8, 3 with 9,
4 with 10, and 5 with 11.  For example, button press 8 will be recorded at led pin 2 (RED) and tested.

The setupLoop() fills the game array with random numbers between 2 and 5.  These numbers correlate
to colors that the player is going to try and guess.
The game is played in loop().  After setup, the program will show the first light in the sequence
using the printLoop() function.  Then the player will press the button that corresponds with the
light.  That data is saved using the inputLoop() function.  The program will then use checkLoop()
to see if the user inputted the pattern correctly.  If they did, the game will iterate another
color in the sequence, and start a new round.  If not, the failState() function is called, the
lights flash, the memory pointer is set to 0, and the game begins again.

setup() is where the pins are defined for the Arduino.

debug() will print major variables and the inputtest and tracker arrays at key steps.  This way
a programer can see what is going on in each step.  
Note:  This code was commented out for efficiency.  Uncomment the code and view the serial monitor
to see the output.
-----------------------------------------------------------------------------------------------*/


// pins: 2,3,4,5
const int ledPin2 = 2;      // LED RED
const int ledPin3 = 3;      // LED YELLOW
const int ledPin4 = 4;      // LED GREEN
const int ledPin5 = 5;      // LED BLUE

// buttonPress: 8,9,10,11
const int buttonPin8 = 8;   //RED
const int buttonPin9 = 9;   //YELLOW
const int buttonPin10 = 10; //GREEN
const int buttonPin11 = 11; //BLUE

int button8State;
int button9State;
int button10State;
int button11State;

// variables
int randNumber = 0;  //sets a random value that will corispond to a color in void setupLoop();
int trackerArraySetup = 0;  //tracks the position when filling in random numbers
int position; // position of the tracker during void setupLoop();
int printing = 0; //print position of void printLoop()
int gameLoop = 0;   //iterate the input loop
int gameTurn = 0; //tracks the game turn in void loop()//iterate the input loop
int sequencePosition = 0; //checks if the user inputed a specific right sequense value in void inputLoop()  
//array position to go through the users input in void inputLoop()
int compaireLoop = 0;  //counter variable for IF statements void checkLoop()
// Note sequencePosition becomes equal to compaireLoop in void checkLoop()
int inputtest[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ; //Initial setup of all 0's, Player sets values every turn here
int tracker[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;  //Initial setup of all 0's, will set random values in setupLoop
int wipeLight;  //failState() counter
int failLight;  //failState() counter

//______________________

void setupLoop();
void printLoop();
void failState();
void inputLoop();
void checkLoop(int sequencePosition);
void inputLoop();
//Reset the inputtest array
void resetUserInput();
void(* resetFunc) (void) = 0;  // function pointer to address 0
void debug();

//________________________________________________________________________________________ 
// Hard coded Arduino function to set up the proper pins, voltage, and serial communication (runs once).
void setup() 
{
Serial.begin(9600);  // Sets up communication between the Arduino and compiler on a COM port
randomSeed(analogRead(0));  // Better randomness that doesn't start at the same point
  // set the digital pin as output:
  pinMode(ledPin2, OUTPUT); // keeps the LED lit up
  pinMode(ledPin3, OUTPUT); // keeps the LED lit up
  pinMode(ledPin4, OUTPUT); // keeps the LED lit up
  pinMode(ledPin5, OUTPUT); // keeps the LED lit up
  pinMode(buttonPin8, INPUT_PULLUP);  // Now your buttons will read HIGH when unpressed, and LOW when pressed. 
  pinMode(buttonPin9, INPUT_PULLUP);  // Now your buttons will read HIGH when unpressed, and LOW when pressed.
  pinMode(buttonPin10, INPUT_PULLUP); // Now your buttons will read HIGH when unpressed, and LOW when pressed.
  pinMode(buttonPin11, INPUT_PULLUP); // Now your buttons will read HIGH when unpressed, and LOW when pressed.
  
}

//________________________________________________________________________________________ 
// Hard coded Arduino function that runs continuously.  This is the main game loop.
void loop() 
{
  Serial.println("S T A R T   O F   G A M E");
  // setting up the random array
  setupLoop();
  gameTurn = 1;
  gameLoop = 1;
  //____________
  while (gameTurn < 21) {
    printLoop();

    inputLoop();
    gameLoop++; //increases the length of each challenge                                                                                                                                                                          

    gameTurn++; //increases the game turn

    resetUserInput();
    sequencePosition = 0; //reset the counter?
    Serial.println("End Of GameTurn____________________________");
  }
  failState();

  Serial.println("E N D   O F   G A M E");
}

//________________________________________________________________________________________    
// This function sets the random pattern Simon will use to test the player.  Only runs once.
void setupLoop() {

  trackerArraySetup = 0;
  position = 0;
  Serial.println("TrackerArraySetup Initial Setup: ");
  while (trackerArraySetup < 20) {
    randNumber = random(2, 6); // generate random number between 2 to 5  (Includes 2, but not 5?)
    tracker[position] = randNumber;

    Serial.print(tracker[position]);
    Serial.print(" ");
    trackerArraySetup++;
    position++;
    //Serial.print("Tracker step:" );
    //Serial.println(trackerArraySetup);
  }
  Serial.println(" ");
  Serial.println("     End of array setup");
  Serial.println(" ");
}

//________________________________________________________________________________________
// This function displays the saved tracker[] array via LED lights
void printLoop() {
  Serial.println("--- STARTING PRINTLOOP ---");
  debug();

  Serial.println(" ");

  printing = 0;

  for (int i = 0; i < gameLoop; i++) {

    Serial.print("INSIDE while printing ");
    Serial.println(printing);
    if (tracker[printing] == 2) {
      digitalWrite(ledPin2, HIGH);
      delay(900);
      Serial.println("TRACKER printLoop RED ledPin2 ButtonPin8 ");
      digitalWrite(ledPin2, LOW);
      delay(200);
    } else if (tracker[printing] == 3) {
      digitalWrite(ledPin3, HIGH);
      delay(900);
      Serial.println("TRACKER printLoop YELLOW ledPin3 ButtonPin9 ");
      digitalWrite(ledPin3, LOW);
      delay(200);
    } else if (tracker[printing] == 4) {
      digitalWrite(ledPin4, HIGH);
      delay(900);
      Serial.println("TRACKER printLoop GREEN ledPin4 ButtonPin10 ");
      digitalWrite(ledPin4, LOW);
      delay(200);
    } else if (tracker[printing] == 5) {
      digitalWrite(ledPin5, HIGH);
      delay(900);
      Serial.println("TRACKER printLoop GREEN ledPin5 ButtonPin11 ");
      digitalWrite(ledPin5, LOW);
      delay(200);
    } else {
      Serial.println("SERIOUS printLoop() ERROR");
      Serial.print("tracker[print] ");
      Serial.println(tracker[printing]);
    }

    debug();
    Serial.println(" ");

    printing++;

  }
  delay(500);

}

//________________________________________________________________________________________ 
// This function takes the players button presses and saves them in inputtest[]
void inputLoop() {
    sequencePosition = 0;
    Serial.println("Waiting for input…");

    // Repeat for each expected press
    //should be gameTrun!!
    while (sequencePosition < gameTurn) {
      Serial.println("First while in inputLoop()");
      Serial.print("sequencePosition ");
      Serial.println(sequencePosition);
      Serial.print("gameLoop ");
      Serial.println(gameLoop);
      // ─── Wait for any button to go LOW ────────────────────────────────
      while (
        digitalRead(buttonPin8) == HIGH &&
        digitalRead(buttonPin9) == HIGH &&
        digitalRead(buttonPin10) == HIGH &&
        digitalRead(buttonPin11) == HIGH
      ) {
        delay(5);
        //Serial.print("Second while");
      }
      Serial.println("Third while");
      // ─── Now sample all four pins ──────────────────────────────────────
      button8State = digitalRead(buttonPin8);
      button9State = digitalRead(buttonPin9);
      button10State = digitalRead(buttonPin10);
      button11State = digitalRead(buttonPin11);
      Serial.println("Forth while");
      // ─── Identify which button was pressed ─────────────────────────────
      if (button8State == LOW) {
        inputtest[sequencePosition] = 2;
        while (digitalRead(buttonPin8) == LOW) {
          digitalWrite(ledPin2, HIGH);
          delay(5);
        }
        digitalWrite(ledPin2, LOW);
      } else if (button9State == LOW) {
        inputtest[sequencePosition] = 3;
        while (digitalRead(buttonPin9) == LOW) {
          digitalWrite(ledPin3, HIGH);
          delay(5);
        }
        digitalWrite(ledPin3, LOW);
      } else if (button10State == LOW) {
        inputtest[sequencePosition] = 4;
        while (digitalRead(buttonPin10) == LOW) {
          digitalWrite(ledPin4, HIGH);
          delay(5);
        }
        digitalWrite(ledPin4, LOW);
      } else if (button11State == LOW) {
        inputtest[sequencePosition] = 5;
        while (digitalRead(buttonPin11) == LOW) {
          digitalWrite(ledPin5, HIGH);
          delay(5);
        }
        digitalWrite(ledPin5, LOW);
      } else {
        // Spurious wake-up: no valid button was pressed
        Serial.println("*** Spurious wake-up: no valid button was pressed ***");
        continue;
      }

      // ─── (Optional) Bounds-check the recorded value ────────────────────
      if (inputtest[sequencePosition] < 2 || inputtest[sequencePosition] > 5) {
        Serial.println("***Input out of range!***");
        failState();
        return;
      }

      // ─── Compare immediately, advance, and loop ───────────────────────

      sequencePosition++;
      //get to print the loop

      Serial.println("*** End of inputLoop() ***");
      debug();

      checkLoop(sequencePosition);

    }
  Serial.println("Input loop complete!                  On to checkLoop()");

}


//________________________________________________________________________________________  
// This function checkes each of the players button presses against the saved tracker[] data
void checkLoop(int sequencePosition) {
  // simple check values loop
  compaireLoop = sequencePosition;
  compaireLoop--;

  Serial.println("+++Starting checkLoop() +++");
  Serial.print("compireLoop Value = ");
  Serial.println(compaireLoop);

  debug();

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
  if (inputtest[compaireLoop] == tracker[compaireLoop]) {
    Serial.println("Color match.  Simon is happy!");
    return; // exits checkLoop()
  }

  //not equal
  else if (inputtest[compaireLoop] != tracker[compaireLoop]) {
    Serial.println("Wrong button pressed! /checkLoop");
    Serial.print("inputtest: ");
    Serial.println(inputtest[compaireLoop]);
    Serial.print("tracker:  ");
    Serial.println(tracker[compaireLoop]);
    Serial.println(" ");
    Serial.print("compireLoop Value = ");
    Serial.println(compaireLoop);
    failState();
  } else {
    Serial.println("CheckLoop() Error problem,  Somehow passed both IFs");
  }
  //inputtest[]
  //tracker[] 
  //Serial.println("IF statement error");
}


//________________________________________________________________________________________  
//Reset the inputtest array
void resetUserInput() {
  for (int i = 0; i < 20; i++) {
    inputtest[i] = 0;
  }
}


//________________________________________________________________________________________  
// This function flashes the lights to let the player know they have lost
void failState() {
  failLight = 0;

  while (failLight < 3) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
    digitalWrite(ledPin5, HIGH);
    delay(300);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin5, LOW);
    delay(200);

    failLight++;
  }

  wipeLight = 0;
  while (wipeLight < 3) {
    digitalWrite(ledPin2, HIGH);
    delay(100);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, HIGH);
    delay(100);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, HIGH);
    delay(100);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, HIGH);
    delay(100);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin5, HIGH);
    delay(100);
    digitalWrite(ledPin5, LOW);

    wipeLight++;
  }
  //Restart Arduino from mem spot 0
  resetFunc();
}
//________________________________________________________________________________________ 
// Uncomment code to enable debug and see variable and arraystates
void debug() {

  /*
    Serial.print("tracker Array:   ");            
    int asdf = 0;
    while (asdf < 20){
                Serial.print(tracker[asdf]);
                Serial.print(" ");
      asdf++;
    }
    Serial.println(" ");
    asdf = 0;
    Serial.print("inputtest Array: ");
    while (asdf < 20){
                Serial.print(inputtest[asdf]);
                Serial.print(" ");
      asdf++;
    }
    Serial.println(" ");
    Serial.print("sequencePosition = ");
    Serial.println(sequencePosition );
    Serial.print("printLoop print = ");
    Serial.println(printing);
    Serial.print("printLoop gameLoop = ");
    Serial.println(gameLoop);
    Serial.print("printLoop gameTurn = ");
    Serial.println(gameTurn);
  */
  return;
}