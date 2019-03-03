#include "tree_collection.h"

TreeCollection::TreeCollection(){
}
TreeCollection::~TreeCollection(){
}
  
int TreeCollection::total_tree_count(){
  return 0;
}

int TreeCollection::count_of_tree_species ( const string & species_name ){
  return 0;
}

int TreeCollection::count_of_tree_species_in_boro
                  ( const string & species_name, const string & boro_name ){
  return 0;
}

int TreeCollection::get_counts_of_trees_by_boro ( const string & species_name,
                                       boro  tree_count[5] ){
  return 0;
}

int TreeCollection::count_of_trees_in_boro( const string & boro_name ){
  return 0;
}

int TreeCollection::add_tree( Tree & new_tree){
  return 0;
}

void TreeCollection::print_all_species(ostream & out) const{

}

void TreeCollection::print(ostream & out ) const{

}

list<string> TreeCollection::get_matching_species(
                           const string & species_name) const{
  list<string> ans;
  return ans;
}

list<string> TreeCollection::get_all_in_zipcode(int zipcode) const{
  list<string> ans;
  return ans;
}

list<string> TreeCollection::get_all_near(double latitude, double longitude, 
                         double  distance) const{
  list<string> ans;
  return ans;
}
