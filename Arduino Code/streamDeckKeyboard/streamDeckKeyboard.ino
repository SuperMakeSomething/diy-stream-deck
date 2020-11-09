/* DIY Stream Deck Keyboard Code (DIY Stream Deck - Super Make Something Episode 22)
 * by: Alex - Super Make Something
 * date: November 8th, 2020
 * license: Creative Commons - Attribution - Non-Commercial.  More information available at: http://creativecommons.org/licenses/by-nc/3.0/
 */

#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Keyboard.h>
#include <Encoder.h>

Encoder upDown(10,15);
Encoder leftRight(14,16);

char buttonArray1[] = {'a','b','c','d','e','s','g','h','i'}; //Array to save button presses
char buttonArray2[] = {'j','k','l','m','n','o','p','q','r'}; // Add additional arrays for more pages

int pageFlag = 1; // Flag for button pages

const int buttonPin2 = 2;
const int buttonPin3 = 3;
const int buttonPin4 = 4;
const int buttonPin5 = 5;
const int buttonPin6 = 6;
const int buttonPin7 = 7;
const int buttonPin8 = 8;
const int buttonPin9 = 9;

int pressedPin2 = HIGH;
int pressedPin3 = HIGH;
int pressedPin4 = HIGH;
int pressedPin5 = HIGH;
int pressedPin6 = HIGH;
int pressedPin7 = HIGH;
int pressedPin8 = HIGH; //Encoder Button 1 
int pressedPin9 = HIGH; //Encoder Button 2

int lastState2 = HIGH;
int lastState3 = HIGH;
int lastState4 = HIGH;
int lastState5 = HIGH;
int lastState6 = HIGH;
int lastState7 = HIGH;
int lastState8 = HIGH;
int lastState9 = HIGH;

unsigned long lastDebounceTime2 = 0; // Last time the button was pressed
unsigned long lastDebounceTime3 = 0;
unsigned long lastDebounceTime4 = 0;
unsigned long lastDebounceTime5 = 0;
unsigned long lastDebounceTime6 = 0;
unsigned long lastDebounceTime7 = 0;
unsigned long lastDebounceTime8 = 0;
unsigned long lastDebounceTime9 = 0;

long posUpDown = 0; //Position counter for up/down encoder
long posLeftRight = 0; //Position counter for left/right encoder
long posUpDownPrev = 0; //Previous position of up/down encoder
long posLeftRightPrev = 0; //Previous position of left/right encoder

int counterUpDown = 0;
int counterLeftRight = 0;

void setup() 
{
  Serial.print("Initializing Pins...");
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(buttonPin7, INPUT_PULLUP);
  pinMode(buttonPin8, INPUT_PULLUP);
  pinMode(buttonPin9, INPUT_PULLUP);
  
  Serial.println(" Done!");

  Serial.print("Initializing Keyboard...");
  Keyboard.begin();
  Serial.println(" Done!");

  delay(50);

  digitalWrite(A0, LOW);
  
  Serial.println("Setup Complete!");
}

void loop() 
{
  
  pressedPin2 = digitalRead(2);
  pressedPin3 = digitalRead(3);
  pressedPin4 = digitalRead(4);
  pressedPin5 = digitalRead(5);
  pressedPin6 = digitalRead(6);
  pressedPin7 = digitalRead(7);
  pressedPin8 = digitalRead(8);
  pressedPin9 = digitalRead(9);

 // BUTTONS
 if (pressedPin2 != lastState2)
  {
    if (pressedPin2 == LOW)
    {
      switch (pageFlag) //Depending on pageFlag, send different keystroke
      {
        case 1:
          Keyboard.press(buttonArray1[0]); // Send keystroke
          break;
        default:
          Keyboard.press(buttonArray2[0]);
          break;
      }
    }
  }

  if (pressedPin3 != lastState3) // Button 3 assigned to page select
  {
    if (pressedPin3 == LOW)
    {
      if (pageFlag == 1)
      {
        pageFlag = 2;
        digitalWrite(A0, HIGH);
      }
      else if (pageFlag == 2)
      {
        pageFlag = 1;
        digitalWrite(A0, LOW);
      }
    }
  }
  Serial.print("Page Flag: ");
  Serial.println(pageFlag);

  if (pressedPin4 != lastState4)
  {
    if (pressedPin4 == LOW)
    {
      switch (pageFlag) //Depending on pageFlag, send different keystroke
      {
        case 1:
          Keyboard.press(buttonArray1[2]); // Send keystroke
          break;
        default:
          Keyboard.press(buttonArray2[2]);
          break;
      }
    }
  }

  if (pressedPin5 != lastState5)
  {
    if (pressedPin5 == LOW)
    {
      switch (pageFlag) //Depending on pageFlag, send different keystroke
      {
        case 1:
          Keyboard.press(buttonArray1[3]); // Send keystroke
          break;
        default:
          Keyboard.press(buttonArray2[3]);
          break;
      }
    }
  }

  if (pressedPin6 != lastState6)
  {
    if (pressedPin6 == LOW)
    {
      switch (pageFlag) //Depending on pageFlag, send different keystroke
      {
        case 1:
          Keyboard.press(buttonArray1[4]); // Send keystroke
          break;
        default:
          Keyboard.press(buttonArray2[4]);
          break;
      }
    }
  }

  if (pressedPin7 != lastState7)
  {
    if (pressedPin7 == LOW)
    {
      switch (pageFlag) //Depending on pageFlag, send different keystroke
      {
        case 1:
          Keyboard.press(buttonArray1[5]); // Send keystroke
          break;
        default:
          Keyboard.press(buttonArray2[5]);
          break;
      }
    }
  }

  if (pressedPin8 != lastState8)
  {
    if (pressedPin8 == LOW)
    {
      switch (pageFlag) //Depending on pageFlag, send different keystroke
      {
        case 1:
          Keyboard.press(buttonArray1[6]); // Send keystroke
          break;
        default:
          Keyboard.press(buttonArray2[6]);
          break;
      }
    }
  }

  if (pressedPin9 != lastState9)
  {
    if (pressedPin9 == LOW)
    {
      switch (pageFlag) //Depending on pageFlag, send different keystroke
      {
        case 1:
          Keyboard.press(buttonArray1[7]); // Send keystroke
          break;
        default:
          Keyboard.press(buttonArray2[7]);
          break;
      } 
    }
  }

  // ENCODERS
  posUpDown = upDown.read(); //Up/down encoder
  if (posUpDown!=posUpDownPrev) //If new position doesn't equal previous position
  {
    if ((posUpDown-posUpDownPrev)>0)
    {
      counterUpDown = counterUpDown+1;
      if (counterUpDown>3) // 3 counts per physical encoder "click"
      {
        Keyboard.press(KEY_UP_ARROW);
        counterUpDown = 0;
        Keyboard.releaseAll();
      }
    }
    else if ((posUpDown-posUpDownPrev)<0)
    {
      counterUpDown = counterUpDown-1;
      if (counterUpDown<-3)
      {
        Keyboard.press(KEY_DOWN_ARROW);
        counterUpDown = 0;
        Keyboard.releaseAll();
      }
    }
  }
  Keyboard.releaseAll();
  posUpDownPrev = posUpDown;
  //Serial.println(counterUpDown);

  posLeftRight = leftRight.read(); // Left/right encoder
  if (posLeftRight!=posLeftRightPrev) //If new position doesn't equal previous position
  {
    if ((posLeftRight-posLeftRightPrev)>0)
    {
      counterLeftRight = counterLeftRight+1;
      if (counterLeftRight>3) // 3 counts per physical encoder "click"
      {
        Keyboard.press(KEY_RIGHT_ARROW);
        counterLeftRight = 0;
        Keyboard.releaseAll();
      }
    }
    else if ((posLeftRight-posLeftRightPrev)<0)
    {
      counterLeftRight = counterLeftRight-1;
      if (counterLeftRight<-3)
      {
        Keyboard.press(KEY_LEFT_ARROW);
        counterLeftRight = 0;
        Keyboard.releaseAll();
      }
    }
  }
  Keyboard.releaseAll();
  posLeftRightPrev = posLeftRight;
  Serial.println(counterLeftRight);


  // BUTTON STATE MANAGEMENT
  lastState2 = pressedPin2; // Save the latest reading
  lastState3 = pressedPin3;
  lastState4 = pressedPin4;
  lastState5 = pressedPin5;
  lastState6 = pressedPin6;
  lastState7 = pressedPin7;
  lastState8 = pressedPin8;
  lastState9 = pressedPin9;
  
  Keyboard.releaseAll(); // Release all pressed keys
}
