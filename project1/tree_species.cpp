#include <algorithm>
#include "tree_species.h"

TreeSpecies::TreeSpecies(){
 sizev = 0;
}

TreeSpecies::~TreeSpecies(){
}

void TreeSpecies::print_all_species(ostream & out) const{
  //copy the vector to a temp vector, sort the temp, then print in order.
  vector<string> speciestemp;
  
  for(int i = 0; i < speciesv.size(); i++){
    speciestemp.push_back(speciesv[i]);
  }
  sort(speciestemp.begin(),speciestemp.end());

  for(int i = 0; i < speciestemp.size(); i++){
    out<<speciestemp[i]<<endl;
  }
 
}
int TreeSpecies::number_of_species() const{
   return sizev;
}

int TreeSpecies::add_species( const string & species){
  //check if the species is already in treespecies. if not, add it
  int notfound = find(speciesv.begin(), speciesv.end(),
  		   species) == speciesv.end();
  if(notfound){
    speciesv.push_back(species);
    sizev++;
  }

  return notfound;

  }


list<string> TreeSpecies::get_matching_species(const string & partial_name) const{

  list<string> ans; //where the matching species names are stored
  string tree_type; //current species name
  string tree_to_find = ""; //= partial_name;

  //remove the leading space tacked on to partial_name from the command line
  if(partial_name.at(0) == ' '){
    for(int k = 1; k < partial_name.length(); k++)
      tree_to_find = tree_to_find + partial_name.at(k);
  }
  
  string temp = "";//where each space/dash-seperated value is stored

  //
  bool ispecial = false; //does the current species have spaces/hyphens
  bool ispecialp = false; //does partial name have spaces/hyphens

  //for possibility 3 (both partialname and speciesname have special chars)
  int stillmatching = 0; //check if partialname still matches speciesname
  vector<string> v1; //each element is a 
  vector<string> v2;

  //get a lowercase version of partial_name and tree_to_find
  transform(tree_to_find.begin(), tree_to_find.end(),
	    tree_to_find.begin(), ::tolower);

  //check if partial name has spaces or dashes
  size_t found = tree_to_find.find(" ");
  size_t foundh = tree_to_find.find("-");
  if(found != string::npos or foundh != string::npos)
    ispecialp = true;
  
  for(int i = 0; i < speciesv.size(); i++){
    
    //make current species lowercase
    tree_type = speciesv[i];
    transform(tree_type.begin(), tree_type.end(), tree_type.begin(), ::tolower);
    if(tree_type.compare(tree_to_find) == 0){
      ans.push_back(speciesv[i]);
      continue; //avoid pushing the same species again
    }
    //check if current species has ' ' or '-'
  found = tree_type.find(" ");
  foundh = tree_type.find("-");
  if(found != string::npos or foundh != string::npos)
    ispecial = true;
  
  //case 2: tree_to_find has no special chars but tree_species does
  if((!ispecialp) and (ispecial)){
    temp = "";

    //construct temp (current string separated by ' ' or '-'
    for(int k = 0; k < tree_type.length(); k++){

      //temp is complete (reached a specialchar or end of string)
      if((tree_type.at(k) == ' ' or tree_type.at(k) == '-') or
	 k == tree_type.length()-1){
	if(k == tree_type.length() - 1){
	  temp = temp + tree_type.at(k);
	}

	//check if the current separated value is equal to partialname
	if(temp.compare(tree_to_find) == 0){
	  ans.push_back(speciesv[i]);
	  break;
	}
	temp = "";
      }
      //temp is incomplete, add current char to temp
      if(tree_type.at(k) != ' ' and tree_type.at(k) != '-')
	temp = temp + tree_type.at(k);
    }
  }
  
  //case 3: tree_to_find and tree_species both have special chars
  if((ispecialp) and (ispecial)){
    v1.clear();
    v2.clear();
    temp = "";

    //construct v1 (holds words of partial name seperated by ' ' or '-')
    for(int f = 0; f < tree_to_find.length();f++){
      if((tree_to_find.at(f) == ' ' or tree_to_find.at(f) == '-') or
	 f == tree_to_find.length() - 1){
	if(f == tree_to_find.length() - 1)
	  temp = temp + tree_to_find.at(f);
	v1.push_back(temp);
	temp = "";
	continue;
      }
      if(tree_to_find.at(f) != ' ' and tree_to_find.at(f) != '-')
	temp = temp + tree_to_find.at(f);
    }
    temp = "";
    
    //construct v2 (holds words of current species name)
    //seperated by ' ' or '-'
    for(int g = 0; g < tree_type.length(); g++){
      if((tree_type.at(g) == ' ' or tree_type.at(g) == '-') or
	 g == tree_type.length() - 1){
	if(g == tree_type.length() - 1)
	  temp = temp + tree_type.at(g);
	v2.push_back(temp);
	temp = "";
	continue;
      }
      if(tree_type.at(g) != ' ' and tree_type.at(g) != '-')
	temp = temp + tree_type.at(g);
    }

    //iterate through v2 (currentspecies vector)
    //v2 is always at least one larger than v1 (since v1 is a partial name)
    //check if all of v1 (partial name) is in v2 (in order)
    stillmatching = 0;
    for(int d = 0; d < v2.size(); d++){
      if(v2[d] == v1[stillmatching])
	stillmatching++;
      else
	stillmatching = 0;
      
      if(v1[v1.size()-1] == v2[d] and stillmatching == v1.size()){
	ans.push_back(speciesv[i]);
	break;
      }
    } 
  }
  }
  return ans;
}


















