#pragma once
#include "Gym.h"
#include "ETherapy.h"
#include "UTherapy.h"
class Scheduler;
class Patient;
class Treatment {
protected:
	int duration;
	int assignmenttime;
	Resources* assignedResource;
	Type t;
public:
	Treatment(int duration);
	int getDuration() const;
	void setDuration(int d);
	Resources*& getAssignedResource();
	void setAssignedResource(Resources*& r);
	void setTypet(Type t);
	Type getTypet();
	virtual bool CanAssign(Scheduler* s) = 0;
	virtual void MoveToWait(Scheduler* s, Patient* p, int t) = 0;
};
