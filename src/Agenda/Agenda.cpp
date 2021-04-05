#include "../../inc/rds.hpp"

Agenda::Agenda(Individual* individual)
{
	m_individual = individual;
	m_individual->setAgenda(this);
}

Agenda::Agenda(std::list<Event> events, Individual* individual)
{
    m_events = events;
    m_individual = individual;
}

void Agenda::executeEvent(std::list<Resource*> resources)
{
	m_events.front().execute(resources);
	m_events.pop_front();
}

bool Agenda::canExecuteEvent(std::list<Resource*> & foundResources, std::list<int> & typesNeeded)
{
	return m_events.front().canExecuteEvent(foundResources, typesNeeded);
}

bool Agenda::inBuilding()
{
	Event theEvent = m_events.front();
	return theEvent.getBuilding()->occupantExists(theEvent.getIndividual()->getID());
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
	m_events.pop_front();
}

std::list<Event> Agenda::getEvents()
{
	return m_events;
}

Individual* Agenda::getIndividual()
{
	return m_individual;
}

