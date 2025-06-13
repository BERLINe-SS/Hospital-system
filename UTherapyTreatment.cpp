#include "UTherapyTreatment.h"
#include "Scheduler.h"
UTherapyTreatment::UTherapyTreatment(int duration) :Treatment(duration)
{}
bool UTherapyTreatment ::CanAssign(Scheduler* s)
{
	return s->getCount_U() > 0;
}
void UTherapyTreatment::  MoveToWait(Scheduler* s, Patient* p,int t) {
	s->AddToWait_U(t,p);
}
