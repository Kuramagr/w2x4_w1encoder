#include <Bounce2.h>
#include <Keyboard.h>
#include <Encoder.h>


//Set up the button grid
const int numButtons = 8;
const int buttonPins[numButtons] = {5,6,7,8,9,10,11,12}; //Array of button pins in an order that makes sense to me
int state = 0;
//Set up all the buttons as bounce objects
Bounce buttons[] = {Bounce(buttonPins[0],10),Bounce(buttonPins[1],10),Bounce(buttonPins[2],10),Bounce(buttonPins[3],10),Bounce(buttonPins[4],10),Bounce(buttonPins[5],10),Bounce(buttonPins[6],10),Bounce(buttonPins[7],10),Bounce(buttonPins[8],10),Bounce(buttonPins[9],10),Bounce(buttonPins[10],10),Bounce(buttonPins[11],10)};

// Define pins for the encoder
const int clkPin = 2;
const int dtPin = 3;
const int swPin = 4;

// Initialize variables
volatile int encoderPos = 0;
volatile boolean buttonState = LOW;
volatile boolean lastButtonState = LOW;

void setup() {
  Serial.begin(9600);
  Keyboard.begin(); //Start the Keyboard object
  for(int i = 0; i < numButtons; i++){
     pinMode(buttonPins[i], INPUT_PULLUP);
  }
  // Set pin modes
  pinMode(clkPin, INPUT_PULLUP);
  pinMode(dtPin, INPUT_PULLUP);
  pinMode(swPin, INPUT_PULLUP);
  
  // Attach interrupt to the CLK pin
  attachInterrupt(digitalPinToInterrupt(clkPin), updateEncoder, CHANGE);
  
  // Set initial state of button
  lastButtonState = digitalRead(swPin);
  
  // Start the serial communication
  Serial.begin(9600);
}

void loop() {
  //check all buttons
  for(int j = 0; j < numButtons; j++){
    if(buttons[j].update()){
      if(buttons[j].fallingEdge()){
        //Serial.write("Button");
       

        //use the current state and the button number to find the command needed and send it.
        switch (state) {
          case 0: //Layout 1
            switch (j) {
              case 0: 
                Keyboard.press('M');
                delay(100);
                Keyboard.releaseAll();
                break;
              case 1: 
              Keyboard.press(KEY_RIGHT_SHIFT);
                Keyboard.press('J');
                delay(100);
                Keyboard.releaseAll();
                break;
              case 2: 
              Keyboard.press('K');
                delay(100);
                Keyboard.releaseAll();
               break;
              case 3:
                Keyboard.press(KEY_RIGHT_SHIFT);
                Keyboard.press('L');
                delay(100);
                Keyboard.releaseAll();
                break;
              case 4: 
              Keyboard.press(KEY_RIGHT_GUI);
                Keyboard.press('V');
                delay(100);
                Keyboard.releaseAll();
                break;
              case 5:
              Keyboard.press(KEY_RIGHT_GUI);
                Keyboard.press('C');
                delay(100);
                Keyboard.releaseAll();
                break;
              case 6: 
                Keyboard.press('O');
                delay(100);
                Keyboard.releaseAll();
                break;
              case 7:
                Keyboard.press('I');
                delay(100);
                Keyboard.releaseAll();
                break;
              case 8:
              Keyboard.press(KEY_RIGHT_GUI);
                Keyboard.press('E');
                delay(100);
                Keyboard.releaseAll();
                break;
              case 9:
              Keyboard.press(KEY_RIGHT_GUI);
                Keyboard.press('A');
                delay(100);
                Keyboard.releaseAll();
                break;
              case 10:
              Keyboard.press(KEY_RIGHT_ALT);
                Keyboard.press('S');
                delay(100);
                Keyboard.releaseAll();
                break;
              case 11:
              Keyboard.press(KEY_RIGHT_GUI);
                Keyboard.press('X');
                delay(100);
                Keyboard.releaseAll();
                break;
             }
            break;

    }
  }
  // Check if button state has changed
  buttonState = digitalRead(swPin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      Serial.write('k');
    }
    lastButtonState = buttonState;
  }
  
  // Check if encoder position has changed
  if (encoderPos < 0) {
    Serial.write('j');
    encoderPos = 0;
  }
  else if (encoderPos > 0) {
    Serial.write('l');
    encoderPos = 0;
  }
}

void updateEncoder() {
  // Read the state of the CLK pin
  int clkState = digitalRead(clkPin);
  
  // Read the state of the DT pin
  int dtState = digitalRead(dtPin);
  
  // Determine direction of rotation
  if (clkState != dtState) {
    encoderPos++;
  } else {
    encoderPos--;
  }
  
  // Add delay to rotation
  delay(50);
}
