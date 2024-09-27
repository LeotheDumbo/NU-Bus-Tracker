/*busstop.h*/

//
// A BusStop in the Open Street Map.
// 
// Leo Zhang
// Northwestern University
// CS 211
// 

#pragma once

#include <string>
#include <vector>

#include "curl_util.h"

using namespace std;


//
// BusStop
//
// Defines a campus bus stop with a stop ID, the bous route,
// stop name, direction of travel, the location of the stop,
// and the position in lat and lon of the bus stop.
// 
class BusStop
{
public:
  long long StopID;
  int BusRoute;
  string StopName;
  string Direction;
  string Location;
  double Latitude;
  double Longitude;


  //
  // constructor
  //
  BusStop(long long stopid, int busRoute, string stopName, string direction, string location, double latitude, double longitude);

  //
  // print
  // 
  // prints information about a bus stop
  //
  void print() const;

  //
  // printBusPredictions
  // 
  // prints information about how long it will take for a bus to arrive at a bus stop
  //
  void printBusPredictions(CURL* curl) const;

  //
  // accessors / getters
  //
  long long getID() const;

  int getRoute() const;

  string getName() const;

  string getLocation() const;
  
  double getLat() const;

  double getLon() const;

  string getDir() const;

  double getDis(double lat, double lon) const;
  //
  // gets the position (lat, lon) of a bus stop
  //
  // pair<double, double> getLocation();

};