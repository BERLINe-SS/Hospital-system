#pragma once
#include "Treatment.h"
class XTherapyTreatment : public Treatment {
public:
	XTherapyTreatment(int duration);
	virtual bool CanAssign(Scheduler* s);
	virtual void MoveToWait(Scheduler* s, Patient* p, int t);
};

