#include "ETherapy.h"
ETherapy ::ETherapy() {
	cap = 1;
	type = E;
	ID = nextID++;
}
int ETherapy::nextID = 1;
