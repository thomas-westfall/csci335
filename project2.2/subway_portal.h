/******************************************************************************
  Title          : subway_portal.h
  Author         : Thomas Westfall
  Created on     : May 1, 2019
  Description    : SubwayPortal header
  Purpose        : 
  Usage          :
  Build with     : C++11
  Modifications  :
******************************************************************************/

#ifndef SUBWAY_PORTAL_H
#define SUBWAY_PORTAL_H

#include "gps.h"
#include "subway_route.h"
//#include "subway_station.h"
#include <string>
#include <vector>

using namespace std;

struct Invalid_Portal_Data {};

//class SubwayStation;
class SubwayPortal{
  public:
	//default constructor
	SubwayPortal(); 

	//parameterized constructor
	SubwayPortal(string data_row);

	//copy constructor
        SubwayPortal(SubwayPortal const& sp);
	//copy operator
	void operator=(SubwayPortal const& sp);
	//move operator
	void operator=(SubwayPortal&& sp);
	
	/** returns the distance between station and a gps location  */
	double distance_from(double latitude, double longitude);

	/** returns the distance between the two portals  */
	friend double distance_between(SubwayPortal portal1, SubwayPortal portal2);

	/** returns true if the two portals have the exact same set of routes  */
	friend bool same_routes(SubwayPortal portal1, SubwayPortal portal2);

	/** returns true if the two portals belong to the same station */
	friend bool same_station(SubwayPortal portal1, SubwayPortal portal2);

	friend ostream& operator<<(ostream& out, SubwayPortal e);

	friend class SubwayStation;

	/*  Accessor  Functions */
	/**  name() returns name of portal as a unique string
	 */
	string name() const;

	string sname() const;
	/** can_access() returns true if given route is accessible
	 *  @param route_set [in]  a bitstring with a 1 bit for route
	 *  @return bool  true iff route is accessible from this portal
	 */
	bool can_access(route_set route) const;

	/**  p_location() returns GPS location of portal  */
	GPS p_location() const;

	/**  s_location() returns GPS location of portal's station */
	GPS s_location() const;

	/**  routes() returns route set of portal */
	route_set routes() const;

  private:
	//takes a string s, the string version of
	//a row of data. stores each data value
	//as a string element in a vector
	//will be assigned to the following 
	//variables
	vector<string> constructvector(string s);


	string portalname;
	string division;
	string line;
	string stationname;
	double stationlat;
	double stationlong;

	//data[5-15]
	route_set portalroutes;

	string entrancetype;
	bool entry;
	bool exitonly;
	bool vending;
	string staff;
	string staffhrs;
	bool ada;
	string adanotes;
	bool freecross;

	// fields necessary for naming
	string northsouthst;
	string eastwestst;
	string corner;
	int id;

	double entrancelat; 
	double entrancelong;
	GPS stationloc;
	GPS entranceloc;
};

#endif /* SUBWAY_PORTAL_H */
