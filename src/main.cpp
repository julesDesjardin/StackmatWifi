#include <Arduino.h>
#include <Keypad.h>

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

char getKeyBlocking()
{
  while(1)
  {
    char key = keypad.getKey();
    if(key)
      return key;
  }
}
int getNumberBlocking()
{
  int ret = 0;

  char key = 0;
  while(key != '#')
  {
    key = getKeyBlocking();
    if(key >= '0' && key <= '9') // if key is a number
    {
      ret*=10;
      ret+=key-'0';
    }
    else if(key == '*') // correction
      ret/=10;
    Serial.printf("Key : %c\n",key);
    Serial.println(ret);
  }
  return ret;
}

int getTime()
{
  int ret;
  ret += (nextChar()-'0')*6000;
  ret += (nextChar()-'0')*1000;
  ret += (nextChar()-'0')*100;
  ret += (nextChar()-'0')*10;
  ret += (nextChar()-'0');
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
  int judge = getNumberBlocking();

  Serial.println("Waiting for competitor number");
  int comp = getNumberBlocking();

  Serial.println("Ready ! Please solve");

  while(!stopped)
  {
    if(Serial2.available())
    {
      int ch = Serial2.read();
      if(ch == 0x0D)
      {
        char next = nextChar();
        if(next == 'S' && !stopped)
        {
          stopped = true;
          timeStack = getTime();
        }
        else if(next == 'I')
        {
          stopped = false;
        }
      }
    }
  }

  Serial.printf("Done. Judge : %d, Comp : %d, Time : %d\n",judge,comp,timeStack);

}
