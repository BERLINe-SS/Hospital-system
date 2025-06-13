#pragma once


#include "LinkedQueue.h"
#include "priQueue.h"
#include "patient.h"
#include "ArrayStack.h"
#include "PriorityQueueRescheduling.h"
#include "QueueSorted.h"
#include "QueueSortedWithCancel.h"
#include "Resources.h"
	
class UI
{
public:
    string getFileName(char& mode);

    void printConsle(int timestep,
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
        const QueueSortedWithCancel& X_Waiting_Patients) const;
    string outputfile();
};
