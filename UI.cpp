#pragma once
#include "UI.h"
string UI::getFileName(char& mode)
    {
        cout << "Enter file name (without extension): ";
        string name;
        cin >> name;
        cout << "what to mode you want (s) for silent: ";
        cin >> mode;
        return name;
    }

void UI::printConsle(int timestep,
        const LinkedQueue<Patient*>& Patients,
        const LinkedQueue<Resources*>& X_Deivces,
        const LinkedQueue<Resources*>& E_Devices,
        const LinkedQueue<Resources*>& U_Deivces,
        const PriorityQueueRescheduling& Early_Patients,
        const priQueue<Patient*>& Late_Patients,
        const ArrayStack<Patient*>& Finished_Patients,
        const priQueue<Patient*>& In_Treatment,
        const QueueSorted& U_Waiting_Patients,
        const QueueSorted& E_Waiting_Patients,
        const QueueSortedWithCancel& X_Waiting_Patients) const
    {
        cout << "Current Timestep: " << timestep << endl;
        cout << "================= ALL List =================" << endl;

        int patientCount = Patients.GetCount();
        cout << patientCount << " patients remaining: ";

        LinkedQueue<Patient*> tempPatients = Patients;
        Patient* tempPatient;

        int printCount = min(10, patientCount);
        for (int i = 0; i < printCount; i++) {
            if (tempPatients.dequeue(tempPatient)) {
                cout << "P" << tempPatient->getPID() << "_" << tempPatient->getVT();
                if (i < printCount - 1) cout << ", ";
            }
        }

        cout << "\n================ Waiting Lists ================" << endl;
        cout << E_Waiting_Patients.GetCount() << " E-therapy patients: ";
        E_Waiting_Patients.PrintQueue();
        cout << endl;

        cout << U_Waiting_Patients.GetCount() << " U-therapy patients: ";
        U_Waiting_Patients.PrintQueue();
        cout << endl;

        cout << X_Waiting_Patients.GetCount() << " X-therapy patients: ";
        X_Waiting_Patients.PrintQueue();
        cout << endl;

        cout << "================= Early List =================" << endl;
        cout << Early_Patients.GetCount() << " patients: ";
        Early_Patients.PrintPriQueue();
        cout << endl;

        cout << "================= Late List =================" << endl;
        cout << Late_Patients.GetCount() << " patients: ";
        Late_Patients.PrintPriQueue();
        cout << endl;

        cout << "================ Avail E-devices ================" << endl;
        int eCount = E_Devices.GetCount();
        cout << eCount << " Electro device: ";
        E_Devices.PrintQueue();
        cout << endl;

        cout << "================ Avail U-devices ================" << endl;
        int uCount = U_Deivces.GetCount();
        cout << uCount << " Ultra device: ";
        U_Deivces.PrintQueue();
        cout << endl;

        cout << "================ Avail X-rooms ================" << endl;
        int xCount = X_Deivces.GetCount();
        cout << xCount << " rooms: ";
        X_Deivces.PrintQueue();
        cout << endl;

        cout << "============== In-treatment List ================" << endl;
        int inTreatmentCount = In_Treatment.GetCount();
        cout << inTreatmentCount << " ==> ";
        In_Treatment.PrintPriQueue();

        cout << "\n------------------------------------------------" << endl;

        int finishedCount = Finished_Patients.GetCount();
        cout << finishedCount << " finished patients: ";
        Finished_Patients.PrintStack();

        cout << "Press any key to display next timestep" << endl;
        cin.ignore();
    }

string UI::outputfile()
    {
        string filename;

        cout << "Enter file name (without extension): ";
        cin >> filename;
        filename = "output/" + filename + ".txt";
        return filename;
    }

