/*     Arduino Rotary Encoder Tutorial

    by Dejan Nedelkovski, www.HowToMechatronics.com

*/
#include <JC_Button.h>          // https://github.com/JChristensen/JC_Button
#define outputA 0
#define outputB 5
const int buttonPin = 11;     // the number of the pushbutton pin
float counter = 0.;
int aState;
int aLastState;
int direction;
const byte
BUTTON_PIN(11);           // connect a button switch from this pin to ground

Button myBtn(BUTTON_PIN);       // define the button

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  myBtn.begin();
  Serial.begin (9600);
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);
}
void loop() {
  //reset();

  aState = digitalRead(outputA); // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  //Serial.println(aState);
  if (aState != aLastState) {
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    //Serial.println("aState != aLastState");
    if (digitalRead(outputB) != aState) {
      counter = counter + 0.1;
      direction = 1;
    } else {
      counter = counter - 0.1;
      direction = 0;
    }
    //Serial.print("Position: ");
    //Serial.print("degree: ");
    Serial.print(counter);
    //Serial.print("direction: ");
    Serial.print("  ");
    Serial.println(direction);
  }
  aLastState = aState; // Updates the previous state of the outputA with the current state
  //delay(20);
  myBtn.read();               // read the button
    if (myBtn.wasReleased())    // if the button was released, change the LED state
    {
  
      //digitalWrite(LED_PIN, ledState);
      Serial.println("reset");
  
    }


}

//
//void reset () {
//  buttonState = digitalRead(buttonPin);
//  if (buttonState == 1) {
//    counter = 0;
//    Serial2.println("baseline reset");
//  }
//
//}

