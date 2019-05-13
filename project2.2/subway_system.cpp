/******************************************************************************
  Title          : subway_system.cpp
  Author         : Thomas Westfall
  Created on     : May 1, 2019
  Description    : SubwaySystem implementation
  Purpose        :
  Usage          :
  Build with     : c++11
  Modifications  :

******************************************************************************/

#include "subway_system.h"
SubwaySystem::SubwaySystem(){
	size = 0;
	for(long i = 0; i < 64; i++){
		routes[i].routes = (static_cast<long int>(1) << i);
	}
}
SubwaySystem::~SubwaySystem(){
}
int SubwaySystem::add_portal(SubwayPortal portal){
	//cout<<"ssystem addportal called"<<endl;
	//no need to sizecheck since the dataset < 2048 entries
	//same logic was applied when implementing the hashtable
	//only check if portal is default constructed (has an empty name)
	if(portal.name() == "")
		return 0;

	//portal is valid, add portal and portalname to next free location
	//within the parenttree array
	stations[size].set_portal(portal);
	stations[size].set_portal_name(portal.name());
	
	//add the station's own station name to it's station name list
	stations[size].add_station_name(portal.sname());

	//for every possible route, if the portal can access the current route
	//then add it's position to route's station list
	for(int i = 0; i < 64; i++)
		if(portal.can_access(routes[i].routes))
			routes[i].add_station_to_route(size);
		
	//now insert portalname into corresponding hash table
	__ItemType item;
	item.set(portal.name(), size);
	portalnames.insert(item); //insert portal name into hash table
	size = size + 1;
	return 1;
}

//this prints a duplicate of the following station:
//6 Avenue-47-50th Sts Rockefeller Center
//Though this isn't a bug since that station has portals
//With two different route sets under the same name.
//(line 482 of newstationnames.csv, this portal has
//the same station name, but also has the 7 route on
//top of original routes
//so, these two "different" stations are not connected
//since they have different routesets
void SubwaySystem::list_all_stations(ostream& out){
	//for each element in station array, check if element < 0
	//if it is, its a parent. run through the parent's 
	//station names (using the names() list), and output each one.
	for(int k = 0; k < size; k++)
	if(stations[k].parent_id() < 0){
		list<string>::iterator itrs; //list iterator
		list<string> stlist = stations[k].names(); //station list
		for(itrs = stlist.begin(); itrs != stlist.end(); ++itrs){
			out << *itrs <<endl;
		}
	}
}

void SubwaySystem::list_all_portals(ostream& out, string station_name){
	__ItemType item;
	int pos = 0; //where the station is stored in the hash table
	item.set(station_name, pos);
	int found = stationnames.find(item);
	if(found){
		item.get(station_name,pos);
		out << stations[pos].portal_name()<<endl; //highest parent portal
		//now output the portal children of this station

		list<int> sportals = stations[pos].portal_list();
		list<int>::iterator itr;
		for(itr = sportals.begin(); itr != sportals.end(); ++itr)
			out << stations[*itr].portal_name()<<endl;
	}
}

//these arent in the order that some of eniac's output files were in
//but the same stations are still outputted
void SubwaySystem::list_stations_of_route(ostream& out, route_id route){
	list<int> routestationlist;
	routestationlist = routes[routestring2int(route)].station_list();

	list<int>::iterator itr;
	SubwayPortal p;

	list<string> foundstr;
	list<string>::iterator itrs;
	bool foundornot = false;

	//outputs each station only once (no dupes allowed)
	//subwayroutes addstationtoroute doesnt handle dupes, so i have to do it
	//in this method
	for(itr = routestationlist.begin(); itr != routestationlist.end(); ++itr){
		foundornot = false;

		for(itrs = foundstr.begin(); itrs != foundstr.end(); ++itrs){
			string temp = *itrs;
			//if the name is already in the list, break
			if(temp.compare(stations[*itr].primary_name()) == 0){
				foundornot = true;
				break;
			}
		}
		//if not found, output it and add it to the alreadyfound list
		if(!foundornot){
			out << stations[*itr].primary_name()<<endl;
			foundstr.push_back(stations[*itr].primary_name());  
		}
	}
}


int SubwaySystem::form_stations() {
	//check every possible pair of stations for connectivity
	//if they should connect, find their parents then union them
	//O(N^2)
	for(int i = 0; i < size; i++){
		if(i == size - 1)
			break; //checked all pairs at this point, break
		for(int j = i+1; j < size; j++)
			//if connected, union parent sets
			if(connected(stations[i], stations[j]))
				unionstations(findstation(i),findstation(j));
	}

	//now fill out children and station lists/sets for parents
	//no need to set children and stations for non-parents.

	//set children of parents
	for(int m = 0; m < size; m++)
		if(stations[m].parent_id() > 0)
			stations[findstation(m)].add_child(m);

	//set stations of parents
	for(int n = 0; n < size;  n++){
		if(stations[n].parent_id() < 0){
			//list of children locations in stations[]
			list<int> children = stations[n].portal_list(); 
			list<int>::iterator itr; //list iterator

		//for each child, add its station name to parents stationname list
		//each stataion[] element is guarenteed a primary name because
		//they were given portals station name in add_portal(portal)
			for(itr = children.begin(); itr != children.end(); ++itr)
				stations[n].add_station_name(stations[*itr].primary_name());
			}
	}


	//now insert parents into the station hash table
	__ItemType item; //will contain station name
	int numstations = 0; //count of stations 

	//for each station, check if it has negative parentid
	//if it does, add each station in its station list
	//to the station hash table
	for(int k = 0; k < size; k++)
	if(stations[k].parent_id() < 0){
		list<string>::iterator itrs; //list iterator
		list<string> stlist = stations[k].names(); //station list
		//add each station name in the staiton names list 
		for(itrs = stlist.begin(); itrs != stlist.end(); ++itrs){
			item.set(*itrs,k); //prepare the item
			stationnames.insert(item); //inserted
		}
		numstations = numstations + 1; //increment station count
	}
	return numstations;
}

bool SubwaySystem::get_portal(string name_to_find, SubwayPortal& portal){
	string temp = name_to_find;
	//the first thing to do is to convert the given string into the
	//portal name format. meaning we convert the semicolons from the
	//command's given name_to_find into commas
	//the command is assumed to have semicolons as seperators because
	//the command files given on eniac have semicolons to divide the
	//portal name in listroutes commands. The name wasn't defined like
	//this in the assignment guidelines (name is separated by 
	//colons), but I want to just make sure and convert any
	//potential semicolons in the event that I'm wrong.
	bool inquote = false;
	for(unsigned int i = 0; i < name_to_find.length(); i++){
		if(name_to_find[i] == '\"')
			inquote = true;
		if(name_to_find[i] == '\"' and inquote)
			inquote = false;
		if(name_to_find[i] == ';' and !(inquote))
			name_to_find[i] = ',';
	}
	int arraypos = 0;
	string dummy = ""; //dummy string for item.get
	__ItemType item;
	item.set(name_to_find,arraypos);
	int found = portalnames.find(item); //find name in hash table
	if(found){
		item.get(dummy,arraypos);
		//set portal with the station at arraypos's portal
		
		stations[arraypos].get_portal(portal); 
		return true;
}
  return false;
}

string SubwaySystem::nearest_portal(double latitude, double longitude){
	SubwayPortal p; //current portal
	string ans = ""; //nearest portal's name
	double min = DBL_MAX; //anything < double max can be the new min at first
	double d = 0.0; //current distance between the two gps
	GPS loc = GPS(longitude, latitude); //gps for given lat and long
	
	//iterate through stations[], checking the distance between
	//the given gps and the current station's portal's gps.
	//if their distance between is smaller than min, it's the new min
	//it's also now the closest portal to the given gps
	//set its name to ans
	for(int i = 0; i < size; i++){
		//if you only want to check parent stations' portals
		//uncomment this if statement
		//this will make nearestportal's output match
		//with the outputs found on eniac, though it is not
		//the correct answer
		//if(stations[i].parent_id() > 0)
		//	continue;
		stations[i].get_portal(p);
		d = distance_between(p.p_location(), loc);
		if(d < min){
			ans = p.name();
			min = d;
		}
	}
  return ans;
}

string SubwaySystem::nearest_routes(double latitude, double longitude){
	SubwayPortal p; //nearest portal

	//nearest portal's name
	string portalname = nearest_portal(latitude, longitude);
	int position = 0; //location of nearest portal in stations[]
	__ItemType item; //needed to find portal in hash table
	item.set(portalname, position); //set the item with pname
	portalnames.find(item); //find closest portals position
	item.get(portalname, position); //get portal position
	//position = findstation(position); //parents position
	stations[position].get_portal(p); //get portal at position
	
	//return routeset of nearest portal
	return str_from_routeset(p.routes());
}


//adapted from chapter 8's disjoint class implementation 
//param x: location of a station in stations[]
//returns the the position of station[x]'s highest parent
int SubwaySystem::findstation(int x) const{
	//at highest parent. return its position in the station array
	if (stations[x].parent_id() < 0)
		return x;
	else{
		//go up the set until highest parent is found
		return findstation(stations[x].parent_id());
	}
}

//adapted from chapter 8's disjoint class implementation
//if stations[r1]'s set size is larger than stations[r2], 
//make station[r1] station[r2]'s parent
//if stations[r1]'s set size is smaller than stations[r2], 
//make stations[r2] stations[r1]'s parent
void SubwaySystem::unionstations(int r1, int r2) {
	if(r1 == r2)
		return; //dont union with itself
	SubwayPortal current;
	SubwayPortal temp;
	string currentname;
	__ItemType item;

	if (stations[r2].parent_id() < stations[r1].parent_id()){ 
	//root2 is deeper
		stations[r2].set_parent(stations[r1].parent_id() + stations[r2].parent_id());
		stations[r1].set_parent(r2); //r2 is now parent of r1
	}
	else {
	//root1 is deeper
		stations[r1].set_parent(stations[r1].parent_id() + stations[r2].parent_id());
		stations[r2].set_parent(r1); //r1 is now parent of r2
	}
}


