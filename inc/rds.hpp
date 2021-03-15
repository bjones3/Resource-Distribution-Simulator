#ifndef RDS_HPP
# define RDS_HPP

# include <list>
# include <queue>
# include <unordered_map>
# include <vector>
# include <string>
# include <algorithm>

class Executive;
class ID;
class Location;
class MainAI;

class Building;
class FulfillmentCenter;
class House;
class Office;

class Resource;
class ResourceTable;

class cityMap;

class Drone;
class CargoDrone;
class PassengerDrone;

class Individual;

class Agenda;
class Event;

# include "Building/Building.hpp"
# include "Building/FulfillmentCenter.hpp"
# include "Building/House.hpp"
# include "Building/Office.hpp"

# include "Drone/Drone.hpp"
# include "Drone/CargoDrone.hpp"
# include "Drone/PassengerDrone.hpp"

# include "Individual/Individual.hpp"

# include "Map/Map.hpp"

# include "Resource/Resource.hpp"

# include "Agenda/Agenda.hpp"
# include "Agenda/Event.hpp"

# include "Executive.hpp"
# include "ID.hpp"
# include "Location.hpp"
# include "MainAI.hpp"

#endif
