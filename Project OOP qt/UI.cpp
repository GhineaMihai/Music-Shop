#include "UI.h"
#include <iostream>
using namespace std;

void UI::display()
{
	cout << "1. Add music to the repository" << endl;
	cout << "2. Remove music from the repository" << endl;
	cout << "3. Print the repository" << endl;
	cout << "4. Print either physical or digital types of music" << endl;
	cout << "5. Undo" << endl;
	cout << "6. Redo" << endl;
	cout << "7. Load csv" << endl;
	cout << "8. Save csv" << endl;
	cout << "0. Stop" << endl;
}

UI::UI()
{
	this->R = new Repository();
}

UI::~UI()
{

}

void UI::run()
{
	int y = 0;
	int id = 0;
	this->R->load();
	while (true)
	{
		this->display();
		int x;
		cin >> x;
		if (x == 1)
		{
			y = 1;
			string name, artist, type;
			float price;
			id++;
			cout << "Give the name of the record " << endl;
			cin >> name;
			cout << "Give the name of the artist " << endl;
			cin >> artist;
			cout << "Give the price of the record " << endl;
			cin >> price;
			cout << "Give the type of the record if it is physical (cd, vynil, tape) (must be lowercase) or the code of the record if it is digital (a 12 character combination)" << endl;
			cin >> type;
			bool ok = 0;
			while (ok == 0)
			{
				if (type == "cd" || type == "vynil" || type == "tape")
				{
					Physical *z = new Physical(id, name, artist, price, type);
					ok = 1;
					this->R->add(z);
				}

				if (size(type) == 12)
				{
					Digital *z = new Digital(id, name, artist, price, type);
					ok = 1;
					this->R->add(z);
				}
				
				if (ok == 0)
				{
					cout << "Type either the physical types (cd, vynil, tape) or the digital 12 character code " << endl;
					cin >> type;
				}
			}
		}
		if (x == 2)
		{
			y = 2;
			int z;
			cout << "Give the id of the record you want to remove " << endl;
			cin >> z;
			this->R->remove(z);
			id--;
		}
		if (x == 3)
		{
			this->R->displayall();
		}
		if (x == 4)
		{
			string z;
			cout << "Choose what record you want to print (Physical or Digital)" << endl;
			cin >> z;
			while (true)
			{
				if (z == "Physical" || z == "physical")
					this->R->displayallPhysical();
				if (z == "Digital" || z == "digital")
					this->R->displayallDigital();
				if (!(z == "Physical" || z == "physical" || z == "Digital" || z == "digital"))
				{
					cout << "Type Physical or Digital" << endl;
					cin >> z;
				}
				else
					break;
			}
		}
		if (x == 5) 
		{
			if (y == 1)
			{
				this->R->undoadd();
				y = 5;
			}
			if (y == 2)
			{
				this->R->undoremove();
				y = 6;
			}
		}
		if (x == 6)
		{
			if (y == 5)
			{
				this->R->redoadd();
				y = 1;
			}
			if (y == 6)
			{
				this->R->redoremove();
				y = 2;
			}
		}
		if (x == 7)
		{
			this->R->load();
			cout << "Loaded from file Load.csv" << endl;
		}
		if (x == 8)
		{
			this->R->save();
			cout << "Saved in file Save.csv" << endl;
		}
		if (x == 0)
		{
			this->R->save();
			break;
		}

	}
}