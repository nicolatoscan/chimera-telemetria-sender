#include "gather_service.h"

void gatherSetup() {
    condition.structure.flush_toilet = false;
    condition.structure.toggle_state = 0;
    condition.structure.data_head = gatherCreate();
    condition.structure.data_tail = NULL;

    pthread_mutex_init(&condition.structure.threads.data_head_mutex, NULL);
    pthread_mutex_init(&condition.structure.threads.data_tail_mutex, NULL);
    pthread_mutex_init(&condition.structure.threads.flush_toilet_mutex, NULL);
    pthread_mutex_init(&condition.structure.threads.toggle_state_mutex, NULL);
    pthread_cond_init(&condition.structure.threads.flush_toilet_cond, NULL);
    pthread_cond_init(&condition.structure.threads.toggle_state_cond, NULL);
}

data_t* gatherCreateData() {
	data_t* data = (data_t*) malloc(sizeof(data_t));
	data->steering_wheel.marker = 0;
	// {{GENERATE_STRUCTURE_ALLOCATOR}}
	return data;
}

void gatherDataToBson(data_t *data, bson_t** bson_document) {
	//{{GENERATE_BSON}}
}

void gatherDeleteData(data_t *data) {
	//{{GENERATE_STRUCTURE_DEALLOCATOR}}
}

void gatherResetDataId() {
    condition.structure.id = 0;
}