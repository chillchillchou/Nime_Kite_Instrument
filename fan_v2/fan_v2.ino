/***********************************************************************************


   AC LINE FREQUENCY - 60HZ 

   Variables for dimming - buf_CH1, buf_CH2, buf_CH3, buf_CH4 !

   Variables have range 0-255. 0 - Fully ON, 255 - Fully OFF.

 ***********************************************************************************/


#include <TimerOne.h>

int buton1 = 4;                 // first button at pin 5
int buton2 = 5;                 // second button at pin 6
int buton3 = 6;
int buton4 = 7;
const byte interruptPin = 3;

#define channel_3 9
#define channel_4 10


#define SPEED 50

#define GATE_IMPULSE 5

#define FREQ 84

unsigned int  CH1, CH2, CH3, CH4;
unsigned int  buf_CH1, buf_CH2, buf_CH3, buf_CH4;
unsigned char clock_cn;
unsigned int  clock_tick;
unsigned char i;
int throttle ;
int throttle2;

void setup() {

  pinMode(channel_3, OUTPUT);
  pinMode(channel_4, OUTPUT);
  //  pinMode(channel_3, OUTPUT);
  //  pinMode(channel_4, OUTPUT);
  attachInterrupt(1, zero_crosss_int, RISING);
  Timer1.initialize(10);
  Timer1.attachInterrupt( timerIsr );
  Serial.begin(9600);
}

void timerIsr()
{
  clock_tick++;

  if (clock_cn)
  {
    clock_cn++;

    if (clock_cn == GATE_IMPULSE)
    {
      digitalWrite(channel_3, LOW);
      digitalWrite(channel_4, LOW);
      //      digitalWrite(channel_3, LOW);
      //      digitalWrite(channel_4, LOW);
      clock_cn = 0;
    }
  }

  if (CH3 == clock_tick)
  {
    digitalWrite(channel_3, HIGH);
    clock_cn = 1;
  }

  if (CH4 == clock_tick)
  {
    digitalWrite(channel_4, HIGH);
    clock_cn = 1;
  }
  //
  //  if (CH3 == clock_tick)
  //  {
  //    digitalWrite(channel_3, HIGH);
  //    clock_cn = 1;
  //  }
  //
  //  if (CH4 == clock_tick)
  //  {
  //    digitalWrite(channel_4, HIGH);
  //    clock_cn = 1;
  //  }


}



void zero_crosss_int()
{
  CH1 = buf_CH1;
  CH2 = buf_CH2;
  CH3 = buf_CH3;
  CH4 = buf_CH4;

  clock_tick = 0;
}

unsigned int DIMM_VALUE (unsigned char level)
{
  unsigned int buf_level;

  if (level < 26)  {
    level = 26;
  }
  if (level > 229) {
    level = 229;
  }

  return ((level * (FREQ)) / 256) * 10;
}



void loop() {
  //fan1
  String button_1 = String(digitalRead(buton1));
  String button_2 = String(digitalRead(buton2));


  String input = button_1 + button_2;

  int accleration = ceil(throttle * 0.01) + 1;
  if (input == "00" || input == "11" ) {
  }


  else if (input == "10" && throttle <= 255) {
    throttle += accleration;
    buf_CH3 = DIMM_VALUE(throttle);
    if (throttle >= 255) {
      throttle = 254;
    }
    delay(throttle);
  }


  else if (input == "01" && throttle >= 0) {
    throttle -= accleration;
    buf_CH3 = DIMM_VALUE(throttle);
    if (throttle < 5) {
      throttle = 5;
    }
    delay(throttle);
  }
//  Serial.print("Fan 1: ");
  Serial.print(throttle);
  Serial.print(" ");


  //fan 2

  String button_3 = String(digitalRead(buton3));
  String button_4 = String(digitalRead(buton4));

  String input2 = button_3 + button_4;

  int accleration2 = ceil(throttle2 * 0.01) + 1;
  if (input2 == "00" || input2 == "11" ) {
  }


  else if (input2 == "10" && throttle2 <= 255) {
    throttle2 += accleration2;
    buf_CH4 = DIMM_VALUE(throttle2);
    if (throttle2 >= 255) {
      throttle2 = 254;         ;
    }
    delay(throttle2);
  }


  else if (input2 == "01" && throttle2 >= 0) {
    throttle2 -= accleration2;
    buf_CH4 = DIMM_VALUE(throttle2);
    if (throttle2 < 5) {
      throttle2 = 5;
    }
    delay(throttle2);
  }
//  Serial.print("Fan 2: ");
  Serial.println(throttle2);
//  Serial.print('\n');
}




