#include <list>

#ifndef AGENDA_H
#define AGENDA_H

class Agenda
{

  public:
    Agenda();

    bool completeEvent();

    void addNewEvents(std::list<Event> newEvents);

    list<Event> getListOfEvents();

    const long long int getID() const;

  private:
    std::list<Event> listOfEvents;
    long long int ID;

};
#endif
