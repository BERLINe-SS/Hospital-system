#include "ETherapyTreatment.h"
#include "Scheduler.h"
ETherapyTreatment::ETherapyTreatment(int duration) : Treatment(duration)
{}
bool ETherapyTreatment ::CanAssign(Scheduler* s)
{
	return s->getCount_E() > 0;
}
void ETherapyTreatment :: MoveToWait(Scheduler * s,Patient* p,int t) {
	s->AddToWait_E(t,p);
}
