#include <Arduino.h>
#include <Keypad.h>
#include "KeypadUtils.h"
#include "Person.h"

HardwareSerial Serial2(2);

bool stopped = false;
char nextChar()
{
  while(!Serial2.available());
  return Serial2.read();
}


const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {18,5,4,15}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {23,22,21,19}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



int getTime()
{
  int ret;
  ret += (nextChar()-'0')*6000;
  Serial.println(ret);
  ret += (nextChar()-'0')*1000;
  Serial.println(ret);
  ret += (nextChar()-'0')*100;
  Serial.println(ret);
  ret += (nextChar()-'0')*10;
  Serial.println(ret);
  ret += (nextChar()-'0');
  Serial.println(ret);
  return ret;
}
void setup() {

  Serial.begin(115200);

  // Serial2.begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert)
  Serial2.begin(1200, SERIAL_8N1, 26, 25, true);
}

void loop() {
  int timeStack = 0;
  Serial.println("Waiting for judge number");
  Person judge(getNumberBlocking(keypad));

  Serial.println("Waiting for competitor number");
  Person comp(getNumberBlocking(keypad));

  Serial.println("Ready ! Please solve");

  stopped = false;
  Serial2.flush();
  while(!stopped)
  {
    Serial.println("Running");
    if(Serial2.available())
    {
      int ch = Serial2.read();
      if(ch == 0x0D)
      {
        char next = nextChar();
        if(next == 'S' && !stopped)
        {
          Serial.println("Stopped");
          stopped = true;
          timeStack = getTime();
        }
      }
    }
  }

  Serial.printf("Done. Judge : %d, Comp : %d, Time : %d\n",judge.getId(),comp.getId(),timeStack);

}
