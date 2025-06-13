#include "patient.h"

// Define static variable for Patient
int Patient::PIDs = 0;

Patient::Patient(char type, int p, int v) {
		PID = ++PIDs;
		if (type == 'N' || type == 'n') {
			typeN = true;
		}
		else if (type == 'R' || type == 'r') {
			typeN = false;
		}
		PT = p;
		VT = v;
		FT = 0;
		TW = 0;
		TT = 0;
		numRes=0;
		canceled = false;
		rescheduled = false;
		PS = IDLE;
	}
bool Patient::isCanceled() const {
		return canceled;
	}
bool Patient::isRescheduled() const {
		return rescheduled;
	}
void Patient::setCanceled() {
		canceled = true;
	}
bool Patient::canReschedule() const {
	if (VT < PT && numRes < 3) {
		return true;
	}
	else return false;
}
void Patient::setRescheduled() {
	numRes++;
		rescheduled = true;
	}
void Patient::setFT(int t) {
		FT = t;
	}
int Patient::getFT() const {
		return FT;
	}
int Patient::getTT() const { // right logic
		return TT;
	}
int Patient::getcurrentTimeStep(int timeStep) const {
		return timeStep - VT;
	}
int Patient::getfinalTW() const { // wrong logic
		return FT - VT - TT;
	}
void Patient::incPT(int k) {
		PT = PT + k;
	}
int Patient::getPID() const {
		return PID;
	}
void Patient::decTT() {
		TT = TT - XT;
	}
int Patient::getPT() const {
		return PT;
	}
Patient_status Patient::getPS() const {
		return PS;
	}
int Patient::getVT() const {
		return VT;
	}
void Patient::setE() {
		PS = ERLY;
	}
void Patient::setL() {
		PS = LATE;
	}
void Patient::setW() {
		PS = WAIT;
	}
void Patient::setS() {
		PS = SERV;
	}
void Patient::setF() {
		PS = FNSH;
	}
bool Patient::istypeN() const {
		return typeN;
	}
bool Patient::istypeR() const {
		return !typeN;
	}
bool Patient::isEarly()
	{
		return VT < PT;
	}
bool Patient::isLate()
	{
		return VT > PT;
	}
float Patient::getWaitTimeOfPatient() const {
		if (VT <= PT)
			return PT - VT;
		else
			return 0.5 * (VT - PT);
	}
int Patient::getWaitOfFirstRequired() {
		Treatment* R;
		bool v = RequiredTreatements.peek(R);
		if (v) return R->getDuration();
		else return -1;
	}
float Patient::getservingT() const {
		if (PT >= VT)
			return PT;
		else
			return VT + 0.5 * (VT - PT);
	}
bool Patient::removeFirstRequired(Treatment*& R) {

		if (RequiredTreatements.isEmpty()) {
			return false;
		}
		else {
			RequiredTreatements.dequeue(R);
			return true;
		}
	}
bool Patient::getFirstRequired(Treatment*& R) {

		if (RequiredTreatements.isEmpty()) {
			R = nullptr;
			return false;
		}
		else {
			RequiredTreatements.peek(R);
			return true;
		}
	}
bool Patient::canCancel() {
		Treatment* r;
		RequiredTreatements.peek(r);
		if (RequiredTreatements.GetCount() == 1 && r->getTypet() == G) {
			return true;
		}
		else return false;
	}
void Patient::addAttachedResource(Resources*& t) {
		Treatment* temp;
		RequiredTreatements.peek(temp);
		temp->setAssignedResource(t);
	}
Resources*& Patient::getAttachedResource() {
		Treatment* temp;
		RequiredTreatements.peek(temp);
		return temp->getAssignedResource();
	}
void Patient::addTreat(int s, char t)
	{
		Treatment* temp;
		TT += s;
		switch (t)
		{
		case 'X': temp = new XTherapyTreatment(s); temp->setTypet(G); XT = s;  break;
		case 'E':  temp = new ETherapyTreatment(s); temp->setTypet(E); break;
		case 'U':  temp = new UTherapyTreatment(s); temp->setTypet(U); break;
		default:
			cout << "Invalid resource type character";
		}

		RequiredTreatements.enqueue(temp);
	}
LinkedQueue<Treatment*> Patient::getRequiredTreatements()
	{
		return RequiredTreatements;
	}
void Patient::removeTreat(Treatment* T)
	{
		if (RequiredTreatements.isEmpty())
		{
			return;
		}
		LinkedQueue<Treatment*> dummy;
		Treatment* T2;
		while (!RequiredTreatements.isEmpty())
		{
			RequiredTreatements.dequeue(T2);
			if (T2 != T)
			{
				dummy.enqueue(T2);
			}
		}
		while (!dummy.isEmpty())
		{
			dummy.dequeue(T2);
			RequiredTreatements.enqueue(T2);
		}
	}
void Patient::addTreatFirst(Treatment* T)
	{
		LinkedQueue<Treatment*> temp = RequiredTreatements;
		Treatment* T2;
		while (!RequiredTreatements.isEmpty())
		{
			RequiredTreatements.dequeue(T2);
		}
		RequiredTreatements.enqueue(T);
		while (!temp.isEmpty())
		{
			temp.dequeue(T2);
			RequiredTreatements.enqueue(T2);
		}
	}


void Patient::Print() const
	{
		if (PS == IDLE)
			cout << "P" << PID << "_" << VT;
		else if (PS == ERLY)
			cout << PID;
		else if (PS == LATE)
			cout << PID;
		else if (PS == WAIT)
			cout << PID;
		else if (PS == SERV) {
			Treatment* R;
			RequiredTreatements.peek(R);
			cout << "P" << PID << "_";
			R->getAssignedResource()->printForPatient();
		}
		else if (PS == FNSH)
			cout << PID;

	}
std::ostream& operator<<(ostream& os, const Patient* p)
{
	p->Print();
	return os;
}