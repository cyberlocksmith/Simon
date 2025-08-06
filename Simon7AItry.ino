/*
Simon on the Arduino
by Tristan Clawson
rev: 0.70
red date:  7/6/2025
 */


//pins: 2,3,4,5
int ledPin2 = 2;    // LED connected to digital pin 2
int ledPin3 = 3;    // LED connected to digital pin 3
int ledPin4 = 4;    // LED connected to digital pin 4
int ledPin5 = 5;    // LED connected to digital pin 5

//buttonPress: 8,9,10,11
const int buttonPin8 = 8; //RED
const int buttonPin9 = 9;
const int buttonPin10 = 10;
const int buttonPin11 = 11;

int randNumber = 0;
int trackerArraySetup = 0;
//int i;  //iteration of the game loop
int position; // position of the tracker
int x;  //iteration of the display loop
int k;  //rotation of the display loop
int n; //reset loop
int m; //input loop
int gameTurn = 0; //iterate the input loop
int buttonPress = 0; //input for the buttons
int test = 0;
int var = 0;
int light = 0;
int gameloop = 0;
int compaireLoop = 0;  //checkLoop counter variable for IF statements
int inputtest[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;
int tracker[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;  //Initial setup of all 0's, will set random values in setupLoop

int ledState = LOW;  

//AI______________________
// Debounce parameters
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
  pinMode(buttonPin8, INPUT);
  pinMode(buttonPin9, INPUT);
  pinMode(buttonPin10, INPUT);
  pinMode(buttonPin11, INPUT);   
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

//gameLoop
// while bool is true?  when to check,  else fail
gameloop = 0;
for (gameloop < 21; gameloop ++;){
printLoop();                                                                                                                                                                             
inputLoop();
checkLoop();
//counting
      position ++;  //a little iteration, if you please
//      x = 0; //<< upper error
//      k = 0;
}
failState();
//restart put in failstate,  or breakout / break
          m++; 

                             
Serial.println("E N D   O F   L O O P");                             
} 

//________________________________________________________________________________________   
//________________________________________________________________________________________   
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
    Serial.print("Tracker step:" );
    Serial.println(trackerArraySetup);
  }
   Serial.println("     End of array setup"); 
   Serial.println(" ");
}


//________________________________________________________________________________________   

void printLoop(){
// Display loop
x = 0;
k = 0;

  while (x < 20){
      //use if instead?          
                                      Serial.println("In the Lights While Loop");
                                      Serial.print("The value of tracker[k] " );  
                                      Serial.println(tracker[k]);
                                      

                  
                  light = tracker[k];  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< has to be an array problem  copy variable and ++ it   B A D
                    if (light < 2)
                  {//do nothing
                    Serial.println("--------------LOWER Bounds ERROR--------------");
                  }
                    if (light == 2)
                  {
                   //ledPin2
                    digitalWrite (ledPin2, HIGH);
                    //sound
                    delay (1000);
                    digitalWrite (ledPin2, LOW);
                    Serial.println("Pin2!");
                    delay (200);
                  }
                   if (light == 3)
                  {
                   //ledPin2
                    digitalWrite (ledPin3, HIGH);
                    //sound
                    delay (1000);
                    digitalWrite (ledPin3, LOW);
                    Serial.println("Pin3!");
                    delay (200);
                  }
                   if (light == 4)
                  {
                   //ledPin2
                    digitalWrite (ledPin4, HIGH);
                    //sound
                    delay (1000);
                    digitalWrite (ledPin4, LOW);
                    Serial.println("Pin4!");    
                    delay (200);                
                  }
                    if (light == 5)
                  {
                   //ledPin2
                    digitalWrite (ledPin5, HIGH);
                    //sound
                    delay (1000);
                    digitalWrite (ledPin5, LOW);
                    Serial.println("Pin5!"); 
                    delay (200);                   
                  }                  
                    else if (light > 5)
                      {Serial.println("--------------Upper Bounds ERROR--------------");
                      Serial.println(tracker[k]);
                  }

                  x++;
                  k++;
                                                                                                                   }
  }






//________________________________________________________________________________________                                                                                                                                                                                           

void inputLoop(){

//AI code in

//inputtest[]
//millis is inbuilt function?
 unsigned long now = millis();

  for (int i = 0; i < numButtons; i++) {
    int raw = digitalRead(buttonPins[i]);

    // 1) If the raw reading changed, reset its debounce timer
    if (raw != lastReadState[i]) {
      lastDebounceTime[i] = now;
    }

    // 2) If it's been stable longer than debounceDelay, treat it as real
    if (now - lastDebounceTime[i] > debounceDelay) {
      if (raw != stableState[i]) {
        stableState[i] = raw;

        // 3) On HIGH→LOW transition, log event and blink LED
        if (stableState[i] == LOW && pressCount < maxPresses) {
          pressEvents[pressCount++] = i;
          Serial.print("Button index ");
          Serial.print(i);
          Serial.print(" logged at event #");
          Serial.println(pressCount - 1);

          // Blink the LED for 100 ms
          digitalWrite(ledPins[i], HIGH);
          delay(100);
          digitalWrite(ledPins[i], LOW);
        }
      }
    }

    // 4) Save raw state for next loop
    lastReadState[i] = raw;

//Need to call check loop to test

  }


}


//________________________________________________________________________________________  


void checkLoop(){
// simple check values loop

Serial.println("Starting the array checking process");

//First 2 tests see if the numbers are out of bounds.
if (inputtest[compaireLoop] > 5 || inputtest[compaireLoop] < 1 ){
Serial.println("Error.  Something has gone seriously wrong with checking the arrays!");
failState();
}

//First 2 tests see if the numbers are out of bounds.
if (tracker[compaireLoop] > 5 || tracker[compaireLoop] < 1 ){
Serial.println("Error.  Something has gone seriously wrong with checking the arrays!");
failState();
}

//equal
if (inputtest[compaireLoop] == tracker[compaireLoop] ){
Serial.println("Color match.  Simon is happy!");
return;
}

//not equal
if (inputtest[compaireLoop] =! tracker[compaireLoop] ){
Serial.println("Wrong button pressed! /checkLoop");
Serial.print(inputtest[compaireLoop] );
Serial.print(tracker[compaireLoop]);
failState();
}

//inputtest[]
//tracker[] 
Serial.println("IF statement error");
}


//inputtest[]
//tracker[] 


//________________________________________________________________________________________  
// This function flashes the lights to let the player know they have lost
// Will add game restart functionality in later
void failState(){
failLight = 0;

while (failLight < 5){
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
  while (whipeLight < 5){
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


}















 /*          
Serial.println("I broke out of the show loop");
delay(1000); // wait 1 second before displaying the next number


        //.................................................................
        gameloop = 0;
        while ( gameloop < 20){ 
          Serial.println("I'm in the INPUT loop");
          //Serial.println(m);
          
                    //  while (tracker[m] != 0) //need a for loop to reset the array
                             // {
                                  gameturn = i;
                                  
                                  
                                  Serial.println("I'm DOING the INPUT ARRAY loop I'm DOING the INPUT ARRAY loop I'm DOING the INPUT ARRAY loop");
                                  int button8State = digitalRead(buttonPin8);
                                  int button9State = digitalRead(buttonPin9);
                                  int button10State = digitalRead(buttonPin10);
                                  int button11State = digitalRead(buttonPin11);
                                  //Serial.println(button8State);

                                  
                                 // Serial.println(buttonPin8 == HIGH);
                             
//change back from LOW to HIGH
while (button8State == LOW && button9State == LOW && button10State == LOW && button11State == LOW  ) {Serial.println("Holding and waiting for input.Holding and waiting for input."); } //HOLD
                                  /*
                                  while (gameturn > 1  )  // i = x, for gameturn values
                                        {
                                          //Serial.println("while input -------");
                                          //button input
                                          //duration = pulseIn(buttonPin10, HIGH);
                                          //duration = pulseIn(buttonPin11, HIGH);
                      
                                          if (buttonPin8 == HIGH)
                                          {
                                            inputtest[i] = 2;
                                                digitalWrite(ledPin2, HIGH);
                                                delay (100); 
                                                digitalWrite(ledPin2, LOW);
                                            }
                                          if (buttonPin9 == HIGH)
                                          {
                                            inputtest[i] = 3;
                                                digitalWrite(ledPin3, HIGH);
                                                delay (100); 
                                                digitalWrite(ledPin3, LOW);                      
                                            }
                                           if (buttonPin11 == HIGH)
                                          {
                                            inputtest[i] = 4;
                                                digitalWrite(ledPin4, HIGH);
                                                delay (100); 
                                                digitalWrite(ledPin4, LOW);                      
                                            }
                                           if (buttonPin9 == HIGH)
                                          {
                                            inputtest[i] = 5;
                                                digitalWrite(ledPin5, HIGH);
                                                delay (100); 
                                                digitalWrite(ledPin5, LOW);                      
                                            }
                      
                                                         if (buttonPin10 > 13 ) //NOPE
                                                        {
                                                          Serial.println("Input UPPER bounds error");
                                                          }  
                                                        if (buttonPin11 < 10 ) //NOPE
                                                        {
                                                          Serial.println("Input LOWER bounds error");
                                                          }  
                      
                                          //button press
                                          // if input value A = array[i] continue (pause for input) +beep
                                          if  (  buttonPress = tracker[i] )
                                          {
                                            //break out? 
                                            //goto win;//crap;
                                            }
                                          // else fail + beep 
                                           else ( buttonPress != tracker[i] );
                                          {
                                            //goto fail;//FAIL;
                                            }
                                          gameturn--;
                                        }

                                       
                                        m++; 
                               // }
                             gameloop ++;
                               
               }          
         //.................................................................


/*
                                                          while (tracker[i] != 0) //no?  Get input and check
                                                                {
                                                                    i = input;
                                                                    
                                                                    while (input >1 , input--)  // i = x, for input values
                                                                          {
                                                                            
                                                                            //button press
                                                                            // if input value A = array[i] continue (pause for input) +beep
                                                                            if  (  buttonPress = tracker[i] )
                                                                            {
                                                                              //break out? 
                                                                              goto win;//crap;
                                                                              }
                                                                            // else fail + beep 
                                                                             else ( buttonPress != tracker[i] )
                                                                            {
                                                                              goto fail//FAIL;
                                                                              }
                                                                            
                                                                          }
                                                                 }
                                                                
win: //
fail://

for (int r = 0, r < 20, r++){

}


*/

//end of game loop
 
//reset everything
 //
                                         //for (int n = 0, n < 20, n++){
                                         //int tracker[n] = 0;
                                         //}
//reseting
//}


//________________________________________________________________________________________                                                                                                                                                                                           
// k= 0?

