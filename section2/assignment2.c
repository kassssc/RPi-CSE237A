#include "assignment1.h"
#include "assignment2.h"
#include "workload.h"
#include "scheduler.h"
#include "governor.h"
#include <stdio.h>

// Note: Deadline of each workload is defined in the "workloadDeadlines" variable.
// i.e., You can access the dealine of the BUTTON thread using workloadDeadlines[BUTTON]
// See also deadlines.c and workload.h

// Assignment: You need to implement the following two functions.

// learn_workloads(SharedVariable* v):
// This function is called at the start part of the program before actual scheduling
// - Parameters
// sv: The variable which is shared for every function over all threads
void learn_workloads(SharedVariable* sv) {
	// TODO: Fill the body
	// This function is executed before the scheduling simulation.
	// You need to calculate the execution time of each thread here.

	// Thread functions for workloads:
	// thread_button, thread_twocolor, thread_temp, thread_track,
	// thread_touch, thread_rgbcolor, thread_aled, thread_buzzer

	// Tip 1. You can call each workload function here like:
	// thread_button();

	// Tip 2. You can get the current time here like:
	// long long curTime = get_current_time_us();

	long long start_time, end_time, dur;
	int i;
	for (i = 0; i < 8; i++) {
		sv->avg_runtime[i] = 0;
	}

	for (i = 0; i < 15; i++) {
		// Button
		start_time = get_current_time_us();
		thread_button(sv);
		end_time = get_current_time_us();
		dur = end_time - start_time;
		sv->avg_runtime[0] += dur;
//		printf("button thread: %lld\n", dur);

		// Three Color
		start_time = get_current_time_us();
		thread_threecolor(sv);
		end_time = get_current_time_us();
		dur = end_time - start_time;
		sv->avg_runtime[1] += dur;
//		printf("RGB thread: %lld\n", dur);

		// Big
		start_time = get_current_time_us();
		thread_big(sv);
		end_time = get_current_time_us();
		dur = end_time - start_time;
		sv->avg_runtime[2] += dur;
//		printf("big thread: %lld\n", dur);

		// Small
		start_time = get_current_time_us();
		thread_small(sv);
		end_time = get_current_time_us();
		dur = end_time - start_time;
		sv->avg_runtime[3] += dur;
//		printf("small thread: %lld\n", dur);

		// Touch
		start_time = get_current_time_us();
		thread_touch(sv);
		end_time = get_current_time_us();
		dur = end_time - start_time;
		sv->avg_runtime[4] += dur;
//		printf("touch thread: %lld\n", dur);

		// RGB Color
		start_time = get_current_time_us();
		thread_rgbcolor(sv);
		end_time = get_current_time_us();
		dur = end_time - start_time;
		sv->avg_runtime[5] += dur;
//		printf("SMD RGB thread: %lld\n", dur);

		// ALED
		start_time = get_current_time_us();
		thread_aled(sv);
		end_time = get_current_time_us();
		dur = end_time - start_time;
		sv->avg_runtime[6] += dur;
//		printf("ALED thread: %lld\n", dur);

		// Buzzer
		start_time = get_current_time_us();
		thread_buzzer(sv);
		end_time = get_current_time_us();
		dur = end_time - start_time;
		sv->avg_runtime[7] += dur;
//		printf("buzzer thread: %lld\n", end_time - start_time);
	}

	for (i = 0; i < 8; i++) {
		sv->avg_runtime[i] = (sv->avg_runtime[i] / 10.0) * 1.1;
		printf("AVG runtime %d = %d\n", i, sv->avg_runtime[i]);
	}
}


// select_task(SharedVariable* sv, const int* aliveTasks):
// This function is called while runnning the actual scheduler
// - Parameters
// sv: The variable which is shared for every function over all threads
// aliveTasks: an array where each element indicates whether the corresponed task is alive(1) or not(0).
// idleTime: a time duration in microsecond. You can know how much time was waiting without any workload
//           (i.e., it's larger than 0 only when all threads are finished and not reache the next preiod.)
// - Return value
// TaskSelection structure which indicates the scheduled task and the CPU frequency
TaskSelection select_task(SharedVariable* sv, const int* aliveTasks, long long idleTime) {
	// TODO: Fill the body
	// This function is executed inside of the scheduling simulation.
    // You need to implement an energy-efficient EDF (Earliest Deadline First) scheduler.

	// Tip 1. You may get the current time elapsed in the scheduler here like:
	// long long curTime = get_scheduler_elapsed_time_us();

	// Also, do not make any interruptable / IO tasks in this function.
	// You can use printfDBG instead of printf.

	/*
	// Sample scheduler: Round robin
	// It selects a next thread using aliveTasks.
	static int prev_selection = -1;

	int i = prev_selection + 1;
	while(1) {
		if (i == NUM_TASKS)
			i = 0;

		if (aliveTasks[i] == 1) {
			prev_selection = i;
			break;
		}
		++i;
	}

	// The retun value can be specified like this:
	TaskSelection sel;
	sel.task = prev_selection; // The thread ID which will be scheduled. i.e., 0(BUTTON) ~ 7(BUZZER)
	sel.freq = 1; // Request the maximum frequency (if you want the minimum frequency, use 0 instead.)

  return sel;
	*/

  long long earliest_deadline = 9223372036854775807; // max long long value
  int chosen = -1;
  int i;
  for (i = 0; i < 8; i++) {
  	if (aliveTasks[i]) {

  		// If a task missed its deadline, schedule immediately
  		if (get_scheduler_elapsed_time_us() > workloadDeadlines[i]) {
  			chosen = i;
  			break;
  		}
  		if (workloadDeadlines[i] < earliest_deadline) {
  			chosen = i;
  			earliest_deadline = workloadDeadlines[chosen];
  		}
  	}
  }

  if (chosen == -1) {
  	// No alive tasks
  }

  //last_scheduled_task = chosen;
  TaskSelection sel;
	sel.task = chosen;
	sel.freq = 1;

	return sel;
}
