#pragma once
#include "Music.h"
#include <iomanip>
#include <string.h>

class Physical : public Music
{
public:
	Physical(int i, string n, string a, float p, string t);
	void displayInfo() override;  // custom display for physical records
};
