#include "XTherapyTreatment.h"
#include "Scheduler.h"

XTherapyTreatment::XTherapyTreatment(int duration) : Treatment(duration){}
bool XTherapyTreatment::CanAssign(Scheduler* s)
{
	return s->getCount_X() > 0;
}
void XTherapyTreatment::MoveToWait(Scheduler* s, Patient* p,int t) {
	s->AddToWait_X(t,p);
}