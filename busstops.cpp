/*busstops.cpp*/

//
// A collection of bus stops in the Open Street Map.
// 
// Leo Zhang
// Northwestern University
// CS 211
// 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>

#include "busstops.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;


//
// readMapBusStops
//
// Given an XML document, reads through the document and 
// stores all the bus stops into the given vector.
//
void BusStops::readMapBusStops(string filename)
{
  ifstream input;
  input.open(filename);
  if (!input.is_open()) {
    cout << "Error" << endl;
    return;
  }

  //
  // loops and parses through each line, taking the necessary inputs and values, 
  // and stores it into the vector
  //
  while (!input.eof()) {
    string line;
    getline(input, line);
    
    if (input.fail()) {
        break;
    }
    
    stringstream parser(line);  // setup to parse the line
    
    string stopid, busRoute, stopName, direction, location, latitude, longitude;
    
    getline(parser, stopid, ',');
    getline(parser, busRoute, ',');
    getline(parser, stopName, ',');
    getline(parser, direction, ',');
    getline(parser, location, ',');
    getline(parser, latitude, ',');
    getline(parser, longitude);
    
    BusStop b(stoll(stopid), stoi(busRoute), stopName, direction, location, stod(latitude), stod(longitude));
    this->MapBusStops.push_back(b);
  }
   
}

//
// print
//
// prints each building (id, name, address) to the console.
//
void BusStops::print()
{
  for (const BusStop& B : this->MapBusStops) {
    B.print();
  }
}


//
// findAndPrint
//
// Prints each building that contains the given name.
//
void BusStops::findAndPrint(string name)
{
  bool found = false;

  for (BusStop& B : this->MapBusStops)
  {
    if (B.StopName.find(name) != string::npos) { // contains name:
      B.print();
      found = true;
    }
  }

  if (!found)
    cout << "No such bus stop" << endl;
}

//
// accessors / getters
//
int BusStops::getNumMapBusStops() {
  return (int) this->MapBusStops.size();
}

BusStop BusStops::getClosest(double lat, double lon, string direction) { 
  BusStop A = this->MapBusStops[0];
  
  //
  // finds first BusStop with given direction
  //
  for (BusStop b : this->MapBusStops) {
    if (b.getDir() == direction) {
      A = b;
      break;
    } 
  }  
  BusStop B = A;
  //
  // finds closest BusStop in given direction
  //
  for (BusStop b : this->MapBusStops) {
    if (b.getDir() == direction) {
      if (b.getDis(lat, lon) < B.getDis(lat, lon)) {
        B = b;
      } 
    }   
  }
  return B;
}