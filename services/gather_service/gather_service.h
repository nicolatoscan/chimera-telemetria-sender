#ifndef TELEMETRY_GATHER_SERVICE
#define TELEMETRY_GATHER_SERVICE

/* IMPORTS */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/timeb.h>
#include <sys/sysinfo.h>
#include <bson.h>
#include <pthread.h>
#include "../../state_machine/state_machine_condition.h"

#include "./can/gather_can_service.h"
#include "./master/gather_master_service.h"

/* EXTERN */

extern condition_t condition;

/* FUNCTIONS */

/**
 * Initializes the structure object of the condition
*/
void gatherSetup();

/**
 * Creates and returns an empty data structure, that will contain all the messages gathered in a certain amount of 
 * time and translated to a bson document
 * @return The empty data structure
*/
data_t* gatherCreateData();

/**
 * Deallocates the passed data structure
 * @param document The data structure to deallocate 
*/
void gatherDeleteData(data_t *document);

/**
 * Resets the id of the data_head structure
*/
void gatherResetDataId();

#endif