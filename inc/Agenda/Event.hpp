



#ifndef EVENT_HPP
#define EVENT_HPP

class Event()
{
public:
  Event(Building building);
  Event(Building building, std::list<Resources> resources);

  void execute();
  bool canExecuteEvent();
private:
  std::list<Resources> m_resources;
  Building m_building;
};

#endif
