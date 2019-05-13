Usage:
g++ -Wall -g -o main main.cpp hash_table.cpp _hash_item.cpp
./main textfile

Log:
4/8/19
Implemented GPS. Made stubs for hashtable and hashitem. The executable compiles.

4/9/19
Implemented __ItemType.

4/10/19
Started implementing __HashTable, namely the constructors and two helper functions (isprime and nextprime).

4/11/19
Implemented the rest of __HashTable (find, insert, remove). Documented code.

Notes:
- The hash table's hash function is simply the mod of the table size, and the collision resolution is just linear probing. I may improve these two aspects of the table in the later parts of the project.
- I don't implement resizing, because the size is assumed to be large enough so that resizing isn't needed.
- I do use the haversine formula implementation from Project1 for GPS's distance_between(point1,point2) and the Horner Rule encoding from Lecture Notes Chapter 5.5 for __ItemType's code(). 
