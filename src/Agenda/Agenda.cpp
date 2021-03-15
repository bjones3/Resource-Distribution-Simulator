#include "../../inc/rds.hpp"

Agenda::Agenda(Individual individual)
{

  m_individual = individual;

}

Agenda::Agenda(std::list<Event> events, Individual individual)
{
    m_events = events;
    m_individual = individual;
}

void Agenda::executeEvent()
{

  m_events.front().execute();

  m_events.pop_front();

}

bool Agenda::canExecuteEvent()
{

  return m_events.front().canExecuteEvent();

}

void Agenda::addEvent(Event event)
{
  m_events.push_back(event);
}
void Agenda::addEvents(std::list<Event> events)
{
  for(int i = 0; i < events.size(); i++)
  {

    m_events.push_back(events.front());
    events.pop_front();

  }
}

void Agenda::removeEvent(Event event)
{

  //std::list<Event>::iterator findEvent = std::find(list.begin(), list.end(), event);
  //m_events.remove(findEvent);

}
