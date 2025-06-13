#include "Treatment.h"
#include "Scheduler.h"

Treatment::Treatment(int duration){
	this->duration = duration;
	assignmenttime = 0;
	assignedResource = nullptr;
}
int Treatment::getDuration() const {
	return duration;
}
Resources*& Treatment::getAssignedResource() {
	return assignedResource;
}
void Treatment::setAssignedResource(Resources*& r) {
	assignedResource = r;
}
void Treatment::setTypet(Type t) {
	this->t = t;
}
Type Treatment::getTypet() {
	return t;
}
void Treatment::setDuration(int d) {
	duration = d;
}