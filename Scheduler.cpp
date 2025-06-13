#pragma once
#include "Scheduler.h"
#include <iostream>



using namespace std;
	// Functions here
	int Scheduler::getCount_X()
	{
		return X_Devices.GetCount();
	}
	int Scheduler::getCount_E()
	{
		return E_Devices.GetCount();
	}
	int Scheduler::getCount_U()
	{
		return U_Devices.GetCount();
	}

	void Scheduler::AddToWait_U(int timestep, Patient* P)
	{
		P->setW();
		U_Waiting_Patients.insertSorted(-timestep, P);
	}

	void Scheduler::AddToWait_E(int timestep, Patient* P)
	{
		P->setW();
		E_Waiting_Patients.insertSorted(-timestep, P);
	}

	void Scheduler::AddToWait_X(int timestep, Patient* P)
	{
		P->setW();
		X_Waiting_Patients.insertSorted(-timestep, P);
	}
	void Scheduler::AddToEL(Patient* P) {
		All_Patients.dequeue(P);
		if (P->getVT() <= P->getPT())
		{
			P->setE();
			Early_Patients.enqueue(P, -P->getservingT());
		}
		else if (P->getVT() > P->getPT())
		{
			P->setL();
			Late_Patients.enqueue(P, -P->getservingT());
		}
	}
	void Scheduler::AddToWFromEL(int times, Patient* P) {
		Treatment* T = nullptr;
		if (P->istypeN()) {
			P->getFirstRequired(T);
			T->MoveToWait(this, P, times);
		}
		else if (P->istypeR()) {// to be edited
			P->getFirstRequired(T);
			if (T) {
				P->setW();
				RP(times, P, T);
			}
		}
	}




	void Scheduler::AssignX(Patient* P2, Treatment* T,int times) {
		Resources* R = nullptr;
		X_Waiting_Patients.dequeue(P2);
		P2->setS();
		X_Devices.peek(R);
		R->incAttachedPatientsCount();
		if (R->isFull()) {
			X_Devices.dequeue(R);
		}
		P2->addAttachedResource(R);
		In_Treatment.enqueue(P2, -times - (T->getDuration()));
	}



	void Scheduler::AssignE(Patient* P2, Treatment* T, int times) {
		Resources* R = nullptr;
		E_Waiting_Patients.dequeue(P2);
		P2->setS();
		E_Devices.dequeue(R);
		R->incAttachedPatientsCount();
		P2->addAttachedResource(R);
		In_Treatment.enqueue(P2, -times - (T->getDuration()));
	}



	void Scheduler::AssignU(Patient* P2, Treatment* T, int times) {
		Resources* R = nullptr;
		U_Waiting_Patients.dequeue(P2);
		P2->setS();
		U_Devices.dequeue(R);
		R->incAttachedPatientsCount();
		P2->addAttachedResource(R);
		In_Treatment.enqueue(P2, -times - (T->getDuration()));
	}



	void Scheduler::AddToFWFromInTreat(int times, Patient* P) {
		Treatment* T = nullptr;
		Resources* R = nullptr;
		R = P->getAttachedResource();
		if (R->getType() == G) {
			if (R->isFull()) {
				X_Devices.enqueue(R);
			}
			R->decAttachedPatientsCount();
		}
		else if (R->getType() == E) {
			R->decAttachedPatientsCount();
			E_Devices.enqueue(R);
		}
		else if (R->getType() == U) {
			R->decAttachedPatientsCount();
			U_Devices.enqueue(R);
		}
		if (P->istypeN()) {
			P->removeFirstRequired(T);
			P->getFirstRequired(T);
			if (T) {
				T->MoveToWait(this, P, times);
			}
			else {
				P->setF();
				P->setFT(times);
				Finished_Patients.push(P);
			}
		}
		else if (P->istypeR()) {// to be edited
			P->removeFirstRequired(T);
			P->getFirstRequired(T);
			if (T) {
				P->setW();
				RP(times, P, T);
			}
			else {
				P->setF();
				P->setFT(times);
				Finished_Patients.push(P);
			}
		}
	}




	void Scheduler::ReadInput(string filename)
	{


		filename = "input files\\" + filename + ".txt";

		ifstream inFile(filename);
		if (!inFile.is_open())
		{
			cout << "Error: could not open input file.\n";
			exit(555);
		}

		int eCount, uCount, xCount;
		inFile >> eCount >> uCount >> xCount;

		for (int i = 0; i < eCount; i++)
			E_Devices.enqueue(new ETherapy());

		for (int i = 0; i < uCount; i++)
			U_Devices.enqueue(new UTherapy());

		for (int i = 0; i < xCount; ++i)
		{
			int cap;
			inFile >> cap;

			Gym* g = new Gym();
			g->setCap(cap);
			X_Devices.enqueue(g);
		}

		inFile >> PCancel >> PReschedule;

		int patientCount;
		inFile >> patientCount;

		for (int i = 0; i < patientCount; ++i)
		{
			char type;
			int pt, vt;
			inFile >> type >> pt >> vt;

			Patient* p = new Patient(type, pt, vt);

			int numberofTreatments;
			inFile >> numberofTreatments;

			for (int i = 0; i < numberofTreatments; ++i)
			{
				char type0fTreatments;
				int numberofSteps;
				inFile >> type0fTreatments >> numberofSteps;
				//  Required Treatements on progress......
				p->addTreat(numberofSteps, type0fTreatments);
			}

			All_Patients.enqueue(p);
		}

		inFile.close();
		cin.ignore();
	}


	void Scheduler::RP(int timestep, Patient*& P, Treatment*& T)
	{
		LinkedQueue<Treatment*> dummy = P->getRequiredTreatements();
		LinkedQueue<Treatment*> dummy2 = dummy;
		Treatment* T2;
		int count = dummy.GetCount();

		if (count == 1)
		{
			T->MoveToWait(this, P, timestep);
			return;
		}
		int x = 0, y = 0, z = 0;
		while (!dummy2.isEmpty())
		{
			dummy2.dequeue(T);
			if (T->getTypet() == E)
			{
				x = E_Waiting_Patients.calcTreatmentLatency();
			}
			if (T->getTypet() == U)
			{
				y = U_Waiting_Patients.calcTreatmentLatency();
			}
			if (T->getTypet() == G)
			{
				z = X_Waiting_Patients.calcTreatmentLatency();
			}
		}
		if (count == 2)
		{
			while (!dummy.isEmpty())
			{
				dummy.dequeue(T);
				if (T->getTypet() == E && (x <= y || x <= z))
				{
					P->setW();
					P->removeTreat(T);
					P->addTreatFirst(T);
					T->MoveToWait(this, P, timestep);
					return;
				}
				else if (T->getTypet() == U && (y <= x || y <= z))
				{
					P->setW();
					P->removeTreat(T);
					P->addTreatFirst(T);
					T->MoveToWait(this, P, timestep);
					return;
				}
				else if (T->getTypet() == G && (z <= y || z <= x))
				{
					P->setW();
					P->removeTreat(T);
					P->addTreatFirst(T);
					T->MoveToWait(this, P, timestep);
					return;
				}
			}
		}
		else if (count == 3)
		{
			while (!dummy.isEmpty())
			{
				dummy.dequeue(T);
				if (T->getTypet() == E && x <= y && x <= z)
				{
					P->setW();
					P->removeTreat(T);
					P->addTreatFirst(T);
					T->MoveToWait(this, P, timestep);
					return;
				}
				else if (T->getTypet() == U && y <= x && y <= z)
				{
					P->setW();
					P->removeTreat(T);
					P->addTreatFirst(T);
					T->MoveToWait(this, P, timestep);
					return;
				}
				else if (T->getTypet() == G && z <= y && z <= x)
				{
					P->setW();
					P->removeTreat(T);
					P->addTreatFirst(T);
					T->MoveToWait(this, P, timestep);
					return;
				}
			}
		}
	}

	void Scheduler::simulation()
	{
		char mode;
		string filename;
		filename = ui.getFileName(mode);
		ReadInput(filename);
		int timestep = 0;
		int c = All_Patients.GetCount();
		Patient* P;
		Patient* P2;
		Treatment* T;
		srand(time(0));
		int Finished_PatientsCount = Finished_Patients.GetCount();

		while (c != Finished_PatientsCount && c > Finished_PatientsCount)
		{
			P = nullptr;
			P2 = nullptr;
			T = nullptr;
			int dummy;

			while (All_Patients.peek(P) && P->getVT() == timestep) {//entering early or late list case
				AddToEL(P);
			}

			int X = rand() % 101;
			if (X < PCancel)//cancel case
			{
				if (X_Waiting_Patients.cancel2(P))
				{
					P->setF();
					P->setCanceled();
					P->decTT();
					P->setFT(timestep);
					Finished_Patients.push(P);
				}
			}

			X = rand() % 101;
			if (X < PReschedule)//reschedule case
			{
				if (Early_Patients.Reschedule(P)) {
					P->setRescheduled();
				}
			}

			while (Early_Patients.peek(P, dummy) && P->getservingT() <= timestep) {//going out of early to waiting
				Early_Patients.dequeue(P, dummy);
				AddToWFromEL(timestep,P);
			}

			while (Late_Patients.peek(P, dummy) && (P->getservingT()) <= timestep) {//going out of late to waiting
				Late_Patients.dequeue(P, dummy);
				AddToWFromEL(timestep - (P->getVT() - P->getPT()),P);
			}

			while (In_Treatment.peek(P, dummy) && (-dummy) <= timestep) { //going out of In_treatment to Finish or Waiting List
				In_Treatment.dequeue(P, dummy);
				AddToFWFromInTreat(timestep, P);
			}

			while (E_Waiting_Patients.peek(P2) && P2->getFirstRequired(T) && T->CanAssign(this)) { //going out of E_waiting to In_treatment
				AssignE(P2, T, timestep);
			}

			while (U_Waiting_Patients.peek(P2) && P2->getFirstRequired(T) && T->CanAssign(this)) {//going out of U_waiting to In_treatment
				AssignU(P2, T, timestep);
			}

			while (X_Waiting_Patients.peek(P2) && P2->getFirstRequired(T) && T->CanAssign(this)) {//going out of X_waiting to In_treatment
				AssignX(P2,T,timestep);
			}


			if (mode != 's')
			{
				//system("cls"); //if we wanted to clear the console
				ui.printConsle(timestep, All_Patients, X_Devices, E_Devices, U_Devices, Early_Patients, Late_Patients, Finished_Patients, In_Treatment, U_Waiting_Patients, E_Waiting_Patients, X_Waiting_Patients);
			}
			timestep++;
			Finished_PatientsCount = Finished_Patients.GetCount();
		}
		timestep--;
		filename = ui.outputfile();
		MakeOutFile(filename, timestep);

	}

	void Scheduler::MakeOutFile(string filename, int timestep)
	{
		ofstream outFile(filename);
		if (!outFile) {
			cout << "Error creating file!" << endl;
			return;
		}


		outFile << "PID  PType PT   VT   FT   WT   TT   Cancel Resc" << endl;
		float totalnumber, Nnumber, Rnumber, Wall, WR, WN, Tall, TN, TR, accCP, accRP, Pearly, Plate, latePen;

		totalnumber = Nnumber = Rnumber = Wall = WR = WN = Tall = TN = TR = accCP = accRP = Pearly = Plate = latePen = 0;

		while (!Finished_Patients.isEmpty())
		{
			Patient* temp;
			Finished_Patients.pop(temp);

			if (temp->getPID() < 10)
			{
				outFile << "P" << temp->getPID() << "   ";
			}
			else if (temp->getPID() < 100)
			{
				outFile << "P" << temp->getPID() << "  ";
			}
			else
			{
				outFile << "P" << temp->getPID() << " ";
			}
			if (temp->istypeN())
				outFile << "N" << "     ";
			if (temp->istypeR())
				outFile << "R" << "     ";

			if (temp->getPT() < 10)
			{
				outFile << temp->getPT() << "    ";
			}
			else if (temp->getPT() < 100)
			{
				outFile << temp->getPT() << "   ";
			}
			else if (temp->getPT() < 1000)
			{
				outFile << temp->getPT() << "  ";
			}
			else
			{
				outFile << temp->getPT() << " ";
			}

			if (temp->getVT() < 10)
			{
				outFile << temp->getVT() << "    ";
			}
			else if (temp->getVT() < 100)
			{
				outFile << temp->getVT() << "   ";
			}
			else if (temp->getVT() < 1000)
			{
				outFile << temp->getVT() << "  ";
			}
			else
			{
				outFile << temp->getVT() << " ";
			}

			if (temp->getFT() < 10)
			{
				outFile << temp->getFT() << "    ";
			}
			else if (temp->getFT() < 100)
			{
				outFile << temp->getFT() << "   ";
			}
			else if (temp->getFT() < 1000)
			{
				outFile << temp->getFT() << "  ";
			}
			else
			{
				outFile << temp->getFT() << " ";
			}

			if (temp->getfinalTW() < 10)
			{
				outFile << temp->getfinalTW() << "    ";
			}
			else if (temp->getfinalTW() < 100)
			{
				outFile << temp->getfinalTW() << "   ";
			}
			else if (temp->getfinalTW() < 1000)
			{
				outFile << temp->getfinalTW() << "  ";
			}
			else
			{
				outFile << temp->getfinalTW() << " ";
			}

			if (temp->getTT() < 10)
			{
				outFile << temp->getTT() << "    ";
			}
			else if (temp->getTT() < 100)
			{
				outFile << temp->getTT() << "   ";
			}
			else if (temp->getTT() < 1000)
			{
				outFile << temp->getTT() << "  ";
			}
			else
			{
				outFile << temp->getTT() << " ";
			}

			if (temp->isCanceled())
			{
				outFile << "T      ";
				++accCP;
			}
			else
			{
				outFile << "F      ";
			}
			if (temp->isRescheduled())
			{
				outFile << "T\n";
				++accRP;
			}
			else
			{
				outFile << "F\n";
			}

			++totalnumber;
			Wall += temp->getfinalTW();
			Tall += temp->getTT();
			if (temp->istypeN())
			{
				++Nnumber;
				WN += temp->getfinalTW();
				TN += temp->getTT();
			}
			else
			{
				++Rnumber;
				WR += temp->getfinalTW();
				TR += temp->getTT();
			}

			if (temp->isEarly())
				++Pearly;
			else if (temp->isLate())
			{
				++Plate;
				latePen += temp->getWaitTimeOfPatient();
			}


		}

		Wall /= totalnumber;
		Tall /= totalnumber;

		WN /= Nnumber;
		TN /= Nnumber;

		WR /= Rnumber;
		TR /= Rnumber;

		accCP = accCP / totalnumber * 100;
		accRP = accRP / totalnumber * 100;

		if (Plate != 0)
			latePen /= Plate;
		else
			latePen = 0;

		Pearly = Pearly / totalnumber * 100;
		Plate = Plate / totalnumber * 100;


		outFile << "\nTotal number of timesteps = " << timestep << endl;
		outFile << "Total number of All, N, R = " << totalnumber << ", " << Nnumber << ", " << Rnumber << endl;
		outFile << "Average total waiting time of All, N, R = " << Wall << ", " << WN << ", " << WR << endl;   // wrong logic
		outFile << "Average total treatment time  of All, N, R = " << Tall << ", " << TN << ", " << TR << endl; // wrong logic
		outFile << "Percentage of patients that accepted cancellation (%) = " << accCP << " %\n";
		outFile << "Percentage of patients that accepted rescheduling (%) = " << accRP << " %\n";

		outFile << "Percentage of early patients (%) = " << Pearly << " %\n";
		outFile << "Percentage of late patients (%) = " << Plate << " %\n";
		outFile << "Average late penalty = " << latePen << " timestep(s)\n";

		outFile.close();

		cout << "\nFile created at: " << filename << endl << endl;

		return;
	}

	Scheduler::~Scheduler() {};

