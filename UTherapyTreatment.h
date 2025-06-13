#pragma once
#include "Treatment.h"

class UTherapyTreatment : public Treatment
{
public:
	UTherapyTreatment(int duration);
	virtual bool CanAssign(Scheduler* s);
	virtual void MoveToWait(Scheduler* s, Patient* p, int t);
};
