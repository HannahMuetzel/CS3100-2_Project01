#pragma once
#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

static const int DEFAULT_CAP = 25;

template<class T> class MagicBag
{
public:

	MagicBag() {
		capacity = DEFAULT_CAP;
		size = 0;
		bag = new T[capacity];
	}
	
	// Copy constructor
	MagicBag(const MagicBag& copy) {
		*this = copy;
	}
	
	// Override the = operator
	MagicBag& operator=(const MagicBag& other) {
		// Set other's capacity, size, & bag to this's
		size = other.size;
		capacity = other.capacity;
		bag = new T[size];

		// Copy items of original bag into resized bag
		for (int i = 0; i < capacity; i++) {
			other.bag[i] = this->bag[i];
		}

		return *this;
	}
	
	// Destructor
	~MagicBag() {
		delete[] bag;
	}

	// Inserts an item into the MagicBag. If bag is full, increases capacity of bag.
	void insert(T item) {
		// If capacity = size, then bag is full.
		if (size == capacity)
			resize(capacity * 2);

		// Add item to bag, increase size by 1
		bag[size] = item;
		size++;
	}

	// Removes a random item from the bag. If bag is empty, throws an exception.
	T draw() {
		// Throws an exception if bag is empty
		if (size == 0) {
			throw(out_of_range(0));
			cout << "ERROR: There are no items in the bag.";
			abort();
		}

		// Generate random number, go to that location in the bag, and return that item
		int randnum;
		srand((unsigned int)time(NULL));
		randnum = rand() % size + 1;

		// Get random item
		T drawThis = bag[randnum - 1];
		// Overwrite item in random location with last item in bag
		bag[randnum - 1] = bag[size - 1];
		// Update number of items in bag counter
		size--;

		// Return the removed item
		return drawThis;
	}

	// Checks to see if passed item is in the bag. The number of matched items in the bag is returned.
	int peek(T item) {
		int inBag = 0;

		// Iterate through the bag, searching for item
		for (int i = 0; i < capacity; i++) {
			if (bag[i] == item)
				inBag++;
		}

		// Return number of times item was found (0 if not in bag)
		return inBag;
	}

private:

	//Private variables: MagicBag itself, capacity (max # of items in bag), size (actual # of items in bag)
	T* bag;
	int size;
	int capacity;

	// Resizes the bag, increasing the capacity in case bag is full
	void resize(int newCap) {
		// Update capacity and create empty bag in larger size
		capacity = newCap;
		T* newBag = new T[newCap];

		// Copy items of original bag into resized bag
		for (int i = 0; i < size; i++) {
			newBag[i] = bag[i];
		}

		// Set MagicBag to newBag
		this->bag = newBag;
	}

	// Overwrite << operator to print contents of MagicBag
	// Format: [item0, item1, item2, item3,...]
	friend ostream& operator<<(ostream& os, const MagicBag& mb) {
		os << "[";
		for (int i = 0; i < mb.size - 1; i++) {
			os << mb.bag[i] << ", ";
		}
		os << mb.bag[mb.size] << "]";
		return os;
	}
};