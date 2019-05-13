/******************************************************************************
  Title          : gps.cpp
  Author         : Thomas Westfall
  Created on     : April 8, 2019
  Description    : Implementation of GPS
  Purpose        :
  Usage          :
  Build with     :
********************************************************************************/

#include "gps.h"
GPS::GPS(){
  longitude = 0.0;
  latitude = 0.0;
}

GPS::GPS(double lon, double lat) throw (BadPoint){
	//check if latitude is valid
	if (!(lat > -90 and lat < 90))
		throw(BadPoint());
	//check if longitude is valid
	if (!(lon > -180 and lon < 180))
		throw(BadPoint());
    //both are valid, GPS can be constructed
	latitude = lat;
	longitude = lon;
}

GPS::GPS(const GPS& location) {
	//check if latitude is valid
	if (!(location.latitude > -90 and location.latitude < 90))
		throw BadPoint();
	//check if longitude is valid
	if (!(location.longitude > -180 and location.longitude < 180))
		throw BadPoint();
	//both are valid, GPS can be constructed
	latitude = location.latitude;
	longitude = location.longitude;
}

void GPS::operator=(const GPS& location) {
	longitude = location.longitude;
	latitude = location.latitude;
}

//Use project1's implementation of the Haversine formula
// to calculate distance between two GPS points
//Written by Stewart Weiss
const double R = 6372.8;
const double TO_RAD = M_PI / 180.0;
double distance_between(GPS point1, GPS point2) {
	//avoid modifying point1 and point2
	double p1lat = point1.latitude;
	double p1long = point1.longitude;
	double p2lat = point2.latitude;
	double p2long = point2.longitude;

	p1lat = TO_RAD * p1lat;
	p2lat = TO_RAD * p2lat;
	p1long = TO_RAD * p1long;
	p2long = TO_RAD * p2long;
	double dLat = (p2lat - p1lat) / 2;
	double dLon = (p2long - p1long) / 2;
	double a = sin(dLat);
	double b = sin(dLon);

    return 2 * R * asin(sqrt(a*a + cos(p1lat) * cos(p2lat) * b * b));
}

ostream& operator<<(ostream& out, GPS point) {
	out << "POINT(" << point.latitude << " " << point.longitude << ")" << endl;
	return out;
}
