#include "gather_master_service.h"

/* INTERNAL FUNCTIONS SIGNATURES */

static double getMillisecondsFromTimespec(struct timespec time);

/* EXPORTED FUNCTIONS */

void gatherMasterWait() {
	// Init timer variables
    struct timespec t_start, t_end;
    double start, end;
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    start = getMillisecondsFromTimespec(t_start);

	do {
		// Get current millieseconds to check condition
        clock_gettime(CLOCK_MONOTONIC, &t_end);
        end = getMillisecondsFromTimespec(t_end);
    }
    while (!condition.structure.toggle_state || end - start < condition.structure.sending_rate);
}

void gatherMasterSwap() {
    data_t* temp = condition.structure.data_head;
    condition.structure.data_head = condition.structure.data_tail;
    condition.structure.data_tail = temp;
}

/* INTERNAL FUNCTIONS DEFINITIONS */

static double getMillisecondsFromTimespec(struct timespec time) {
    return (double) (time.tv_sec * 1000 + 1.0E-6 * time.tv_nsec);
}