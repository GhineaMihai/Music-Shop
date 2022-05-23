#pragma once
#include <iostream>
#include <string.h>
#include <string>
using namespace std;
class Music
{
public:
	Music();  // default contructor
	Music(int i, string n, string a, float p, string x);  // parameter contructor
	Music(const Music& other);  // copy constructor
	Music& operator=(const Music& other);  // assignment operator
	virtual ~Music();  // destructor
	virtual void displayInfo();  // display
public:
	int m_id;
	string m_name, m_artist;
	float m_price;
	string m_type;
};

