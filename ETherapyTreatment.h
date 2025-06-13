#pragma once
#include "Treatment.h"
class ETherapyTreatment : public Treatment {
public:
	ETherapyTreatment(int duration);
	virtual bool CanAssign(Scheduler* s);
	virtual void MoveToWait(Scheduler* s, Patient* p, int t);
};

