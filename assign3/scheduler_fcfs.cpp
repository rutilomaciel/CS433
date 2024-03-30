/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Rutilo Maciel and Alvaro Espinoza Merida
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_fcfs.h"

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here


//Constructor and Destructor
SchedulerFCFS::SchedulerFCFS() {}
SchedulerFCFS::~SchedulerFCFS() {}

//Initialize the process list
void SchedulerFCFS::init(std::vector<PCB> &process_list) {
    this->process_list = process_list;
}

void SchedulerFCFS::simulate() {

    //Initialize waitTime variable for processes
    unsigned int waitTime = 0;

    /*
     * Iterate through the process list and print the running process with burst time.
     * Update the arrival time and burst time of each process.
     */
    for(PCB& pcb : this->process_list) {
        cout<<"Running Process "<< pcb.name <<" for "<<pcb.burst_time<<" time units"<<endl;
        pcb.arrival_time = waitTime;
        waitTime += pcb.burst_time;
        pcb.burst_time = waitTime;
    }
}

//Iterate and print each process with turn-around time and waiting time.
//Also, calculating the average turn-around time and waiting time of the processes.
void SchedulerFCFS::print_results() {
    for(PCB pcb : this->process_list){

        this->tTime+= pcb.burst_time;
        this->wTime += pcb.arrival_time;

        cout<<pcb.name <<" turn-around time = "<< pcb.burst_time<< ", waiting time = "<< pcb.arrival_time <<endl;
    }
    cout<<"Average turn-around time = "<< this->tTime / this->process_list.size() << ", Average waiting time = "<< this->wTime / this->process_list.size() <<endl;
}