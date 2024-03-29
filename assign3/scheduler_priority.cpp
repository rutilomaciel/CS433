/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author ??? (TODO: your name)
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code


#include "scheduler_priority.h"

// TODO: add implementation of SchedulerPriority constructor, destrcutor and 
// member functions init, print_results, and simulate here

SchedulerPriority::SchedulerPriority() {
    tTime = 0.0;
    wTime = 0.0;
}

SchedulerPriority::~SchedulerPriority()  {}

void SchedulerPriority::init(std::vector<PCB>& process_list) {
    this->process_list = process_list;
}

void SchedulerPriority::simulate() {
//    std::sort(this->process_list.begin(), this->process_list.end(), comparePriority);
//    unsigned int waitTime = 0;
//
//    for (PCB& pcb : this->process_list) {
//        cout << "Running Process " << pcb.name << " for " << pcb.burst_time << " time units | wait time:" << waitTime << endl;
//        pcb.arrival_time = waitTime;
//        waitTime += pcb.burst_time;
//        pcb.burst_time = waitTime;
//    }
}

void SchedulerPriority::print_results() {}