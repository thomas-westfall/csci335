/******************************************************************************
  Title          : subway_portal.cpp
  Author         : Thomas Westfall
  Created on     : May 1, 2019
  Description    : SubwayPortal implementation
  Purpose        :
  Usage          :
  Build with     : C++11
  Modifications  :
******************************************************************************/

#include "subway_portal.h"

//helper functions
//string trimspaces(string s)
//pre: None
//post: Theres a maximum of 1 space between nonspace characters
string trimspaces(string s) {
	string ans = "";
	bool firstspace = true;

	for (unsigned int i = 0; i < s.size(); i++) {
		if (s[i] == ' ' and firstspace) {
			ans = ans + ' ';
			firstspace = false;
			continue;
		}
		if(s[i] == ' ' and !(firstspace))
			continue;
		else{
			ans = ans + s[i];
			firstspace = true;
		}
	}

	return ans;
}

//default constructor
SubwayPortal::SubwayPortal(){
    portalname = "";
    division = "";
    line = "";
    stationname = "";
    stationlat = 0.0;
    stationlong = 0.0;
    portalroutes = 0;
    entrancetype = "";
    entry = false;
    exitonly = false;
    vending = false;
    staff = "";
    staffhrs = "";
    ada = false;
    adanotes =  "";
    freecross = false;
    northsouthst = "";
    eastwestst = "";
    corner = "";
    id = 1;
    entrancelat = 0.0;
    entrancelong = 0.0;
    stationloc = {0,0};
    entranceloc = {0,0};
}

//parameterized constructor
SubwayPortal::SubwayPortal(string s) {
	//parse the row into a vector
	vector<string> row = constructvector(s);

	//assign correct vector element to corresponding variable
	division = row[0];
	line = row[1];
	stationname = row[2];
	stationlat = stod(row[3]);
	stationlong = stod(row[4]);

	portalroutes = 0;
	//for each possible route (row[5] to row[15])
	for (int i = 5; i <= 15; i++) {
		//if the route is in the portal, set the correct bit in portalroutes
		if (row[i] != "") {
			//temp is binary digit that corresponds to current route
			long temp = routestring2int(row[i]);
			//cout<<temp<<endl;
			//shift left temp many times
			temp = (static_cast<long int>(1) << temp);
			//cout<<temp<<endl;
			//bitwise or with ans to set the correct bit in portalroutes
			portalroutes = portalroutes | temp;
			//cout<<portalroutes<<endl;
		}
	}
	
	//cout<<"routeset: " << portalroutes<< " string: "<<str_from_routeset(portalroutes)<<endl;
	
	entrancetype = row[16];
	entry = (row[17].compare("YES") == 0);
	exitonly = (row[18].compare("YES") == 0);
	vending = (row[19].compare("YES") == 0);
	staff = row[20];
	staffhrs = row[21];
	ada = (row[22].compare("TRUE") == 0);
	adanotes = row[23];
	freecross = (row[24].compare("TRUE") == 0);
	northsouthst = row[25];
	eastwestst = row[26];
	corner = row[27];
	string ids = row[28]; //string id for portalname
	id = stoi(row[28]); //int id for the variable itself
	portalname = trimspaces(northsouthst + "," + eastwestst + "," + corner + "," + ids);
	entrancelat = stod(row[29]);
	entrancelong = stod(row[30]);
	//I could parse the last two elements of the vector
	//which contain the coords of GPS, but I already
	//have them in vector positions 3,4,29, and 30. 
	//It's easier to just use those to construct two GPS
	stationloc = GPS(stationlong, stationlat);
	entranceloc = GPS(entrancelong, entrancelat);

}

//copy constructor
SubwayPortal::SubwayPortal(SubwayPortal const& sp){
 	division = sp.division;
	line = sp.line;
  	stationname = sp.stationname;
  	stationlat = sp.stationlat;
  	stationlong = sp.stationlong;
  	portalroutes = sp.portalroutes;
  	entrancetype = sp.entrancetype;
  	entry = sp.entry;
  	exitonly = sp.exitonly;
  	vending = sp.vending;
  	staff = sp.staff;
  	staffhrs = sp.staffhrs;
  	ada = sp.ada;
  	adanotes = sp.adanotes;
  	freecross = sp.freecross;
  	northsouthst = sp.northsouthst;
  	eastwestst = sp.eastwestst;
  	corner = sp.corner;
  	id = sp.id;
	portalname = sp.portalname;
  	entrancelat = sp.entrancelat;
  	entrancelong = sp.entrancelong;
  	stationloc = sp.stationloc;
  	entranceloc = sp.entranceloc;
}
void SubwayPortal::operator=(SubwayPortal const& sp){
 	division = sp.division;
	line = sp.line;
  	stationname = sp.stationname;
  	stationlat = sp.stationlat;
  	stationlong = sp.stationlong;
  	portalroutes = sp.portalroutes;
  	entrancetype = sp.entrancetype;
  	entry = sp.entry;
  	exitonly = sp.exitonly;
  	vending = sp.vending;
  	staff = sp.staff;
  	staffhrs = sp.staffhrs;
  	ada = sp.ada;
  	adanotes = sp.adanotes;
  	freecross = sp.freecross;
  	northsouthst = sp.northsouthst;
  	eastwestst = sp.eastwestst;
  	corner = sp.corner;
  	id = sp.id;
	portalname = sp.portalname;
  	entrancelat = sp.entrancelat;
  	entrancelong = sp.entrancelong;
  	stationloc = sp.stationloc;
  	entranceloc = sp.entranceloc;
}

//move operator
void SubwayPortal::operator=(SubwayPortal&& sp){
  //cout<<"portal move operator"<<endl;
 	division = sp.division;
	line = sp.line;
  	stationname = sp.stationname;
  	stationlat = sp.stationlat;
  	stationlong = sp.stationlong;
  	portalroutes = sp.portalroutes;
  	entrancetype = sp.entrancetype;
  	entry = sp.entry;
  	exitonly = sp.exitonly;
  	vending = sp.vending;
  	staff = sp.staff;
  	staffhrs = sp.staffhrs;
  	ada = sp.ada;
  	adanotes = sp.adanotes;
  	freecross = sp.freecross;
  	northsouthst = sp.northsouthst;
  	eastwestst = sp.eastwestst;
  	corner = sp.corner;
  	id = sp.id;
	portalname = sp.portalname;
  	entrancelat = sp.entrancelat;
  	entrancelong = sp.entrancelong;
  	stationloc = sp.stationloc;
  	entranceloc = sp.entranceloc;
}

vector<string> SubwayPortal::constructvector(string s) {
	string temp = ""; //current element
	vector<string> ans;
	bool inquote = false; //true if s is inside quotes

	for (unsigned int i = 0; i < s.size(); i++) {
		//if char is a quote, add it and set the flag
		if(s[i] == '\"' and !(inquote)){
			temp = temp + s[i];
			inquote = true;
			continue;
		}
		if(s[i] == '\"' and inquote){
			temp = temp + s[i];
			inquote = false;
			continue;
		}
		//if either char is in quotes, or its not a comma
		//then its not a comma seperator. add it to temp
		if (s[i] != ',' or inquote) {
			temp = temp + s[i];
		}

		//at this point, s[i] must be a comma seperator
		//add temp to vector, reset temp
		if(s[i] == ',' and !(inquote)){
			ans.push_back(temp);
			temp = "";
		}
		
	}

	//no comma seperator for the last, so it's added manually
	ans.push_back(temp);
	return ans;
}

double SubwayPortal::distance_from(double latitude, double longitude) {
	//construct a GPS from parameters, then use distance_between(gps,gps)
	GPS rhs(longitude, latitude);
	return distance_between(stationloc, rhs);
}

double distance_between(SubwayPortal portal1, SubwayPortal portal2) {
	//use distance_between(gps,gps)
	return distance_between(portal1.entranceloc, portal2.entranceloc);
}

bool same_routes(SubwayPortal portal1, SubwayPortal portal2) {
	return portal1.portalroutes == portal2.portalroutes;
}

bool same_station(SubwayPortal portal1, SubwayPortal portal2) {
	return (portal1.stationname.compare(portal2.stationname) == 0);
}

//What this should output wasn't defined
//So I just made it output the portals name
ostream& operator<<(ostream& out, SubwayPortal e) {
	out<< e.name();
	return out;
}


//accessor functions
string SubwayPortal::name() const {
	return portalname;
}

string SubwayPortal::sname() const{
	return stationname;
}

bool SubwayPortal::can_access(route_set route) const {
	//cout<<(1 & 3)<<endl;
	//cout<<((portalroutes & route) != 0)<<endl;
	return ((portalroutes & route) != 0);
}

GPS SubwayPortal::p_location() const {
	return entranceloc;
}

GPS SubwayPortal::s_location() const {
	return stationloc;
}

route_set SubwayPortal::routes() const {
	return portalroutes;
}
