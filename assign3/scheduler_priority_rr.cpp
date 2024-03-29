/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author ??? (TODO: your name)
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
}

// Destructor
SchedulerPriorityRR::~SchedulerPriorityRR() {}

//bool SchedulerPriorityRR::comparePriority(const PCB& pcb1, const PCB& pcb2) {
//    return (pcb1.priority < pcb2.priority);
//}

void SchedulerPriorityRR::init(std::vector<PCB>& process_list) {
    this->process_list = process_list;
}

// Function to print simulation results
void SchedulerPriorityRR::print_results() {
    Scheduler::print_results();
}

// Function to simulate the scheduling of processes
void SchedulerPriorityRR::simulate() {
    std::sort(this->process_list.begin(), this->process_list.end(), comparePriority);

    unsigned int waitTime = 0;

    for (PCB& pcb : this->process_list) {
        cout << "Running Process " << pcb.name << " for " << pcb.burst_time << " time units | wait time:" << waitTime << endl;
        pcb.arrival_time = waitTime;
        waitTime += pcb.burst_time;
        pcb.burst_time = waitTime;
    }
}