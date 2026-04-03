//
//  ArrayInt.hpp
//  ArrayInt
//
//  Created by Jim Bailey on 3/31/2021 with modifications by Tina Majchrzak
//  This work by Jim Bailey is licensed under a Creative
//  Commons Attribution 4.0 International License.
//

#ifndef ArrayInt_hpp
#define ArrayInt_hpp
#include <string>

class ArrayInt {
private:
    const static int SIZE = 10;
    int size;
    int lastIndex;
    int * theArray;
    
public:
    // constructor and destructor
    ArrayInt(int size = SIZE);
    ~ArrayInt();
    
    // return the array size
    int getSize() { return size; }

    // add item at next location in array
    void append(int value);

    // get last item in array
    int getLast();

    // delete item  at last location
    void deleteLast();

    // resize the array to s, if s is bigger than the current array size
    void resize(int s);
    
    // list elements from 0 to last location
    std::string listElements();
    
    // search for a value
    bool find(int value);

    // remove a value if found
    bool removeVal(int index);
    
    // return largest value
    int findLargest();

    // remove largest value
    void removeLargest();

    // insert item into array at index, moving other items as needed
    void insertAt(int index, int value);

    // remove item at index from array, moving other items as needed
    int removeAt(int index);

    // use append, findLargest, and remove to arrange values 
    // in descending order
    void solveThink(int *values, int numValues);
};

#endif /* ArrayInt_hpp */
