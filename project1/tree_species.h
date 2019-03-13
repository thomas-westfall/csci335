/*******************************************************************************
  Title          : tree_species.h
  Author         : Thomas Westfall
  Created on     : March 3, 2019
  Description    : The interface file for the TreeSpecies class
  Purpose        : To provide a minimal interface to be used to interact with 
                   the TreeSpecies objects.
  Usage          : 
  Build with     : No building
  Modifications  : 
 
*******************************************************************************/

#ifndef Tree_Species_H_
#define Tree_Species_H_

#include <vector>
#include "__tree_species.h"

class TreeSpecies : public __TreeSpecies
{
private:
  vector<string> speciesv;
  int sizev;

public:
  TreeSpecies();
  ~TreeSpecies();
  string getspecies(int i);
  void print_all_species(ostream & out) const;
  int number_of_species() const;
  int add_species( const string & species);
  list<string> get_matching_species(const string & partial_name) const;
};

#endif /* Tree_Species_H_ */









