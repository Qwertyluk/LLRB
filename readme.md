# LLRB Map

This repository contains the source code of the map container based on the Left-Leaning Black Tree. The container is implemented in C++.

## Overall information
* Red-black tree is a kind of self-balancing binary search tree in which each node stores extra information about color, used to ensure that the tree remains balanced during insertion and deletion process.
* Left-leaning red–black tree is a variant of the red–black tree that guarantees the same complexity for operations, but is designed to be easier to implement. It is based on three ideas:
    * Use a recursive implementation.
    * Require that nodes lean left.
    * Perform rotations on the way up the tree.


## Functionality
Implemented ``LLRB_Map class`` takes generic parameters: Key (each element in a map is uniquely identified by its key), T (type of the mapped value), Compare (a binary predicate that takes two element keys as arguments and returns a bool that determines if one key is greater than another) and Alloc (type of the allocator object used to define the storage allocation model).

``LLRB_Map class`` contains basic methods that can:
* modify container
* access elements of the container
* check capacity
* return iterators referring to the elements of the container
* perform look-up operations

Example of declaration an object of map class:<br/>
``LLRB_Map<int, std::string, std::less<int>, std::allocator<Node<int, std::string>>> map;``

Example of use the insert method that extends the container by inserting new elements:<br/>
``std::pair<Iterator<int, std::string>, bool> ret_pair = map.insert(std::make_pair(1, "value_1"));``

Example of use the erase method that removes from the map container a single element:<br/>
``size_t ret_size = map.erase(1);``

Example of use the access method that returns the value identified with key:<br/>
``std::string ret_value = map.at(1);``

Example of use the end() method that returns the iterator referring to the past-the-end element in the map container:<br/>
``Iterator<int, std::string> ret_iterator = map.end();``

Example of use one of the look up methods:<br/>
``Iterator<int, std::string> ret_iterator = map.lower_bound(5);``

## Features that will be added in the future:<br/>

* Extending current map class to be the same as the map container in C++ standard.