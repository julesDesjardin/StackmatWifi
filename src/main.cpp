#include <Arduino.h>

HardwareSerial Serial2(2);

bool stopped = false;
char nextChar()
{
  while(!Serial2.available());
  return Serial2.read();
}
void setup() {

  Serial.begin(115200);

  // Serial2.begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert)
  Serial2.begin(1200, SERIAL_8N1, 26, 25, true);
}

void loop() {

  if(Serial2.available()) {
    int ch = Serial2.read();
    if(ch == 0x0D)
    {
      if(nextChar() == 'S' && !stopped)
      {
        stopped = true;
        Serial.printf("%c:%c%c.%c%c%c\n",nextChar(),nextChar(),nextChar(),nextChar(),nextChar(),nextChar());
      }
      else if(nextChar() == 'I')
      {
        stopped = false;
      }
    }
  }
}
