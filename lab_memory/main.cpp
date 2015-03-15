#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

#include "fileio.h"
#include "letter.h"
#include "room.h"
#include "allocator.h"

using namespace std;

/**
 * Main routine.
 * Creates an Allocator object and allocates the students
 */
int main()
{
	cout << endl;
	//cout << "1" << endl;
	fileio::init();
	//cout << "2" << endl;
	//problem goes here,->
	Allocator theAllocator("students.txt", "rooms.txt");
	//cout << "2" << endl;
	theAllocator.allocate();
	//cout << "2" << endl;
	theAllocator.printRooms();
	fileio::halt();
	//cout << endl;
	return 0;
}
