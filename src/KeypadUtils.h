#ifndef _JUDGECOMP_H
#define _JUDGECOMP_H

#include <Arduino.h>
#include <Keypad.h>

#define CORRECTION_KEY '*'
#define VALIDATE_KEY '#'

char getKeyBlocking(Keypad keypad);
int getNumberBlocking(Keypad keypad);


#endif
