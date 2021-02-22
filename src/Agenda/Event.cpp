#include "../../inc/rds.hpp"

Event::Event(Building building, Individual individual)
{
  m_building = building;
}
Event::Event(Building building, Individual individual, std::list<Resources> resources)
{
  m_building = building;
  m_individual = individual;
  m_resources = resources;
}
void execute()
{

  m_individual.doTask(m_resources);

}
bool canExecuteEvent()
{

  if(!building.occupants().contains(individual))
  {
    return false;
  }

  std::list<Resource>::iterator iter = m_resouces.begin();

  while(iter!=m_resources.end())
  {
    std::list<Resource>:: iterator iter2;
    iter2 = std::find(m_building.getContents().begin(), m_building.getContents().end(), *iter);
    if(iter2 == m_building.getContents().end())
    {
      return false;
    }
    iter++;
  }
  return true;
}
