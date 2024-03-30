/**
* Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Rutilo Maciel and Alvaro Espinoza Merida
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_sjf.h"

// TODO: add implementation of SchedulerSJF constructor, destrcutor and 
// member functions init, print_results, and simulate here

//Constructor and Destructor
SchedulerSJF :: SchedulerSJF() {}
SchedulerSJF :: ~SchedulerSJF(){}

//Comparing by burst time
bool comparePriority ( PCB& pcb1 ,PCB& pcb2 ) {
    if (pcb1.burst_time == pcb2.burst_time) {
        // If priorities are equal, compare process numbers in descending order
        return pcb1.id < pcb2.id;
    }
    // Compare priorities in ascending order by priority
    return pcb1.burst_time < pcb2.burst_time;
}

//Initialize process list
void SchedulerSJF :: init(std::vector<PCB>& process_list){
    this->process_list = process_list;
}

//Comparison function to sort by id
bool compareId(const PCB& pcb1, const PCB& pcb2) {
    return pcb1.id < pcb2.id;
}

void SchedulerSJF::simulate() {

    //Sort by burst time and print running process while updating arrival time
    // and burst time of each process
    std::sort(this->process_list.begin(), this->process_list.end(), comparePriority );

    unsigned int  waitTime = 0;

    for(PCB& pcb : this->process_list){
        cout<<"Running Process "<< pcb.name <<" for "<<pcb.burst_time<<" time units"<<endl;
        pcb.arrival_time = waitTime;
        waitTime += pcb.burst_time;
        pcb.burst_time = waitTime;
    }
}

//Print function displaying turnaround time and wait time with the averages of both at the end
void SchedulerSJF::print_results() {

    // Sort the process_list by id
    std::sort(this->process_list.begin(), this->process_list.end(), compareId);

    for(PCB pcb : this->process_list){

        this->tTime+= pcb.burst_time;
        this->wTime += pcb.arrival_time;

        cout<<pcb.name <<" turn-around time = "<< pcb.burst_time<< ", waiting time = "<< pcb.arrival_time <<endl;
    }

    cout<<"Average turn-around time = "<< this->tTime / this->process_list.size() << ", Average waiting time = "<< this->wTime / this->process_list.size() <<endl;

}