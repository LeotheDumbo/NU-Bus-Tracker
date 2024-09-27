/*busstop.cpp*/

//
// A bus stop in the Open Street Map.
// 
// Leo Zhang
// Northwestern University
// CS 211
// 

#include <iostream>
#include <utility>

#include "busstop.h"
#include "curl_util.h"
#include "dist.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;


//
// constructor
//
BusStop::BusStop(long long stopid, int busRoute, string stopName, string direction, string location, double latitude, double longitude)
  : StopID(stopid), BusRoute(busRoute), StopName(stopName), Direction(direction), Location(location), Latitude(latitude), Longitude(longitude)
{
}

//
// print
// 
// prints information about a bus stop
//
void BusStop::print() const
{
  cout << this->StopID << ": bus " << this->BusRoute << ", " << this->StopName
       << ", " << this->Direction << ", " << this->Location << ", location (" << Latitude << ", " << Longitude << ")" << endl;
}

//
// printBusPredictions
// 
// prints information about how long it will take for a bus to arrive at a bus stop
//
void BusStop::printBusPredictions(CURL* curl) const 
{
  string url = "https://ctabustracker.com/bustime/api/v2/getpredictions?key=DEvKa2fAhdFBibx54TjRJRHpp&rt=" + to_string(this->BusRoute) + "&stpid=" + to_string(this->StopID) + "&format=json";
  string output;
  bool success = callWebServer(curl, url, output);
  if (!success) {
    cout << "  <<bus predicitons unavailable, call failed>>" << endl;
    return;
  }
  auto jsondata = json::parse(output);
  auto bus_reponse = jsondata["bustime-response"];
  auto predictions = bus_reponse["prd"];
  
  if (predictions.empty()){
    cout << "  <<no predictions available>>" << endl;
  }
  for (auto& M: predictions) {
    try {
      cout << "  vehicle #" << stoi(M["vid"].get_ref<std::string&>()) << " on route " << stoi(M["rt"].get_ref<std::string&>()) << " travelling " << M["rtdir"].get_ref<std::string&>() << " to arrive in " << stoi(M["prdctdn"].get_ref<std::string&>()) << " mins" << endl;
    }
    catch (exception& e) {
      cout << "  error" << endl;
      cout << "  malformed CTA response, prediction unavailable" << " (error: " << e.what() << ")" << endl;
    }
  }
}

//
// accessors / getters
//
long long BusStop::getID() const
{
  return this->StopID;
}

int BusStop::getRoute() const
{
  return this->BusRoute;
}

string BusStop::getName() const
{
  return this->StopName;
}

string BusStop::getLocation() const
{
  return this->Location;
}

double BusStop::getLat() const
{
  return this->Latitude;
}

double BusStop::getLon() const
{
  return this->Longitude;
}

string BusStop::getDir() const
{
  return this->Direction;
}

double BusStop::getDis(double lat, double lon) const
{
  return distBetween2Points(this->Latitude, this->Longitude, lat, lon); 
}