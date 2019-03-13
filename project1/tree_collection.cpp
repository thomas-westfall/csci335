#include "tree_collection.h"
#include <cmath> //for haversine formula

//for haversine formula
const double R = 6372.8;
const double TO_RAD = M_PI / 180.0; //conversion of degrees to rads

//Given four doubles lat1, lon1, lat2, and long2, calculate approximate
//distance between the the points (lat1, lon1) and (lat2, lon2)
//This is a helper function used in the TreeCollection method get_all_near
//Taken from Project1 project guidelines, Section 6.1.3
double haversine(double lat1, double lon1, double lat2, double lon2){
  lat1 = TO_RAD * lat1;
  lat2 = TO_RAD * lat2;
  lon1 = TO_RAD * lon1;
  lon2 = TO_RAD * lon2;
  double dLat = (lat2 - lat1) / 2;
  double dLon = (lon2 - lon1) / 2;
  double a = sin(dLat);
  double b = sin(dLon);
  return 2 * R * asin(sqrt(a*a + cos(lat1) * cos(lat2)*b*b));
}

Tree t; //used to construct the avltree and temp

//default constructor
TreeCollection::TreeCollection() : avltree(t), tempavl(t){
  sizet = 0;
}

//destructor
TreeCollection::~TreeCollection(){
  //cout<<"tc destructor called"<<endl;
}

int TreeCollection::total_tree_count(){
  return sizet;
}

int TreeCollection::count_of_tree_species ( const string & species_name ){
  int ans = 0;
  Tree temptree;
  //tone = species_name, ttwo = current tree's species name
  //convert species names into lowercase first to make it case insensitive
  string tone = species_name;
  string ttwo = "";
  transform(tone.begin(), tone.end(), tone.begin(), ::tolower);

  tempavl = avltree; //avoid side effects
  while(!tempavl.isEmpty()){
    temptree = tempavl.findMin(); //current tree (minimum)
    ttwo = temptree.common_name();
    transform(ttwo.begin(), ttwo.end(), ttwo.begin(), ::tolower);
    if(tone.compare(ttwo) == 0) //increment if the two species match
      ans++;
    tempavl.remove(temptree); //iterate
  }
		     
    return ans;
}

int TreeCollection::count_of_tree_species_in_boro
                  ( const string & species_name, const string & boro_name ){
  Tree temptree;
  tempavl = avltree;
  int ans = 0;
  string tone = species_name;
  string ttwo = "";
  transform(tone.begin(), tone.end(), tone.begin(), ::tolower);

  while(!tempavl.isEmpty()){
    temptree = tempavl.findMin();
    if(temptree.borough_name().compare(boro_name) == 0){
      ttwo = temptree.common_name();
      transform(ttwo.begin(), ttwo.end(), ttwo.begin(), ::tolower);
      if(tone.compare(ttwo) == 0)
	ans++;
    }
    tempavl.remove(temptree);
  }
  return ans;
}

int TreeCollection::get_counts_of_trees_by_boro ( const string & species_name,
                                       boro  tree_count[5] ){
  //for each of the 5 boroughs, add to its treecount the count of the
  //current species name. 
   for(int i = 0; i < 5; i++)
    tree_count[i].count += count_of_tree_species_in_boro(species_name,
							tree_count[i].name);
  
  
  return count_of_tree_species(species_name);
}

int TreeCollection::count_of_trees_in_boro( const string & boro_name ){
  Tree temptree;
  int ans = 0;
  tempavl = avltree;
  while(!tempavl.isEmpty()){
    temptree = tempavl.findMin();
    if(temptree.borough_name().compare(boro_name) == 0)
      ans++;
    
    tempavl.remove(temptree);
  }
  return ans;
  
  
}

int TreeCollection::add_tree( Tree& new_tree){
  Tree isinside = avltree.find(new_tree);

  //check if the tree's id is 0. If true, return 0, since it's invalid.
  if(isinside.id() != 0)
    return 0;
  
  //check if the common name is empty. if not, add to treespecies
  //this accounts for stumps, which have no common_name, being ignored
  if(new_tree.common_name().compare("") != 0){
    treespeciesc.add_species(new_tree.common_name());
  }
  //the tree is valid, so it is added to the avltree
   avltree.insert(new_tree);
   sizet++;
  return 1;
}

void TreeCollection::print_all_species(ostream & out) const{
  treespeciesc.print_all_species(out);
}

void TreeCollection::print(ostream & out ) const{
  Tree temptree;//copied tree (also used to construct the temp avltree)
  //construct a new avltree here (instead of using private avltemp)
  //since this method has const property
  AvlTree<Tree> avltempb(temptree); //construct the temp avl tree
  avltempb = avltree; //copy the avltree into the temp avl tree

  //iterate through every value of the avltree
  while(!avltempb.isEmpty()){
    temptree = avltempb.findMin(); //sorted order, since we take min
    out<<temptree<<endl;
    avltempb.remove(temptree); //iterate
  }

}

list<string> TreeCollection::get_matching_species(
                           const string & species_name) const{
  return treespeciesc.get_matching_species(species_name);
}

list<string> TreeCollection::get_all_in_zipcode(int zipcode) const{
  list<string> ans;
  Tree temptree;//copied tree (also used to construct the temp avltree)
  string speciesname = ""; //current species name
  AvlTree<Tree> avltempb(temptree); //account for const
  avltempb = avltree; //copy the avltree into the temp avltree
  
  while(!avltempb.isEmpty()){
    temptree = avltempb.findMin(); //current tree (minimum)

    //check if zipcode is equal to the current tree's zipcode
    if(temptree.zip_code() == zipcode){
      speciesname = temptree.common_name();
      
      //check if the current species name is already in ans
      //commenting the following if statement (which ignores duplicates)
      //makes the main file's output for the listall_inzip command correct
      //Leaving this if statement in would make the returned list not have
      //duplicates, but would give me frequencies of 1 for every tree
      
      //if true, the current tree's speciesname is added to the answer list
      //	if(find(ans.begin(), ans.end(), speciesname) == ans.end()){
	  ans.push_back(speciesname);
	  //  }
    }
    
    avltempb.remove(temptree); //iterate
  }
  return ans;
}

list<string> TreeCollection::get_all_near(double latitude, double longitude, 
                         double  distance) const{
  list<string> ans;
  Tree temptree; //copied tree (also used to construct the temp avltree)
  string speciesname = ""; //
  double currentlat = 0.0; //current tree's latitude
  double currentlon = 0.0; //current tree's longitude
  double currentdistance = 0.0; //current distance to be compared
  AvlTree<Tree> avltempb(temptree); //account for const
  avltempb = avltree; //copy the avltree into avltempb
  
  while(!avltempb.isEmpty()){
    temptree = avltempb.findMin();//current tree
    temptree.get_position(currentlat, currentlon);//current tree's lat and long

    //find the distance between the two points using the Haversine formula:
    currentdistance = haversine(latitude, longitude, currentlat, currentlon);
    
    //check if current distance is less than specified distance
    //if true, the current tree's speciesname is added to the answer list
    if(currentdistance < distance){
      speciesname = temptree.common_name();

      //similar to get_all_in_zipcode, having duplicates in the returned
      //list gives the correct frequency output of each matached species
      //near the given point. Having this statement in will result in only
      //having a frequency of 1 for each found species.
      
      //check if the current species name is already in ans
      //	if(find(ans.begin(), ans.end(), speciesname) == ans.end()){
	  ans.push_back(speciesname);
	  //}
    }
    
    avltempb.remove(temptree); //iterate
  }
  return ans;
}
