/*busstops.h*/

//
// A collection of bus stops in the Open Street Map.
// 
// Leo Zhang
// Northwestern University
// CS 211
// 

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "busstop.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;


//
// Keeps track of all the bus stops in the map.
//
class BusStops
{
public:
  vector<BusStop> MapBusStops;

  //
  // readMapBusStops
  //
  // Given an XML document, reads through the document and 
  // stores all the bus stops into the given vector.
  //
  void readMapBusStops(string filename);

  //
  // print
  //
  // prints each building (id, name, address) to the console.
  //
  void print();

  //
  // findAndPrint
  //
  // Prints each building that contains the given name.
  //
  void findAndPrint(string name);

  //
  // accessors / getters
  //
  int getNumMapBusStops();
  
  BusStop getClosest(double lat, double lon, string direction);

};


