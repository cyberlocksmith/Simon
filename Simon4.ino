/*
Simon on the Arduino
by Tristan Clawson
rev: 0.40
red date:  5/26/2025
 */


//pins: 2,3,4,5
int ledPin2 = 2;    // LED connected to digital pin 2
int ledPin3 = 3;    // LED connected to digital pin 3
int ledPin4 = 4;    // LED connected to digital pin 4
int ledPin5 = 5;    // LED connected to digital pin 5

//buttonPress: 8,9,10,11
const int buttonPin8 = 8;
const int buttonPin9 = 9;
const int buttonPin10 = 10;
const int buttonPin11 = 11;

int randNumber = 0;
int trackerArraySetup = 0;
int i;  //iteration of the game loop
int x;  //iteration of the display loop
int k;  //rotation of the display loop
int n; //reset loop
int m; //input loop
int gameturn = 0; //iterate the input loop
int buttonPress = 0; //input for the buttons
int test = 0;
int var = 0;
int light = 0;
int gameloop = 0;
int inputtest[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;
int tracker[] = {} ;  //0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

int ledState = LOW;  

void printLoop();

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


// setting up the random array

   Serial.println("Start of array setup"); 

  while (trackerArraySetup < 21 ){
  randNumber = random(2,6); // generate random number between 2 to 5  (Includes 2, but not 5?)
  tracker[i] = randNumber;   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< has to be an array problem  only doing 1 number?
   Serial.println(tracker[i]); 
   trackerArraySetup ++;
  }
 
 Serial.println("End of array setup"); 

}

//Don't use letter variables
//Print statements after every iteration

void loop() //can do 20 rounds here
{


  Serial.println("Add a Random value"); 

//________________________________________________________________________________________ 
      
      printLoop();
//________________________________________________________________________________________                                                                                                                                                                                           
                                                                                                    
      i++;  //a little iteration, if you please
      x = 0; //<< upper error
      k = 0;
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

                                       */
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
void printLoop(){
  while (x < 20){
      //use if instead?          
                                      Serial.println("In the Lights While Loop");
                                      Serial.println("The value of tracker[k] " );  Serial.println(tracker[k]);
                                      

                  
                  light = tracker[k];  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< has to be an array problem  copy variable and ++ it   B A D
                    if (light < 2)
                  {//do nothing
                    Serial.println("-------blank1-------");
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




