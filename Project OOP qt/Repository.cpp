#include "Repository.h"

Repository::Repository()  
{
	this->pos = 0;
	this->firstEmpty = 0;
	this->data = new Music*[100];
}

Repository::Repository(const Repository& other)
{
	this->pos = other.pos;
	this->firstEmpty = other.firstEmpty;
	this->data = new Music*[100];
	for (int i = 0; i < 100; i++)
		this->data[i] = other.data[i];
}

void Repository::add(Music* x)   // adds an element at the end of the repository
{
	if (x->m_price < 0)
		throw exception();
	this->data[this->firstEmpty] = x;
	this->firstEmpty++;  // increases the firstEmpty everytime an element is added
}

void Repository::remove(int y)  // searches for the id to be deleted if it is not found an exception is thrown, if there are 2 records with the same id, the first one is deleted
{
	int i = 0;
	bool ok = 0;
	while (i < this->firstEmpty && ok == 0)
	{
		if (y == this->data[i]->m_id)
			ok = 1;
		i++;
	}
	if (ok == 0)
		return;
	else
	{
		this->removed = this->data[i-1];
		this->pos = i - 1;

		for (int k = i; k < 100; k++)
			this->data[k - 1] = this->data[k];
		this->firstEmpty--;  // firstEmpty decreases every time an element is deleted
	}

}

void Repository::undoadd()
{
	remove(this->firstEmpty);
}
void Repository::undoremove()
{
	add(this->removed);
	for (int i = firstEmpty; i >= pos+1; i--)
		this->data[i] = this->data[i-1];
	this->data[pos] = this->data[firstEmpty];
}
void Repository::redoadd()
{
	add(this->removed);
}
void Repository::redoremove()
{
	remove(this->firstEmpty);
}

// undos and redos work for only one action

void Repository::displayall()  // displays the repository
{
	for (int i = 0; i < this->firstEmpty; i++)
		this->data[i]->displayInfo();
}

void Repository::displayallPhysical()  // displays only physiscal records
{
	for (int i = 0; i < this->firstEmpty; i++)
		if(this->data[i]->m_type == "cd" || this->data[i]->m_type == "vynil" || this->data[i]->m_type == "tape")
			this->data[i]->displayInfo();
}

void Repository::displayallDigital()  // displays only digital records
{
	for (int i = 0; i < this->firstEmpty; i++)
		if (this->data[i]->m_type != "cd" && this->data[i]->m_type != "vynil" && this->data[i]->m_type != "tape")
			this->data[i]->displayInfo();
}

void Repository::load()  // load gets the lines of the files one by one and uses ',' to choose the elements of the line one by one and the the last element is chosen if it has a "\n" after it
{
	while (firstEmpty != 0)
		remove(this->firstEmpty);
	bool found = false;
	string id, name, artist, price, t;
	ifstream f;
	f.open("Load.csv");
	while (getline(f, id, ',') && !found)
	{
		getline(f, name, ',');
		getline(f, artist, ',');
		getline(f, price, ',');
		getline(f, t, '\n');
		if (t == "cd" || t == "vynil" || t == "tape")
		{
			Physical *x = new Physical(stoi(id), name, artist, stof(price), t);
			add(x);
		}

		else
		{
			Digital *x = new Digital(stoi(id), name, artist, stof(price), t);
			add(x);
		}
		// we check if the read element is a digital record or a physical record and add it to the repository accordingly
	}

}

void Repository::save() // save just writes the elements of the repository delimited by ',' and with a "\n" at the end
{
	ofstream f;
	f.open("Save.csv");
	for (int i = 0; i < this->firstEmpty; i++)
		f << this->data[i]->m_id << ',' << this->data[i]->m_name << ',' << this->data[i]->m_artist << ',' << this->data[i]->m_price << ',' << this->data[i]->m_type << "\n";
}

Repository::~Repository()
{
	delete[] data;
}