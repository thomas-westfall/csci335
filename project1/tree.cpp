#include "tree.h"

//helper function used by Tree::Tree(const string & str)
//returns true if the string is an integer, false otherwise
bool isint(string s){
  char* p;
  strtol(s.c_str(), &p, 10);
  return *p == 0;
}

//helper function used by Tree::Tree(const string & str)
//returns true if the given string is a double, false otherwise
bool isdouble(string s){
  char* p;
  strtod(s.c_str(), &p);
  return *p == 0;
}

//helper function used by issamename and islessname
//returns the lowercase version of a string
string tolowers(string s){
  string ans = s;
  transform(ans.begin(), ans.end(), ans.begin(), ::tolower);
  return ans;
}

Tree::Tree(){
  tree_id = 0;
  tree_dbh = 0;
  status = "";
  health = "";
  spc_common = "";
  zipcode = 0;
  address = "";
  boroname = "";
  latitude = 0.0;
  longitude = 0.0;
}

Tree::Tree(const string & str){
  //I would have used delegating constructors here but the compiler
  //defaults on the cslab machines aren't c++11, so I copy and paste
  //the default constructor here to account for invalid str parameter
  tree_id = 0;
  tree_dbh = 0;
  status = "";
  health = "";
  spc_common = "";
  zipcode = 0;
  address = "";
  boroname = "";
  latitude = 0.0;
  longitude = 0.0;

  bool valid = true; //check if the str parameter is valid
  bool isquoteclosed = true; //check if string is in double quote
  int commacounter = 0;
  string id, diam, stat, hlth, name, zip, addr, boro, lat, longtd;
  for(unsigned int i = 0; i < str.length(); i++){
    if(str[i] == '\"' and isquoteclosed) isquoteclosed = false;
    if(str[i] == '\"' and !isquoteclosed) isquoteclosed = true;
    if(str[i] == ',' and isquoteclosed){
      commacounter++;
      continue; //avoid putting comma separators into tree values
    }

    //check which comma str is at, creates needed values accordingly
    if(commacounter == 0) id = id + str[i];
    if(commacounter == 3) diam = diam + str[i];
    if(commacounter == 6) stat = stat + str[i];
    if(commacounter == 7) hlth = hlth + str[i];
    if(commacounter == 9) name = name + str[i];
    if(commacounter == 24) addr = addr + str[i];
    if(commacounter == 25) zip = zip + str[i];
    if(commacounter == 29) boro = boro + str[i];
    if(commacounter == 37) lat = lat + str[i];
    if(commacounter == 38) longtd = longtd + str[i];
  }
  
  //checks if tree id, diameter, and zipcode are valid integers
  //also checks if latitude and longitude are valid doubles
  if (!isint(id) or !isint(diam) or !isint(zip) or
      !isdouble(lat) or !isdouble(longtd))
    valid = false;

  //if one or more input string values is invalid, nothing more is done
  //in other words, the constructed tree remains to be an empty tree
  //if input is valid, tree values are updated by the values retrieved
  //from the string
  if(valid){
    tree_id = atoi(id.c_str());
    tree_dbh = atoi(diam.c_str());
    status = stat;
    health = hlth;
    spc_common = name;
    zipcode = atoi(zip.c_str());
    address = addr;
    boroname = boro;

    char *p;
    latitude = strtod(lat.c_str(), &p);
    longitude = strtod(longtd.c_str(), &p);
  }
}

Tree::Tree(int id, int diam,  string stat, string hlth, string name, 
        int zip, string addr, string boro, double lat, double longtd){
  tree_id = id;
  tree_dbh = diam;
  status = stat;
  health = hlth;
  spc_common = name;
  zipcode = zip;
  address = addr;
  boroname = boro;
  latitude = lat;
  longitude = longtd;
}

ostream& operator<< (ostream & os, const Tree & t){
  double latitude, longitude;
  t.get_position(latitude,longitude);
  return os <<t.common_name()<<','<<t.id()<<','<<t.diameter()<<','<<
    t.life_status()<<','<<t.tree_health()<<','<<t.nearest_address()<<','<<
    t.zip_code()<<','<<t.borough_name()<<','<<latitude<<','<<longitude;
}

bool operator==(const Tree & t1, const Tree & t2){
  return samename(t1,t2) and t1.id() == t2.id();
}

bool operator<(const Tree & t1, const Tree & t2){
  if (islessname(t1,t2))
    return true;
  if (t1.id() < t2.id())
    return true;
  return false;
}

bool samename(const Tree & t1, const Tree & t2){
  return tolowers(t1.common_name()) == tolowers(t2.common_name());
}

bool islessname(const Tree & t1, const Tree & t2){
  return tolowers(t1.common_name()) < tolowers(t2.common_name());
}

string Tree::common_name() const{
  return spc_common;
}
string Tree::borough_name() const{
  return boroname;
}
string Tree::nearest_address() const{
  return address;
}
string Tree::life_status() const{
  return status;
}
string Tree::tree_health() const{
  return health;
}
int Tree::id()       const{
  return tree_id;
}
int Tree::zip_code() const{
  return zipcode;
}
int Tree::diameter() const{
  return tree_dbh;
}
void Tree::get_position(double & latitude,double & longitude) const{
  latitude = this->latitude;
  longitude = this->longitude;
}

