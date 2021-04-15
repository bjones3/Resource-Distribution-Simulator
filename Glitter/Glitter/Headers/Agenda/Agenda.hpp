#ifndef AGENDA_HPP
#define AGENDA_HPP

# include "../rds.hpp"

class Agenda
{
	public:
		Agenda(Individual* individual);
		Agenda(std::list<Event> events, Individual* individual);
		void 					executeEvent(std::list<Resource*> resources);
		bool 					canExecuteEvent(std::list<Resource*> & foundResources, std::list<int> & typesNeeded);
		bool					inBuilding();
		void 					addEvent(Event event);
		void 					addEvents(std::list<Event> events);
		void 					removeEvent(Event event);
		std::list<Event> 		getEvents();
		Individual*				getIndividual();

	private:
		std::list<Event> 		m_events;
		Individual* 			m_individual;
};

#endif
