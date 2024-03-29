/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author ??? (TODO: your name)
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
//

#include "scheduler_rr.h"

// TODO: add implementation of SchedulerRR constructor, destrcutor and 
// member functions init, print_results, and simulate here

SchedulerRR::SchedulerRR(int time_quantum) : time_quantum(time_quantum){}

SchedulerRR::~SchedulerRR() {}

void SchedulerRR::init(std::vector<PCB>& process_list) {
    for (PCB& pcb : process_list) {
        ready_queue.push(pcb);
    }
}

void SchedulerRR::print_results() {}

void SchedulerRR::simulate() {
    unsigned int waitTime = 0;

    for (PCB& pcb : this->process_list) {
        cout << "Running Process " << pcb.name << " for " << pcb.burst_time << " time units | wait time:" << waitTime << endl;
        pcb.arrival_time = waitTime;
        waitTime += pcb.burst_time;
        pcb.burst_time = waitTime;
    }
}
