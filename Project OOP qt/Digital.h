#pragma once
#include "Music.h"
#include <iomanip>
#include <string.h>

class Digital : public Music
{
public:
	Digital(int i, string n, string a, float p, string c);
	void displayInfo() override;  // custom display for digital records
};