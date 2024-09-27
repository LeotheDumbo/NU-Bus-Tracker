/*building.cpp*/

//
// A building in the Open Street Map.
// 
// Leo Zhang
// Northwestern University
// CS 211
// 

#include <iostream>
#include <utility>

#include "building.h"
#include "busstop.h"
#include "busstops.h"

using namespace std;


//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr)
{
  //
  // the proper technique is to use member initialization list above,
  // in the same order as the data members are declared:
  //
  //this->ID = id;
  //this->Name = name;
  //this->StreetAddress = streetAddr;

  // vector is default initialized by its constructor
}

//
// print
// 
// prints information about a building --- id, name, etc. -- to
// the console. Also prints out the closest bus stops to the building
// in the south and northbound direction, as well as the predicitions
// for when the bus arrives, if any. Nodes, BusStops, and Curl is passed for 
// searching and accessing.
//
void Building::print(Nodes& nodes, BusStops& b, CURL* curl)
{
  cout << this->Name << endl;
  cout << "Address: " << this->StreetAddress << endl;
  cout << "Building ID: " << this->ID << endl;
  cout << "# perimeter nodes: " << this->NodeIDs.size() << endl;
  cout << "Location: (" << getLocation(nodes).first << ", " << getLocation(nodes).second << ")" << endl;
  cout << "Closest southbound bus stop:" << endl;
  BusStop south = b.getClosest(getLocation(nodes).first, getLocation(nodes).second, "Southbound");
  cout << "  " << south.getID() << ": " << south.getName() << ", bus #" << south.getRoute() << ", " << south.getLocation() << ", " << south.getDis(getLocation(nodes).first, getLocation(nodes).second) << " miles" << endl;
  south.printBusPredictions(curl);
  cout << "Closest northbound bus stop:" << endl;
  BusStop north = b.getClosest(getLocation(nodes).first, getLocation(nodes).second, "Northbound");
  cout << "  " << north.getID() << ": " << north.getName() << ", bus #" << north.getRoute() << ", " << north.getLocation() << ", " << north.getDis(getLocation(nodes).first, getLocation(nodes).second) << " miles" << endl;
  north.printBusPredictions(curl);
}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}

//
// gets the center (lat, lon) of the building based
// on the nodes that form the perimeter
//
pair<double, double> Building::getLocation(const Nodes& nodes) {
  double avgLat = 0;
  double avgLon = 0;
  int size = 0;

  for (long long nodeid : this->NodeIDs)
  {
    double lat = 0.0;
    double lon = 0.0;
    bool entrance = false;

    bool found = nodes.find(nodeid, lat, lon, entrance);

    if (found) {
      avgLat += lat;
      avgLon += lon;
      size ++;
    }
  }

  avgLat = avgLat / size;
  avgLon = avgLon / size;

  return make_pair(avgLat, avgLon);
}
