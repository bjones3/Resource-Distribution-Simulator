#include "../../inc/rds.hpp"

Event::Event(Building building, Individual individual)
{
  m_building = building;
  m_individual = individual;
}
Event::Event(Building building, Individual individual, std::list<int> resources)
{
  m_building = building;
  m_individual = individual;
  m_resources = resources;
}
void Event::execute()
{

  //m_individual.doTask(m_resources);

}
bool Event::canExecuteEvent()
{

	//Make sure the individual is in the building
  /*if(!m_building.getOccupants().contains(m_individual))
  {
    return false;
  }*/

  std::list<int>::iterator iter = m_resources.begin();

  while(iter!=m_resources.end())
  {
    std::list<int>:: iterator iter2;
	/*
    iter2 = std::find(m_building.getContents().begin(), m_building.getContents().end(), *iter);
    if(iter2 == m_building.getContents().end())
    {
      return false;
    }*/
    iter++;
  }
  return true;
}
