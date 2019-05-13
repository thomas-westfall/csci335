/******************************************************************************
Title          : subway_station.cpp
Author         : Thomas Westfall
Created on     : May 1, 2019
Description    : SubwayStation implementation
Purpose        : 
Usage          :
Build with     :c++11
Modifications  :

******************************************************************************/

#include "subway_station.h"

SubwayStation::SubwayStation() {
	m_parent_id = -1;
	portal_unique_name = "";
}

SubwayStation::SubwayStation(SubwayPortal portal) {
  cout<<"station parameter cons called"<<endl;
  this->portal = portal;
  add_station_name(portal.sname());
  
}

void SubwayStation::set_parent(int newparent) {
  m_parent_id = newparent;
}

void SubwayStation::add_child(int child) {
  children.push_back(child);
}

bool connected(SubwayStation s1, SubwayStation s2) {
  double d = distance_between(s1.portal.s_location(), s2.portal.s_location());
  return ((s1.portal.routes() == s2.portal.routes()) and d < 0.32);
}

int SubwayStation::add_station_name(string newname) {
	return m_station_names.emplace(newname).second;
}

//this returns a list to be consistent with the assignment
//definition of this method. I know station names is
//a set,but at this point, all of its names are already
//added, so there can't be any dupes if its converted
//to a list at this point. 
list<string> SubwayStation::names() const {
  list<string> ans;
  set<string>::iterator itr = m_station_names.begin();
  while(itr != m_station_names.end()){
	ans.push_back(*itr);
	itr++;
}
  return ans;
}

string SubwayStation::primary_name() const {
  set<string>::iterator itr = m_station_names.begin();
  return *itr;
}

int SubwayStation::parent_id() const {
  return m_parent_id;
}

list<int> SubwayStation::portal_list() const {
  return children;
}

string SubwayStation::portal_name() const {
  return portal_unique_name;
}

void SubwayStation::get_portal(SubwayPortal& portal) const {
  portal = this->portal;
}

void SubwayStation::set_portal(SubwayPortal p){
	portal = p;
}
void SubwayStation::set_portal_name(string s){
	portal_unique_name = s;
}

