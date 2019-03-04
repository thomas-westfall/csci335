/*******************************************************************************
  Title          : tree_collection.h
  Author         : Thomas Westfall
  Created on     : March 2, 2019
  Description    : The interface file for the TreeCollection class
  Purpose        : To provide a minimal interface to be used to interact with 
                   the TreeCollection objects.
  Usage          : 
  Build with     : No building
  Modifications  : 
 
*******************************************************************************/
#ifndef Tree_Collection_H
#define Tree_Collection_H

#include "__tree_collection.h"
class TreeCollection : public __TreeCollection{
 public:
  TreeCollection();
  ~TreeCollection();
  int total_tree_count();
  int count_of_tree_species ( const string & species_name );
  int count_of_tree_species_in_boro ( const string & species_name,
				      const string & boro_name );
  int get_counts_of_trees_by_boro ( const string & species_name,
                                       boro  tree_count[5] );
  int count_of_trees_in_boro( const string & boro_name );
  int add_tree( Tree & new_tree);
  void print_all_species(ostream & out) const;
  void print(ostream & out ) const;
  list<string> get_matching_species(
                           const string & species_name) const;
  list<string> get_all_in_zipcode(int zipcode) const;
  list<string> get_all_near(double latitude, double longitude, 
                         double  distance) const;
};

#endif /* Tree_Collection_H */

