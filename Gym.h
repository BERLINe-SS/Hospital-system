#pragma once
#include "Resources.h"
class Gym : public Resources
{
private:
	static int nextID;
public:
	Gym();
	Gym(int c);
	void setCap(int n);
	int getnumber();
};

