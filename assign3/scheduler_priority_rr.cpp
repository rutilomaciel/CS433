/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author Rutilo Maciel and Alvaro Espinoza Merida
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_priority_rr.h"
#include <algorithm>

// TODO: add implementation of SchedulerPriorityRR constructor, destructor and
// member functions init, print_results, and simulate here

SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum){
    // Initialize any member variables specific to SchedulerPriorityRR if needed
    this->time_quantum = time_quantum;
    this->tTime = 0;
    this->wTime = 0;
}

// Destructor
SchedulerPriorityRR::~SchedulerPriorityRR() {}


void SchedulerPriorityRR::init(std::vector<PCB>& process_list) {
    this->process_list = process_list;
}

// Function to print simulation results
void SchedulerPriorityRR::print_results() {
    for(PCB pcb : this->process_list){

        this->tTime+= pcb.burst_time;
        this->wTime += pcb.arrival_time;

        cout<<pcb.name <<" turn-around time = "<< pcb.burst_time<< ", waiting time = "<< pcb.arrival_time <<endl;
    }
    cout<<"Average turn-around time = "<< this->tTime / this->process_list.size() << ", Average waiting time = "<< this->wTime / this->process_list.size() <<endl;
}

// Function to simulate the scheduling of processes
void SchedulerPriorityRR::simulate() {
    unsigned int waitTime = 0; // Initialize wait time
    int count = 112; // Counter for simulation steps

    int current = 0; // Track current process in the list
    bool allComplete = false; // Flag for total process completion

    // Loop until all processes are complete
    while (!allComplete) {
        // Current process
        PCB* pcb = &this->process_list[current];

        // Execute based on time quantum or burst time
        if (this->time_quantum <= pcb->burst_time) {
            cout << "Running Process " << pcb->name << " for " << this->time_quantum << " time units" << endl;
            pcb->burst_time -= this->time_quantum;
            waitTime += this->time_quantum;
        } else {
            cout <<"Running Process " << pcb->name << " for " << pcb->burst_time << " time units" << endl;
            waitTime += pcb->burst_time;
            pcb->burst_time = 0;
        }

        // Move to next process in the list
        current++;
        if (current >= this->process_list.size()) {
            current = 0;
        }

        // Check for process completion
        allComplete = true;
        for (const PCB& process : this->process_list) {
            if (process.burst_time > 0) {
                allComplete = false;
                break;
            }
        }

        count++; // Increment simulation step counter
    }
}