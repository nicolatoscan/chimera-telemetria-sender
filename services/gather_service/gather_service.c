#include "gather_service.h"

void gatherSetup() {
    condition.structure.flush_toilet = 1;
    condition.structure.toggle_state = 0;
    condition.structure.data_head = gatherCreateData();
    condition.structure.data_tail = NULL;

    pthread_mutex_init(&condition.structure.threads.data_head_mutex, NULL);
    pthread_mutex_init(&condition.structure.threads.data_tail_mutex, NULL);
    pthread_mutex_init(&condition.structure.threads.flush_toilet_mutex, NULL);
    pthread_mutex_init(&condition.structure.threads.toggle_state_mutex, NULL);
    pthread_cond_init(&condition.structure.threads.flush_toilet_cond, NULL);
    pthread_cond_init(&condition.structure.threads.toggle_state_cond, NULL);
}

void gatherResetDataId() {
    condition.structure.id = 0;
}