/*building.h*/

//
// A building in the Open Street Map.
// 
// Leo Zhang
// Northwestern University
// CS 211
// 

#pragma once

#include <string>
#include <vector>

#include "busstops.h"
#include "curl_util.h"
#include "node.h"
#include "nodes.h"

using namespace std;


//
// Building
//
// Defines a campus building with a name (e.g. "Mudd"), a street
// address (e.g. "2233 Tech Dr"), and the IDs of the nodes that
// define the position / outline of the building.
// 
// NOTE: the Name could be empty "", the HouseNumber could be
// empty, and the Street could be empty. Imperfect data.
//
class Building
{
public:
  long long ID;
  string Name;
  string StreetAddress;
  vector<long long> NodeIDs;

  //
  // constructor
  //
  Building(long long id, string name, string streetAddr);

  //
  // print
  // 
  // prints information about a building --- id, name, etc. -- to
  // the console. Also prints out the closest bus stops to the building
  // in the south and northbound direction, as well as the predicitions
  // for when the bus arrives, if any. Nodes, BusStops, and Curl is passed for 
  // searching and accessing.
  //
  void print(Nodes& nodes, BusStops& b, CURL* curl);

  
  // adds the given nodeid to the end of the vector.
  //
  void add(long long nodeid);

  //
  // gets the center (lat, lon) of the building based
  // on the nodes that form the perimeter
  //
  pair<double, double> getLocation(const Nodes& nodes);

};
