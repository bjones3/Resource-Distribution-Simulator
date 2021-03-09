#ifndef AGENDA_HPP
#define AGENDA_HPP

# include "../rds.hpp"

class Agenda
{
public:
  Agenda(Individual individual);
  Agenda(std::list<Event> events, Individual individual);
  void executeEvent();
  bool canExecuteEvent();
  void addEvent(Event event);
  void addEvents(std::list<Event> events);
  void removeEvent(Event event);

private:
  std::list<Event> m_events;
  Individual m_individual;
};

#endif
