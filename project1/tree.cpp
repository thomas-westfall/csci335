#include "tree.h"

Tree::Tree(){}

Tree::Tree(const string & str) {}

Tree::Tree(int id, int diam,  string stat, string hlth, string name, 
        int zip, string addr, string boro, double lat, double longtd){}

ostream& operator<< (ostream & os, const Tree & t){
  return os <<"";
}

bool operator==(const Tree & t1, const Tree & t2){
  return true;
}

bool operator<(const Tree & t1, const Tree & t2){
  return true;
}

bool samename(const Tree & t1, const Tree & t2){
  return false;
}

bool islessname(const Tree & t1, const Tree & t2){
  return false;
}

string Tree::common_name() const{
  return "";
}
string Tree::borough_name() const{
  return "";
}
string Tree::nearest_address() const{
  return "";
}
string Tree::life_status() const{
  return "";
}
string Tree::tree_health() const{
  return "";
}
int Tree::id()       const{
  return 0;
}
int Tree::zip_code() const{
  return 0;
}
int Tree::diameter() const{
  return 0;
}
void Tree::get_position(double & latitude,double & longitude) const{
}

