/******************************************************************************
  Title          : subway_routes.h
  Author         : Stewart Weiss
  Created on     : April 18, 2018
  Description    : Interface file for the SubwayRoute object
  Purpose        : Encapsulates data and methods of a set of subway routes
  Usage          :
  Build with     :
  Modifications  :

******************************************************************************/

#ifndef __SUBWAY_ROUTE_H__
#define __SUBWAY_ROUTE_H__

#include <list>
#include <string.h>
#include <string>

using namespace std;

typedef long route_set;
typedef string route_id;

#define NUM_ROUTES_MAX 64
#define BAD_ROUTE_ID 63

/*******************************************************************************
 *                    Functions related to subway routes                        *
 ******************************************************************************/

// function to check if string contains numbers 1 - 7
bool is_valid_num(string s);

/** is_route_id() validates whether a string is a valid route name
 *  Strings are valid route ids if they are one of the digits 1,...,7 or a
 *  letter A,B,...,Z designating a route, or FS or GS.
 *  @param string [in] s: a string that might be a route
 *  @return true iff s is a valid route name
 */
bool is_route_id(string s);

/** str_from_routeset() returns a string representing a set of routes
 *  @param long int [in] a long int encoding a set of routes
 *  @return string : a string representation suitable for writing to a stream
 */
string str_from_routeset(route_set s);

/** routestring2int() returns a small int unique to the route s
 *  @param string [in] s: a string denoting a route
 *  @return int  in the range [0,63] such that no other route has this value
 */
int routestring2int(string s);

/** int2route_id() is the inverse of routestring2int
 *  @param int [in] k: int in [0,63]
 *  @return string, the unique route associated with this integer k
 */
string int2route_id(int k);

using namespace std;

/*******************************************************************************
 *                           SubwayRoute Class                                  *
 ******************************************************************************/

class SubwayRoute {
  public:

  SubwayRoute();

	/** station_list() returns a list of station index values for all stations
	 *  that access the route, if that list has been formed. If it has not been
	 *  formed yet, then it returns an empty list.
	 *  @pre  This should only be called after all station entries have been
	 *        read and processed.
	 */
	list<int> station_list() const;

	/** add_station_to_route() appends the given station index value to the list of
	 *  stations for this route.
	 */
	void add_station_to_route(int station_id);

	/** get_routeset() returns the bitmask representing this route */
	route_set get_routeset() const;

	/** The SubwaySystem class should have easier access to this class to
	 *  reduce function call overhead.
	 */
	friend class SubwaySystem;

  private:
	route_set routes;   // bit string for this route
	list<int> stations; // list of indices of stations on this route,
};

#endif /* __SUBWAY_ROUTE_H__ */
