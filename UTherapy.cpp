#include "UTherapy.h"
UTherapy ::UTherapy() {
		cap = 1;
		type = U;
		ID = nextID++;
}

int UTherapy::nextID = 1;

