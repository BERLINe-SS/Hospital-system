#pragma once
#include <iostream>
#include "UTherapyTreatment.h"
#include "ETherapyTreatment.h"
#include "XTherapyTreatment.h"
#include "LinkedQueue.h"
using namespace std;
enum Patient_status { IDLE, ERLY, LATE, WAIT, SERV, FNSH };

class Patient
{
	static int PIDs;
	int PID;
	bool typeN; // true is normal  //false for recovering
	int PT;		// Appointment time
	int VT;		// Arrival time
	int FT;		// Finish time
	int TW;		// Total waiting time for this patient
	int TT;		// Total treatment time for this patient
	int XT;
	int numRes;
	LinkedQueue<Treatment*> RequiredTreatements; // for the time needed for each treatment
	Patient_status PS;
	bool canceled;// Whether doing an accepted cancel	
	bool rescheduled;// Whether doing an accepted reschedule
public:

	Patient(char type, int p, int v);
	bool isCanceled() const;
	bool isRescheduled() const;
	void setCanceled();
	void setRescheduled();
	bool canReschedule() const;
	void setFT(int t);
	int getFT() const;
	int getTT() const;
	int getcurrentTimeStep(int timeStep) const;
	int getfinalTW() const;
	void incPT(int k);
	int getPID() const;
	void decTT();
	int getPT() const;
	Patient_status getPS() const;
	int getVT() const;
	void setE();
	void setL();
	void setW();
	void setS();
	void setF();
	bool istypeN() const;
	bool istypeR() const;
	bool isEarly();
	bool isLate();
	float getWaitTimeOfPatient() const;
	int getWaitOfFirstRequired();
	float getservingT() const;
	bool removeFirstRequired(Treatment*& R);
	bool getFirstRequired(Treatment*& R);
	bool canCancel();
	void addAttachedResource(Resources*& t);
	Resources*& getAttachedResource();
	void addTreat(int s, char t);
	LinkedQueue<Treatment*> getRequiredTreatements();
	void removeTreat(Treatment* T);
	void addTreatFirst(Treatment* T);
	void Print() const;
};
ostream& operator<<(ostream& os, const Patient* p);
