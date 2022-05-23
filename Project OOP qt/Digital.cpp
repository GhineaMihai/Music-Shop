#include "Digital.h"

Digital::Digital(int i, string n, string a, float p, string x) : Music(i, n, a, p, x)
{

}

void Digital::displayInfo()
{
	cout << left << setw(20) << this->m_id << setw(20) << this->m_name << setw(20) << this->m_artist << setw(20) << this->m_price << endl;
	cout << left << "Digital code: " << this->m_type << endl;
	cout << endl;
}