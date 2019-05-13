/******************************************************************************
  Title          : hash_table.cpp
  Author         : Thomas Westfall
  Created on     : April 8, 2019
  Description    : Implementation of a hash table
  Purpose        :
  Usage          :
  Build with     :
  Modifications  :
********************************************************************************/
#include "hash_table.h"


//helper functions isprime and nextprime
//for making the hash table always have a prime size
//since making the hash table size prime lessens
//collisions with division based hash functions
//checks if the given number is prime
bool isprime(int x){
    for(int i = 2; i <= x / 2; i++)
        if(x % i == 0)
            return false;
    return true;
}

//the output of nextprime will be the
//size of the hash table
int nextprime(int x) {
	//check if it is prime
	//if not, increment by 1
	//if so, return it
	while(true){
		if(isprime(x))
			return x;
		else
			x = x + 1;
	}
}

HashTable::HashTable() {
	//current size is 0 (no values inserted yet)
	currsize = 0;
    //make size the next prime of the initial size
	maxsize = nextprime(INITIAL_SIZE);
	//create the array of items (the hashtable itself)
	hashTable = new Item[maxsize];
}

HashTable::HashTable(int initial_size) {
    //current size is 0
    currsize = 0;
	// ensure table size is prime
	maxsize = nextprime(initial_size);
	// initialize hash table
	hashTable = new Item[maxsize];
}


HashTable::~HashTable() {
    //since the hash table array was dynamically allocated
    //we have to explicitly delete it in the destructor.
	 delete[] hashTable;
}


int HashTable::find(__ItemType& item) const {
    //hashed key, modded with the maxsize
	int i = item.code() % maxsize;
	string dummystring; //key, but isn't modified so its a dummystring
	int val; //the value that will be items value if its found
    //special O(1) case: if where the item is supposed to be is empty
    //then return 0, since it wont be anywhere else in the table
    if(hashTable[i].st == 0)
        return 0;

    int stopper = i-1;
    while (true){
        //if its in the correct place, we get O(1) time
        //worst case is O(n) when its not in the table
        //and the position where its supposed to be is
        //either occupied with an active or deleted item
      if (hashTable[i].element == item and hashTable[i].st == 1){
	hashTable[i].element.get(dummystring,val); //get element's value
	item.set(dummystring,val); //set item's value
	return 1;
      }
        i = i + 1; //Doing linear probing now
        //If i equals maxsize, then i goes back to 0 (to stay in table size)
        if(i == maxsize)
            i = i % maxsize;
        if (i == stopper)
            return 0; //looped once, not in table
		}
}

/*
//returns the value of the item if it is found, -1 otherwise
//pre: item is not default constructed
int HashTable::findb(__ItemType& item) const {
  string dummyval = "";
  int ans = -1;
    //hashed key, modded with the maxsize
	int i = item.code() % maxsize;

    //special O(1) case: if where the item is supposed to be is empty
    //then return 0, since it wont be anywhere else in the table
    if(hashTable[i].st == 0)
        return ans;

    int stopper = i-1;
    while (true){
        //if its in the correct place, we get O(1) time
        //worst case is O(n) when its not in the table
        //and the position where its supposed to be is
        //either occupied with an active or deleted item
      if (hashTable[i].element == item and hashTable[i].st == 1){
	hashTable[i].element.get(dummyval, ans);
	return ans;
      }
        i = i + 1; //Doing linear probing now
        //If i equals maxsize, then i goes back to 0 (to stay in table size)
        if(i == maxsize)
            i = i % maxsize;
        if (i == stopper)
            return ans; //looped once, not in table
		}
}
*/
//Assume the table is large enough to not
//need to be resized (and, by extension,
//never be full).
int HashTable::insert(__ItemType item) {
	//do nothing if item is already in the table
	if(find(item) == 1)
		return 0;

	//hashed key, modded with the maxsize
	int i = item.code() % maxsize;

	// check to see if the i already has an item at i
	// checks i+1 if yes, until it does a full loop
	// (which it can't, since the table is never full)
    while(true){
        //if the state of the current element is either
        //empty or deleted, then the item is inserted
        if(hashTable[i].st != 1) {
            hashTable[i].element = item; //actual insertion
            hashTable[i].st = 1; //element is now active
            currsize = currsize + 1; //increment size
            return 1; //its inserted, return 1
        }

    //Iterate (loop back to 0 when size is reached)
    //we're under the precondition that table isn't full
    //so we don't have to account for that (such as resizing)
    i = i + 1;
    if(i == maxsize)
        i = i % maxsize;
	}
}

int HashTable::remove(__ItemType item) {
	//if item not found, nothing to remove
	if (find(item) == 0)
		return 0;
    //We now know the item is in the hash table
    //so the remove WILL be successful.
	int i = item.code() % maxsize; //hashed key
    //check if the current element matches the item
    //lazy deletes it if true
    while(true){
    if (hashTable[i].element == item) {
        hashTable[i].st = -1; //marks the element deleted
        currsize = currsize - 1; //decrement size
        return 1; //item was removed, return 1
    }
    //iterate
    i = i + 1;
    if(i == maxsize)
        i = i % maxsize; //wrap around to start of table
    }
}

int HashTable::size() const {
	return currsize;
}

int HashTable::listall(ostream& os) const {
	int numvalid = 0;
	//iterate through table, writing
	//only active elements to the ostream
	//hashitem handles the newline
	for (int i = 0; i < maxsize; i++) {
	    //if element is active, write it to os
		if (hashTable[i].st == 1) {
			os << hashTable[i].element;
            //increment number of valid items written
			numvalid = numvalid + 1;
		}
	}
	return numvalid;
}
