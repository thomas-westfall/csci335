/******************************************************************************
  Title          : hash_table.h
  Author         : Thomas Westfall
  Created on     : April 8, 2019
  Description    : The interface to the hash table class
  Purpose        :
  Usage          :
  Build with     : No building

******************************************************************************/
#ifndef HASH_TABLE_H__
#define HASH_TABLE_H__

#include <string>
#include "_hash_table.h"

using namespace std;

//Stick the ItemType and the state into a struct for lazy deletion.
struct Item {
    __ItemType element;
    int st; //-1 for DELETED, 0 for EMPTY, 1 for ACTIVE
    //st is constructed to 0 by default
};

// The INITIAL_SIZE should be large enough that it will not need to be
// resized, but you might want to implement resizing in your class.
#define INITIAL_SIZE 4096



class HashTable : public __HashTable {
private:
    int maxsize; //maximum amount of elements the table can hold
    int currsize; //how many elements the table is holding at the moment
    Item* hashTable; //the array of Items (the hash table itself)

public:
    //Default constructor
    HashTable();
    //Parameterized constructor
    HashTable(int sz);
    //Destructor
    ~HashTable();

    /** find() searches in table for given item
     *  @precondition: item's key value is initialized
     *  @postcondition: if matching item is found, it is filled with value from
     *                  table.
     *  @param  ItemType [in,out] item : item to search for
     *  @return int 0 if item is not in table, and 1 if it is
     */
    int find   ( __ItemType & item ) const;
    //int findb (__ItemType & item) const;
    /** insert() inserts the given item into the table
     *  @precondition: item is initialized
     *  @postcondition: if item is not in table already, it is inserted
     *  @param  ItemType [in] item : item to insert
     *  @return int 0 if item is not inserted in table, and 1 if it is
     */
    int insert ( __ItemType item   );

    /** remove() removes the specified  item from the table, if it is there
     *  @precondition: item's key is initialized
     *  @postcondition: if item was in table already, it is removed and copied
     *                  into the parameter, item
     *  @param  ItemType [in] item : item to remove
     *  @return int 0 if item is not removed from the table, and 1 if it is
     */
    int remove ( __ItemType  item );


    /** size() returns the number of items in the table
     *  @precondition: none
     *  @postcondition: none
     *  @return int the number of items in the table
     */
    int size() const;

    /** listall() lists all items currently in the table
     *  @note   This function writes each item in the tabel onto the given stream.
     *          Items should be written one per line, in whatever format the
     *          underlying _ItemType output operator formats them.
     *  @param  ostream [in,out] the stream onto which items are written
     *  @return int the number of items written to the stream
     */
    int listall ( ostream & os ) const;

};



#endif /* HASH_TABLE_H__ */

