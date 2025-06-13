#include "Gym.h"
Gym::Gym() {
		type = G;
		cap = 0;
		ID = nextID++;
	}// Default constructor
Gym::Gym(int c) {
	setCap(c);
	type = G;
}
void Gym::setCap(int n)
{
	if (n > 0)
		cap = n;
	else
		cap = 0;
}
int Gym::nextID = 1;
int Gym::getnumber()
{
	return attachedPatientsCount;
}

