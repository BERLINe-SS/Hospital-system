#include "Resources.h"

// Define static variables for Gym, ETherapy, and UTherapy
#include <iostream> // Include the iostream header for cout
using namespace std;
//Resources::Resources() {};
Type Resources::getType() const
{
	return type;
}
bool Resources::isFull() const {
	return attachedPatientsCount == cap;
}
bool Resources::incAttachedPatientsCount() {
	if (attachedPatientsCount < cap) {
		attachedPatientsCount++;
		return true;
	}
	else {
		return false;
	}
}
bool Resources::decAttachedPatientsCount() {
	if (attachedPatientsCount > 0) {
		attachedPatientsCount--;
		return true;
	}
	else {
		return false;
	}
}
int Resources::getCap() const
{
	return cap;
}
void Resources::printForResources() const
{
	if (type == G)
		cout << "R" << this->ID << "[" << attachedPatientsCount << "," << cap << "]";
	else if (type == E)
		cout << "E" << this->ID;
	else if (type == U)
		cout << "U" << this->ID;
}

void Resources::printForPatient() const
{
	if (type == G)
		cout << "R" << this->ID;
	else if (type == E)
		cout << "E" << this->ID;
	else if (type == U)
		cout << "U" << this->ID;
}

std::ostream& operator<<(ostream& os, const Resources* p)
{
	p->printForResources();
	return os;
}