#pragma once
#include "Repository.h"
#include "Music.h"

class UI
{
private:
	void display();
	Repository* R;
public:
	UI();
	~UI();

	void run();
};
