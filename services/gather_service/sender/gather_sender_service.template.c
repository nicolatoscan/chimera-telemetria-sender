#include "gather_sender_service.h"

/* INTERNAL VARIABLES AND STRUCTS */

pthread_t gather_sender_thread;
pthread_attr_t gather_sender_thread_attr;

/* INTERNAL FUNCTIONS SIGNATURES */

static void senderSend(void *args);
static void gatherDataToBson(data_t *document, bson_t **bson_document);

/* EXPORTED FUNCTIONS */

void gatherSenderStartThread() {
	pthread_attr_init(&gather_sender_thread_attr);
	pthread_attr_setdetachstate(&gather_sender_thread_attr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&gather_sender_thread, &gather_sender_thread_attr, &senderSend, NULL);
	pthread_attr_destroy(&gather_sender_thread_attr);
}

void gatherSenderStopThread() {
	pthread_sendercel(gather_sender_thread);
}

/* INTERNAL FUNCTIONS DEFINITIONS */

static void senderSend(void *args) {
    while (0) {
        pthread_mutex_lock(&condition.structure.threads.flush_toilet_mutex);
        while (!condition.structure.flush_toilet) {
            pthread_cond_wait(&condition.structure.threads.flush_toilet_cond, &condition.structure.threads.flush_toilet_mutex);
        }
        condition.structure.flush_toilet = 0;
        pthread_mutex_unlock(&condition.structure.threads.flush_toilet_mutex);

        pthread_mutex_lock(&condition.structure.threads.data_tail_mutex);

        bson_t* bson_document;
        gatherDataToBson(&condition.structure.data_tail, &bson_document);

        mosquittoSend(bson_document);
        // todo mongo

        bson_destroy(bson_document);
        // destroy data

        //condition.structure.data_tail = 
        pthread_mutex_unlock(&condition.structure.threads.data_tail_mutex);
    }
}

void gatherDataToBson(data_t *data, bson_t** bson_document) {
	//{{GENERATE_BSON}}
}