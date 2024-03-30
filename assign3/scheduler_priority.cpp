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

bool comparePriority(PCB& pcb1, PCB& pcb2) {
    if (pcb1.priority == pcb2.priority) {
        // If priorities are equal, compare process numbers in descending order
        return pcb1.id < pcb2.id;
    }
    // Compare priorities in ascending order
    return pcb1.priority > pcb2.priority;
}

bool compareId(const PCB& pcb1, const PCB& pcb2) {
    return pcb1.id < pcb2.id;
}

void SchedulerPriority::simulate() {
    std::sort(this->process_list.begin(), this->process_list.end(), comparePriority );


    unsigned int  waitTime = 0;

    for(PCB& pcb : this->process_list){
        cout<<"Running Process "<< pcb.name <<" for "<<pcb.burst_time<<" time units"<<endl;
        pcb.arrival_time = waitTime;
        waitTime += pcb.burst_time;
        pcb.burst_time = waitTime;

    }
}

void SchedulerPriority::print_results() {
//    for(const PCB& pcb : this->process_list){
//        // Accumulate total turnaround time
//        this->tTime += pcb.burst_time;
//
//        // Accumulate total waiting time
//        this->wTime += pcb.arrival_time;
//
//        // Print turnaround time and waiting time for the process
//        cout << pcb.name << " turn-around time = " << pcb.burst_time << ", waiting time " << pcb.arrival_time << endl;
//    }
//
//    // Calculate and print average turn-around time and average waiting time
//    double avg_turnaround_time = this->tTime / this->process_list.size();
//    double avg_waiting_time = this->wTime / this->process_list.size();
//    cout << "Average turn-around time = " << avg_turnaround_time << ", Average waiting time = " << avg_waiting_time << endl;
//}

// Sort the process_list by id
    std::sort(this->process_list.begin(), this->process_list.end(), compareId);

    for(const PCB& pcb : this->process_list){
        // Accumulate total turnaround time
        this->tTime += pcb.burst_time;

        // Accumulate total waiting time
        this->wTime += pcb.arrival_time;

        // Print turnaround time and waiting time for the process
        cout << pcb.name << " turn-around time = " << pcb.burst_time << ", waiting time " << pcb.arrival_time << endl;
    }

    // Calculate and print average turn-around time and average waiting time
    double avg_turnaround_time = this->tTime / this->process_list.size();
    double avg_waiting_time = this->wTime / this->process_list.size();
    cout << "Average turn-around time = " << avg_turnaround_time << ", Average waiting time = " << avg_waiting_time << endl;
}
