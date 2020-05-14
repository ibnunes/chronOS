//------------------------------------------------------------------------------
//
// chronOS - A scheduling simulator
//
//    Copyright (C) 2020 Igor Cordeiro Bordalo Nunes (www.igornunes.com)
//    Copyright (C) 2020 Jorge Miguel Louro Pissarra
//    Copyright (C) 2020 Diogo Castanheira Simões
//    Copyright (C) 2020 Universidade da Beira Interior (www.ubi.pt)
//
// RUNTIME LIBRARIES PACKAGE
//    fcfs.h
//
// DESCRIPTION:
// -----------
// First Come First Serve algorithm.
//------------------------------------------------------------------------------

#include "fcfs.h"

/*
1-  Input the processes along with their burst time (bt).

2-  Find waiting time (wt) for all processes.

3-  As first process that comes need not to wait so
    waiting time for process 1 will be 0 i.e. wt[0] = 0.

4-  Find waiting time for all other processes i.e. for
                    process i -> wt[i] = bt[i-1] + wt[i-1] .

5-  Find turnaround time = waiting_time + burst_time for all processes.

6-  Find average waiting time = total_waiting_time / no_of_processes.

7-  Similarly, find average turnaround time = total_turn_around_time / no_of_processes.

*/


int fcfs(process p, int burst_time) {
    return 0;
}

void findWaitingTime(void) {

}
