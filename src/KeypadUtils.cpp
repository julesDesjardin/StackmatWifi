#include "KeypadUtils.h"

int getNumberBlocking(Keypad keypad)
{
  int ret = 0;

  char key = 0;
  while(key != '#' || ret == 0)
  {
    key = keypad.getKey();
    if(key >= '0' && key <= '9') // if key is a number
    {
      ret*=10;
      ret+=key-'0';
      Serial.println(ret);
    }
    else if(key == '*') // correction
      ret/=10;
  }
  return ret;
}
