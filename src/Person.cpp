#include "Person.h"

void Person::fetchName()
{
  // TODO : fetch name from database
}
Person::Person()
{

}

Person::Person(int id)
{
  _id = id;
  fetchName();
  memcpy(_name,"toto",strlen("toto")+1);
}

int Person::getId()
{
  return _id;
}

char* Person::getName()
{
  return _name;
}
