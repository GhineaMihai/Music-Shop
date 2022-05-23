#include "Physical.h"

Physical::Physical(int i, string n, string a, float p, string x) : Music(i, n, a, p, x)
{

}

void Physical::displayInfo()
{
	cout << left << setw(20) << this->m_id << setw(20) << this->m_name << setw(20) << this->m_artist << setw(20) << this->m_price << endl;
	cout << left << "It is a " << this->m_type << endl;
	cout << endl;
}