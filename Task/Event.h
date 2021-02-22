#include <list>

#ifndef EVENT_H
#define EVENT_H

class Event
{

private:

  long long int ID;

  std::list resouces;

public:

  Event(std::list resources);

  const long long int getID() const;

  void executeEvent();
};

#endif
