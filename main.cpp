//
//  main.cpp
//  ArrayInt
//
//  Created by Jim Bailey on 3/31/2021 with modifications by Tina Majchrzak
//  This work by Jim Bailey is licensed under a Creative
//  Commons Attribution 4.0 International License.
//

#include "ArrayInt.hpp"
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <stdexcept>
#include <fstream>
#include <algorithm>

#define TEST_CONSTRUCTOR
//#define TEST_APPEND
//#define TEST_MAKE_ROOM
//#define TEST_FIND
//#define TEST_LARGEST

//#define TEST_INSERT_REMOVE
//#define TEST_MIX

//#define TEST_THINK

// Read in values from file
void readInVals(int* arr, int numElems, int skipLines);


int main(int argc, const char *argv[]) {
#ifdef TEST_CONSTRUCTOR
  const int DEFAULT = 10;
  const int OVERLOAD = 15;
  std::cout << "TESTING default and overloaded constructors and getSize.\n\n";

  ArrayInt defaultSize;
  ArrayInt defineSize(OVERLOAD);

  std::cout << "Default size should be " << DEFAULT << " and is " << defaultSize.getSize() << "\n";
  std::cout << "Overload size should be " << OVERLOAD << " and is " << defineSize.getSize() << "\n\n";
  std::cout << "Done with constructor test\n\n\n";
#endif // TEST_CONSTRUCTOR


#ifdef TEST_APPEND
  std::cout << "TESTING append, getLast, and deleteLast\n\n";

  ArrayInt appends;
  const int NUM_APPENDS = 5;
  int appendVals[NUM_APPENDS];
  readInVals(appendVals, NUM_APPENDS, 0);

  for (int i = 0; i < NUM_APPENDS; i++) {
    appends.append(appendVals[i]);
  }

  std::cout << "After APPEND array should be: ";
  for (int i=NUM_APPENDS-1; i>=0; i--) std::cout << appendVals[i] << " ";
  std::cout << "\n";
  std::cout << "             array really is:";
  try {
    for (int i = 0; i < NUM_APPENDS; i++) {
      std::cout << " " << appends.getLast();
      appends.deleteLast();
    }
    std::cout << "\n";
  } catch (...) {
    std::cout << "Problem with appending and deleting\n\n";
  }

  std::cout << "Trying getLast on empty array, should throw exception\n";
  try {
    std::cout << appends.getLast() << "\n";
  } catch (std::out_of_range &ex) {
    std::cout << "Caught out of range with message: " << ex.what() << "\n";
  } catch (...) {
    std::cout << "Caught something weird\n";
  }

  std::cout << "Trying to delete from empty array, should throw exception\n";
  try {
    appends.deleteLast();
  } catch (std::out_of_range &ex) {
    std::cout << "Caught out of range with message: " << ex.what() << "\n";
  } catch (...) {
    std::cout << "Caught something weird\n";
  }
#endif // TEST_APPEND


#ifdef TEST_MAKE_ROOM
  const int START = 7;
  const int UPDATE = 12;
  int roomVals[UPDATE];
  readInVals(roomVals, UPDATE, 1);

  std::cout << "\n\nTESTING resize, auto expansion on appends, and listElements\n\n";

  ArrayInt room(START);
  std::cout << "Starting size should be " << START << " and is " << room.getSize() << "\n";
  room.resize(UPDATE);
  std::cout << "After resize, size should be " << UPDATE << " and is " << room.getSize() << "\n\n";

  std::cout << "Now going to fill array and see if it expands\n";
  for (int i = 0; i < UPDATE; i++) {
    room.append(roomVals[i]);
  }
  std::cout << "Filled with 12 values, no problem\n";
  std::cout << "Size should still be " << UPDATE << " and is " << room.getSize() << "\n\n";
  std::cout << "Adding one more\n";
  room.append(88);
  std::cout << "Size should now be " << 2 * UPDATE << " and is " << room.getSize() << "\n\n";

  std::cout << "After MAKE ROOM should be:";
  for (int i=0; i<UPDATE; i++) std::cout << " " << roomVals[i];
  std::cout << " 88\n";
  std::cout << "                really is:" << room.listElements() << "\n\n\n";
#endif // TEST_MAKE_ROOM


#ifdef TEST_FIND
  const int FIND_COUNT = 10;
  std::cout << "TESTING find and removeVal\n\n";

  ArrayInt findRemove;
  int findRemVals[FIND_COUNT];
  readInVals(findRemVals, FIND_COUNT, 2);
  for (int i = 0; i < FIND_COUNT; i++) {
    findRemove.append(findRemVals[i]);
  }
  int lastEl = findRemVals[FIND_COUNT-1];

  std::cout << "Array contains " << findRemove.listElements() << "\n";

  std::cout << "Testing find on 4 and 7.\n";
  std::cout << "  4" << (findRemove.find(4) ? " was " : " was not ") << "found\n";
  std::cout << "  7" << (findRemove.find(7) ? " was " : " was not ") << "found\n";

  std::cout << "Testing removeVal on 4 and 7.\n";
  std::cout << "  4" << (findRemove.removeVal(4) ? " was " : " was not ") << "removed\n";
  std::cout << "  7" << (findRemove.removeVal(7) ? " was " : " was not ") << "removed\n";

  std::cout << "After REMOVE expected:";
  for (int i=0; i<FIND_COUNT; i++) 
    if ((findRemVals[i]!=4) && (findRemVals[i]!=7)) std::cout << " " << findRemVals[i];
  std::cout << "\n             actually:" << findRemove.listElements() << "\n\n";

  std::cout << "Using removeVal on final element, " << lastEl << "\n";
  std::cout << lastEl << (findRemove.removeVal(lastEl) ? " was " : " was not ") << "removed" << "\n";

  std::cout << "Using find to look for " << lastEl << " after removal.  Should not find\n";
  std::cout << lastEl << (findRemove.find(lastEl) ? " was " : " was not ") << "found\n\n\n";
#endif // TEST_FIND


#ifdef TEST_LARGEST
  const int LARGE_COUNT = 8;
  std::cout << "TESTING findLargest and removeLargest\n\n";

  ArrayInt findLarge;
  int largeVals[LARGE_COUNT] = {3, 11, 19, 7, 5, 2, 13, 23};
  for (int i = 0; i < LARGE_COUNT; i++) {
    findLarge.append(largeVals[i]);
  }

  std::cout << "Array contains " << findLarge.listElements() << "\n";

  std::cout << "Largest should be 23 and is " << findLarge.findLargest() << "\n";

  findLarge.removeLargest();
  findLarge.removeLargest();
  std::cout << "After removing two largest should be: 3 11 7 5 2 13\n";
  std::cout << "                         actually is:" << findLarge.listElements() << "\n";

  std::cout << "Emptying array\n";
  for (int i = 0; i < LARGE_COUNT - 2; i++) {
    findLarge.deleteLast();
  }

  std::cout << "\nNow testing findLargest on empty array\n";
  try {
    findLarge.findLargest();
    std::cout << "Should have thrown an exception\n";
  } catch (std::out_of_range &ex) {
    std::cout << "Caught out of range with message: " << ex.what();
  } catch (...) {
    std::cout << "Caught something weird\n\n";
  }

  std::cout << "\nNow testing removeLargest on empty array\n";
  try {
    findLarge.removeLargest();
    std::cout << "Should have thrown an exception\n";
  } catch (std::out_of_range &ex) {
    std::cout << "Caught out of range with message: " << ex.what() << "\n";
  } catch (...) {
    std::cout << "Caught something weird\n\n\n";
  }
#endif // TEST_LARGEST


#ifdef TEST_INSERT_REMOVE
  const int BEGIN = 10;
  std::cout << "\n\nTESTING insertAt and removeAt\n\n";

  int insRemVals[BEGIN];
  readInVals(insRemVals, BEGIN, 3);
  ArrayInt insertRemove;
  for (int i = 0; i < BEGIN; i++) {
    insertRemove.append(insRemVals[i]);
  }

  std::cout << "Array starting with: ";
  std::cout << insertRemove.listElements();
  std::cout << "\nSize should be " << BEGIN << " and is " << insertRemove.getSize() << "\n\n";

  std::cout << "Now inserting 5 at index 2\n";
  insertRemove.insertAt(2, 5);
  std::cout << "Size should be " << 2 * BEGIN << " and is " << insertRemove.getSize() << "\n";
  std::cout << "  After INSERT AT expected:";
  for (int i=0; i<2; i++) std::cout << " " << insRemVals[i];
  std::cout << " 5";
  for (int i=2; i<BEGIN; i++) std::cout << " " << insRemVals[i];
  std::cout << "\n  After INSERT AT actually:";
  std::cout << insertRemove.listElements() << "\n\n";

  std::cout << "Trying to remove values at indices: 8 2 0\n" 
            << "                           Removed: ";
  std::cout << insertRemove.removeAt(8) << " ";
  std::cout << insertRemove.removeAt(2) << " ";
  std::cout << insertRemove.removeAt(0) << "\n";

  std::cout << "  After REMOVE AT expected:";
  for (int i=1; i<7; i++) std::cout << " " << insRemVals[i];
  for (int i=8; i<BEGIN; i++) std::cout << " " << insRemVals[i];
  std::cout << "\n  After REMOVE AT actually:";
  std::cout << insertRemove.listElements();

  std::cout << "\n\nNow testing illegal inserts and removes\n";
  std::cout << "Testing invalid insertAt at index larger than array size\n";
  try {
    insertRemove.insertAt(BEGIN * 3, 500);
    std::cout << "Should have thrown an exception inserting at " << BEGIN * 3 << "\n";
  } catch (std::out_of_range &ex) {
    std::cout << "Caught out of range with message: " << ex.what();
  } catch (...) {
    std::cout << "Caught something weird\n";
  }

  std::cout << "\nTesting invalid insertAt at negative index\n";
  try {
    insertRemove.insertAt(-1, 500);
    std::cout << "Should have thrown an exception inserting at -1\n";
  } catch (std::out_of_range &ex) {
    std::cout << "Caught out of range with message: " << ex.what() << "\n";
  } catch (...) {
    std::cout << "Caught something weird\n";
  }

  std::cout << "\nEmptying the array, expecting:";
  for (int i=BEGIN-1; i>7; i--) std::cout << " " << insRemVals[i]; 
  for (int i=6; i>0; i--) std::cout << " " << insRemVals[i];
  std::cout << "\n  Actually removed the values:";
  for (int i = 0; i < BEGIN-2; i++) {
    std::cout << " " << insertRemove.getLast();
    insertRemove.deleteLast();
  }
  std::cout << "\n\nNow testing removeAt on empty array\n";
  try {
    insertRemove.removeAt(0);
    std::cout << "Should have thrown an exception\n";
  } catch (std::out_of_range &ex) {
    std::cout << "Caught out of range with message: " << ex.what() << "\n";
  } catch (...) {
    std::cout << "Caught something weird\n\n\n";
  }
#endif // TEST_INSERT_REMOVE


#ifdef TEST_MIX
  std::cout << "\n\nTESTING a mixture of appends, insertAts, and removeAts\n";

  ArrayInt mixed;

  mixed.append(2);
  mixed.append(4);
  mixed.append(6);
  mixed.deleteLast();
  mixed.append(50000);
  mixed.insertAt(0, 16);
  mixed.append(32);
  mixed.insertAt(2, 19);
  mixed.append(256);
  mixed.removeLargest();
  mixed.append(64);
  mixed.removeAt(4);

  std::cout << "Displaying the results\n";
  std::cout << "  After MIX expected: 16 2 19 4 256 64\n";
  std::cout << "  After MIX actually:" << mixed.listElements();

  std::cout << "\nDone testing mixed\n\n\n";
#endif // TEST_MIX


#ifdef TEST_THINK
  std::cout << "TESTING the thinking problem\n";

  ArrayInt think;
  const int NUM_THINK = 10;
  int thinkVals[NUM_THINK];
  readInVals(thinkVals, NUM_THINK, 4);

  std::sort(thinkVals, thinkVals + NUM_THINK, std::greater<int>());
  std::cout << "  After THINK expected:";
  for (int i=0; i<NUM_THINK; i++) std::cout << " " << thinkVals[i];
  std::cout << "\n";

  think.solveThink(thinkVals, NUM_THINK);
  std::cout << "  After THINK actually:" << think.listElements();
  std::cout << "\nDone with thinking test\n\n";
#endif // TEST_THINK

  return 0;
}


// Read numElems values form inf and store them in arr
void readInVals(int* arr, int numElems, int skipLines) {
  std::ifstream inputFile("input");
  if (!inputFile) {
    std::cerr << "Error opening file!\n";
    exit(1);
  }

  // Skip the specified number of lines
  std::string temp;
  for (int i = 0; i < skipLines; i++) {
    if (!std::getline(inputFile, temp)) {
      std::cerr << "Error: Reached end of file while skipping lines!\n";
      exit(1);
    }
  }

  // Read values into the array
  for (int i = 0; i < numElems; i++) {
    if (!(inputFile >> arr[i])) {
      std::cerr << "Error reading values from file!\n";
      exit(1);
    }
  }

  inputFile.close();
}
