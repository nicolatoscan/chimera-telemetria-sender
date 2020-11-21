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
    while (!condition.structure.toggle_state && end - start < condition.structure.sending_rate);
}

void gatherMasterSwap() {
    pthread_mutex_lock(&condition.structure.threads.data_head_mutex);
    pthread_mutex_lock(&condition.structure.threads.data_tail_mutex);

    condition.structure.data_head->timestamp = gatherGetCurrentTimestamp();
    condition.structure.data_head->sessionName = condition.mongodb.instance->session_name;
    condition.structure.data_head->id = condition.structure.id++;

    swapPointers(&condition.structure.data_head, &condition.structure.data_tail);

    pthread_mutex_unlock(&condition.structure.threads.data_head_mutex);
    pthread_mutex_unlock(&condition.structure.threads.data_tail_mutex);
}

void gatherMasterEnableFlushToilet() {
    pthread_mutex_lock(&condition.structure.threads.flush_toilet_mutex);
    condition.structure.flush_toilet = 1;
    pthread_cond_signal(&condition.structure.threads.flush_toilet_cond);
    pthread_mutex_unlock(&condition.structure.threads.flush_toilet_mutex);
}

/* INTERNAL FUNCTIONS DEFINITIONS */

static double getMillisecondsFromTimespec(struct timespec time) {
    return (double) (time.tv_sec * 1000 + 1.0E-6 * time.tv_nsec);
}