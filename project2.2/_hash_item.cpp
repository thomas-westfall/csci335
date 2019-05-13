/******************************************************************************
  Title          : _hash_item.cpp
  Author         : Thomas Westfall
  Created on     : April 8, 2019
  Description    : Implementation of hash item
  Purpose        :
  Usage          :
  Build with     :
********************************************************************************/
#include "_hash_item.h"

__ItemType::__ItemType() {
	key = "";
	order = 0;
}

void __ItemType::set(string s, int pos) {
	key = s;
	order = pos;
}

void __ItemType::get(string& s, int& pos) {
	s = key;
	pos = order;
}

bool __ItemType::operator==(__ItemType rhs) const {
    //make copies of the two keys to avoid side effects
    string keylower = key;
    string rhskeylower = rhs.key;
    //make these two keys lowercase
    transform(keylower.begin(), keylower.end(), keylower.begin(), ::tolower);
    transform(rhskeylower.begin(), rhskeylower.end(), rhskeylower.begin(), ::tolower);
    //check if these two keys are the same
    return (keylower.compare(rhskeylower) == 0);
}

//This implementation of code() was adapted from Lecture Notes Chapter 5.5
//It uses Horner's Rule to encode a string
//It uses and returns an unsigned int to account for integer overflow
unsigned int __ItemType::code() {
    unsigned int hashval = 0;

    //95 printable ASCII characters, so use 95 for RADIX
    for (unsigned int i = 0; i < key.length(); i++)
      hashval = key[i] + 95 * hashval; // p(x) = s_i + x(q(x))
    return hashval;
}

ostream& operator<<(ostream& os, __ItemType item) {
	os << item.key << endl;
	return os;
}

