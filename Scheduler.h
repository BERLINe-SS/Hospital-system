#pragma once
#include <iostream>
#include <ctime>
#include "LinkedQueue.h"
#include "priQueue.h"
#include "patient.h"
#include "ArrayStack.h"
#include "PriorityQueueRescheduling.h"
#include "QueueSorted.h"
#include "QueueSortedWithCancel.h"
#include <fstream>
#include <string>
#include "UI.h"


using namespace std;


class Scheduler
{
private:
	LinkedQueue<Patient*>  All_Patients;
	PriorityQueueRescheduling Early_Patients;
	priQueue<Patient*>  Late_Patients;
	LinkedQueue<Resources*>  E_Devices;
	LinkedQueue<Resources*>  U_Devices;
	LinkedQueue<Resources*>  X_Devices;
	priQueue<Patient*>  In_Treatment;
	ArrayStack<Patient*>  Finished_Patients;
	QueueSorted U_Waiting_Patients;
	QueueSorted E_Waiting_Patients;
	QueueSortedWithCancel X_Waiting_Patients;
	UI ui;
	int PCancel;
	int PReschedule;
public:
	// Functions here
	int getCount_X();
	int getCount_E();
	int getCount_U();
	void AddToWait_U(int timestep, Patient* P);
	void AddToWait_E(int timestep, Patient* P);
	void AddToWait_X(int timestep, Patient* P);
	void ReadInput(string filename);
	void RP(int timestep, Patient*& P, Treatment*& T);
	void simulation();
	void MakeOutFile(string filename, int timestep);
	void AddToEL(Patient* P);
	void AddToWFromEL(int times,Patient* P);
	void AssignX(Patient* P2, Treatment * T,int times);
	void AssignE(Patient* P2, Treatment* T, int times);
	void AssignU(Patient* P2, Treatment* T, int times);
	void AddToFWFromInTreat(int times, Patient* P2);
	~Scheduler();
};
