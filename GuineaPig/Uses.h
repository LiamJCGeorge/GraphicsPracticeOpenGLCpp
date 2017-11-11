#pragma once
#include "Singleton.h"


class Uses
{
private:
	Singleton& _p;
public:
	Uses(Singleton& p);
	void doStuff();
};

