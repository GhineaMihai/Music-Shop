#include "Music.h"
#include <iomanip>

Music::Music()
{
	this->m_id = 0;
	this->m_name = ' ';
	this->m_artist = ' ';
	this->m_price = 0;
	this->m_type = ' ';
}

Music::Music(int i, string n, string a, float p, string x)
{
	this->m_id = i;
	this->m_name = n;
	this->m_artist = a;
	this->m_price = p;
	this->m_type = x;
}

Music::Music(const Music& other)
{
	this->m_id = other.m_id;
	this->m_name = other.m_name;
	this->m_artist = other.m_artist;
	this->m_price = other.m_price;
	this->m_type = other.m_type;
}

Music& Music::operator=(const Music& other)
{
	if (this != &other)
	{
		this->m_id = other.m_id;
		this->m_name = other.m_name;
		this->m_artist = other.m_artist;
		this->m_price = other.m_price;
		this->m_type = other.m_type;
	}
	return *this;
}

void Music::displayInfo()
{
	cout << left << setw(3) << this->m_id << setw(20) << this->m_name << setw(20) << this->m_artist << setw(20) << this->m_price << endl;  // using setw to allign the text 
}

Music::~Music()
{

}