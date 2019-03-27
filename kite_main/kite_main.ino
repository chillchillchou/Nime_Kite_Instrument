
#include <JC_Button.h>          // https://github.com/JChristensen/JC_Button
#include <Keyboard.h>

#define outputA 14
#define outputB 15
int aState;
int aLastState;
//const int buttonPin = 10;     // the number of the pushbutton pin
int counter = 0.;

int direction;


const byte
BUTTON_PIN1(12),              // connect a button switch from this pin to ground
            BUTTON_PIN2(11),              // connect a button switch from this pin to ground
            BUTTON_PIN3(9),              // connect a button switch from this pin to ground
            BUTTON_PIN4(16);             // connect a button switch from this pin to ground


Button myBtn1(BUTTON_PIN1);       // define the button
Button myBtn2(BUTTON_PIN2);       // define the button
Button myBtn3(BUTTON_PIN3);       // define the button
Button myBtn4(BUTTON_PIN4);       // define the button

void setup() {
  myBtn1.begin();              // initialize the button object
  myBtn2.begin();
  myBtn3.begin();
  myBtn4.begin();
  pinMode (outputA, INPUT);
  pinMode (outputB, INPUT);

  Serial.begin (9600);
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);
}

void buttonRead () {
  myBtn1.read();               // read the button
  myBtn2.read();
  myBtn3.read();
  myBtn4.read();
  if (myBtn1.wasReleased())    // if the button was released, change the LED state
  {

    Keyboard.press(KEY_A);
    delay(1);
    Keyboard.release(KEY_A);
    Serial.println("Button1 pressed");
  }

  if (myBtn2.wasReleased())    // if the button was released, change the LED state
  {

    Serial.println("Button2 pressed");
    Keyboard.press(KEY_S);
    delay(1);
    Keyboard.release(KEY_S);
  }
  if (myBtn3.wasReleased())    // if the button was released, change the LED state
  {


    Serial.println("Button3 pressed");
    Keyboard.press(KEY_D);
    delay(1);
    Keyboard.release(KEY_D);
  }
  if (myBtn4.wasReleased())    // if the button was released, change the LED state
  {

    Serial.println("Button4 pressed");
    counter = 0;

  }
}

void loop() {
  buttonRead();

  aState = digitalRead(outputA); // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  if (aState != aLastState) {
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(outputB) != aState) {
      counter = counter + 1;
      direction = 1;
    } else {
      counter = counter - 1;
      direction = 0;
    }
    //Serial.print("Position: ");
    //Serial.print("degree: ");
    if (counter % 2 == 0) {
      Serial.print(counter);
      //Serial.print("direction: ");
      Serial.print("  ");
      Serial.println(direction);
    }
  }
  aLastState = aState; // Upsaqqdates the previous state of the outputA with the current state
  //delay(5);

}


//




