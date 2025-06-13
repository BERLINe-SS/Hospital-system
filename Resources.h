#pragma once
#include <iostream> // Include the iostream header for cout
using namespace std;
enum Type { G, E, U }; //G for Gym, E for ETherapy, U for UTherapy;

class Resources
{
protected:
	int cap;
	int attachedPatientsCount = 0; // Number of patients attached to the gym
	int ID;
	Type type;
public:
	virtual Type getType() const;
	bool isFull() const;
	bool incAttachedPatientsCount();
	bool decAttachedPatientsCount();
	int getCap() const;
	virtual void printForResources() const;
	virtual void printForPatient() const;
};
ostream& operator<<(ostream& os, const Resources* p);