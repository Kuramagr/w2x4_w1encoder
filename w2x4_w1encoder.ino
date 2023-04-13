/* the code is for a Arduino pro micro controller
    handwired keyboard with every switch assing to a pin of the controller.
    if you have some corrections please send a feedback
    
    This is a working version of the micropad for davinci resolve shortcuts.
    the button of the encoder has been added to the array of buttons like case 8
    
    If you need to replace the shortcuts remember if you write with capital letters will aslo press SHIFT
    
    I hope it helps a little bit to start for your macropad
*/

#include <Bounce2.h>
#include <Keyboard.h>
#include <Encoder.h>

// Define pins for the encoder
const int dtPin = 3;
const int swPin = 2;

//Set up the button grid
const int numButtons = 9;
const int buttonPins[numButtons] = {5,6,7,8,9,10,16,14,4}; //Array of button pins in an order that makes sense to me
int state = 0;

//Set up all the buttons as bounce objects
Bounce buttons[] = {Bounce(buttonPins[0],10),Bounce(buttonPins[1],10),Bounce(buttonPins[2],10),Bounce(buttonPins[3],10),Bounce(buttonPins[4],10),Bounce(buttonPins[5],10),Bounce(buttonPins[6],10),Bounce(buttonPins[7],10), Bounce(buttonPins[8],10)};


void setup() {
  Serial.begin(9600);
  Keyboard.begin(); //Start the Keyboard object
  for(int i = 0; i < numButtons; i++){
     pinMode(buttonPins[i], INPUT_PULLUP);
  
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
                Keyboard.press('m');
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
              Keyboard.press('k');
                delay(100);
                Keyboard.releaseAll();
               break;
              case 3:
                Keyboard.press(KEY_RIGHT_SHIFT);
                Keyboard.press('l');
                delay(100);
                Keyboard.releaseAll();
                break;
              case 4: 
              Keyboard.press(KEY_RIGHT_GUI);
                Keyboard.press('v');
                delay(100);
                Keyboard.releaseAll();
                break;
              case 5:
              Keyboard.press(KEY_RIGHT_GUI);
                Keyboard.press('c');
                delay(100);
                Keyboard.releaseAll();
                break;
              case 6: 
                Keyboard.press('o');
                delay(100);
                Keyboard.releaseAll();
                break;
              case 7:
                Keyboard.press('i');
                delay(100);
                Keyboard.releaseAll();
                break;
              case 8:
                Keyboard.press('b');
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

 // If the encoder is turned to the right, press the 'l' key
  if (encoder1Value > 0) {
    Keyboard.press(KEY_LEFT_ARROW);
    delay(50);
    Keyboard.release('l');
    encoder1.write(0);
  }
  // If the encoder is turned to the left, press the 'j' key
  else if (encoder1Value < 0) {
    Keyboard.press('KEY_RIGHT_ARROW');
    delay(50);
    Keyboard.release('j');
    encoder1.write(0);
  }
}
