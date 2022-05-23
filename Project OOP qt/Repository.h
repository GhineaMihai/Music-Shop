#pragma once
#include "Music.h"
#include "Physical.h"
#include "Digital.h"
#include <iostream>
#include <exception>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
using namespace std;
class Repository
{
public:
	Repository();  // default contructor
	Repository(const Repository& other);  // copy constructor
	virtual ~Repository();  // destructor
	void add(Music* x);  // add a record to the repository
	void remove(int y);  // remove a record from the repository by id
	void undoadd();  // undos and redos are specific for the add and remove functions and are called accordingly
	void undoremove();  // undos and redos are specific for the add and remove functions and are called accordingly
	void redoadd();  // undos and redos are specific for the add and remove functions and are called accordingly
	void redoremove();  // undos and redos are specific for the add and remove functions and are called accordingly
	virtual void displayall();  //print repository
	void load();  // load from the Load.csv file
	void save();  // save to the Save.csv file
	void displayallPhysical();  // dispplay only physical record
	void displayallDigital();  // display only digital records
public:
	Music** data;
	int firstEmpty, pos;  // pos and firstEmpty are useful for the add and remove functions
	Music* removed;  // removed is used for the redo functions
};

