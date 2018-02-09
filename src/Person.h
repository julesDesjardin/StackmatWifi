#ifndef _PERSON_H
#define _PERSON_H

#include <Arduino.h>

#define NAME_SIZE 20

class Person
{
private:
  int _id;
  char _name[NAME_SIZE];

  void fetchName(); // TODO Fetch name from database
public:
  Person();
  Person(int id);
  int getId();
  char* getName();
};

#endif
