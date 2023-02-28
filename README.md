# Custom-Hash-Table
A C++ implementation of a custom hash table.  

This hash table support all major data types such as integer, float, character, string, double, long and short. Ideally, the hash table can be of any size (as large as you want). You can decide how large you want to make it.  
Whenever there is a collision during insertion of a new item into the hash table, [quadratic probing](https://cathyatseneca.gitbooks.io/data-structures-and-algorithms/content/tables/quadratic_probing_and_double_hashing.html#:~:text=by%20linear%20probing.-,Quadratic%20Probing,-Quadratic%20Probing%20is) strategy is used.  
The src folder contains the C++ implementation of the hash table. The HashTable.h file contains the implementation of the hash table class. The main.cpp file borrows the class and uses is to insert some values as an example. There are examples of many hash tables, each one for different data type.  

If you find any errors or have a better way of implementing any part of the hash table, feel free to reach out at <puneethar6@gmail.com> :)
