#ifndef EVENT_HPP
#define EVENT_HPP

# include "../rds.hpp"

class Event
{
public:
  Event(Building building, Individual individual);
  Event(Building building, Individual individual, std::list<int> resources);

  void execute();
  bool canExecuteEvent();
private:
  std::list<int> m_resources;
  Building m_building;
  Individual m_individual;
};

#endif
