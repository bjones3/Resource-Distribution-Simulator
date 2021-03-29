#include "../../inc/rds.hpp"

Event::Event(Building* building, Individual* individual)
{
	m_building = building;
	m_individual = individual;
}
Event::Event(Building* building, Individual* individual, std::list<int> resources)
{
	m_building = building;
	m_individual = individual;
	m_resources = resources;
}
void Event::execute(std::list<Resource*> resources)
{

	m_individual->doTask(resources);

}
bool Event::canExecuteEvent(std::list<Resource*> & foundResources, std::list<int> & typesNeeded)
{
	//Make sure the needed resources are in this building
  	std::list<int>::iterator typeIter;
  	for(typeIter = m_resources.begin(); typeIter != m_resources.end(); typeIter++)
  	{
  		bool pushed = false;
    	std::unordered_map<long long int, Resource*> theContents = m_building->getContents();
		for(const auto & [ theID, theResource ] : theContents)
		{
			//If the type of the resource matches
			if(theResource->getType() == (*typeIter))
			{
				int alreadyFound = false;
				
				//And this specific resources has not already been added
				for(std::list<Resource*>::iterator foundIter = foundResources.begin(); foundIter != foundResources.end(); foundIter++)
				{
					if(theID == (*foundIter)->getID())
					{
						alreadyFound = true;
						//std::cout << "duplicate detected\n";
						break;
					}
				}
				
				//Add this resource to the found list
				if(!alreadyFound)
				{
					foundResources.push_back(theResource);
					pushed = true;
					//std::cout << "found match\n";
					break;
				}
			}
		}
		
		//If this type needs to be requested
		if(!pushed)
		{
			typesNeeded.push_back(*typeIter);
		}
  	}
  	
  	//If not all resources were found
	if(!typesNeeded.empty())
	{
		std::cout << "Types needed: \n";
		for(std::list<int>::iterator it = typesNeeded.begin(); it != typesNeeded.end(); it++)
			std::cout << " " << *it << std::endl;
	  	return false;
	}
  	return true;
}

Building* Event::getBuilding()
{
	return m_building;
}

Individual* Event::getIndividual()
{
	return m_individual;
}


