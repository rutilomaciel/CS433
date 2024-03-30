/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Rutilo Maciel and Alvaro Espinoza Merida
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
//

#include "scheduler_rr.h"
#include <algorithm>

//Constructor and Destructor
SchedulerRR::SchedulerRR(int time_quantum){
    this->time_quantum = time_quantum; //Set time quantum for RR
    this->tTime = 0;
    this->wTime = 0;
}

SchedulerRR::~SchedulerRR() {}


//Initialize process list and wait queue
void SchedulerRR::init(std::vector<PCB>& process_list) {
    this->process_list = process_list;
    this->wait_queue = process_list;
}

//Checking for non-zero burst time
bool check_time(std::vector<PCB>& process_list){
    for(PCB& pcb : process_list){
        if(pcb.burst_time != 0 ){
            return true;
        }
    }
    return false;
}

void SchedulerRR::simulate() {

    unsigned int  waitTime = 0;
    int count = 112;

    int current = 0;

    bool allComplete = false;

    //We shouldn't erase any of the values from the list;
    //instead we should be checking once all the values  burst time variable has reached zero
    //create a function that goes through all the PCBs to see if they all have a burst time of zero
    //if we erase them from the wait queue the data from the original queue and the wait queue will be
    //desynced as they will be different sizes

    while(check_time(this->wait_queue )){

        PCB* pcb = &this->wait_queue[current]; //Current process

        //checks if we are at the end of the scheduler
        //get the current process
        //if the process has no current burst move onto the next part
        while(pcb->burst_time == 0){
            current += 1;
            if(current > this->wait_queue.size()-1){
                current = 0;
            }
            pcb = &this->wait_queue[current];
        }

        //subtract the time quantum as long as burst time is greater
        //else this implies that the burst time needs to be reduced by the remaining amount of time
        if (this->time_quantum <= pcb->burst_time){
            cout<<"Running Process "<< pcb->name <<" for "<<this->time_quantum<<" time units"<< endl;

            pcb->burst_time -= this->time_quantum;

            waitTime +=  this->time_quantum;
        }
        else{
            cout<<"Running Process "<< pcb->name <<" for "<<pcb->burst_time<<" time units"<< endl;
            waitTime += pcb->burst_time;
            pcb->burst_time = 0 ;
        }

        if(pcb->burst_time == 0){

            PCB* final_data = &this->process_list[current];

            final_data->arrival_time = waitTime - final_data->burst_time;
            final_data->burst_time = waitTime;
        }

        count += 1;
        current += 1;

        if(current > this->wait_queue.size()-1){
            current = 0;
        }
    }
}

//Print results by iterating through process list and display average turnaround time and wait time
void SchedulerRR::print_results() {
    for(PCB pcb : this->process_list){

        this->tTime+= pcb.burst_time;
        this->wTime += pcb.arrival_time;

        cout<<pcb.name <<" turn-around time = "<< pcb.burst_time<< ", waiting time = "<< pcb.arrival_time <<endl;
    }
    cout<<"Average turn-around time = "<< this->tTime / this->process_list.size() << ", Average waiting time = "<< this->wTime / this->process_list.size() <<endl;
}