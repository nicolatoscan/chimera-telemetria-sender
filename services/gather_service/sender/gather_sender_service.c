#include "gather_sender_service.h"

/* INTERNAL VARIABLES AND STRUCTS */

pthread_t gather_sender_thread;
pthread_attr_t gather_sender_thread_attr;

/* INTERNAL FUNCTIONS SIGNATURES */

static void* senderSend(void *args);

/* EXPORTED FUNCTIONS */

void gatherSenderStartThread() {
	pthread_attr_init(&gather_sender_thread_attr);
	pthread_attr_setdetachstate(&gather_sender_thread_attr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&gather_sender_thread, &gather_sender_thread_attr, &senderSend, NULL);
	pthread_attr_destroy(&gather_sender_thread_attr);
}

void gatherSenderStopThread() {
	pthread_cancel(gather_sender_thread);
}

/* INTERNAL FUNCTIONS DEFINITIONS */

static void* senderSend(void *args) {
    while (1) {
        // Waits until it must flush the toilet
        debugGeneric("{SENDER} Waiting for flushing toilet");
        pthread_mutex_lock(&condition.structure.threads.flush_toilet_mutex);
        while (!condition.structure.flush_toilet) {
            pthread_cond_wait(&condition.structure.threads.flush_toilet_cond, &condition.structure.threads.flush_toilet_mutex);
        }
        condition.structure.flush_toilet = 0;
        pthread_mutex_unlock(&condition.structure.threads.flush_toilet_mutex);

        // Locks data_tail
        debugGeneric("{SENDER} Locking data tail");
        pthread_mutex_lock(&condition.structure.threads.data_tail_mutex);

        if (condition.structure.data_tail != NULL) {
            // Get the bson document from data_tail
            debugGeneric("{SENDER} Creating bson document");
            bson_t* bson_document;  
            gatherDataToBson(condition.structure.data_tail, &bson_document);

            // Sends the data over mosquitto
            debugGeneric("{SENDER} Sending over mosquitto");
            mosquittoSend(bson_document);
            // TODO: mongo

            // Destroys the bson document
            debugGeneric("{SENDER} Destroying bson document");
            bson_destroy(bson_document);

            // Deletes the data_tail document and replaces it with a new one
            debugGeneric("{SENDER} Deleting data tail");
            gatherDeleteData(condition.structure.data_tail);
        }

        // Resets the data_tail document and replaces it with a new one
        debugGeneric("{SENDER} Resetting data tail");
        condition.structure.data_tail = gatherCreateData();

        // Unlocks data tail
        debugGeneric("{SENDER} Unlocking data tail");
        pthread_mutex_unlock(&condition.structure.threads.data_tail_mutex);
    }
}

