#ifndef TELEMETRY_STRUCTURE_SERVICE
#define TELEMETRY_STRUCTURE_SERVICE

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
#include "../can_service/can_service.h"
#include "../log_service/log_service.h"
#include "../gps_service/gps_service.h"
#include "structure_identifiers.h"

/* EXTERN */

extern condition_t condition;

/* TYPES */

/**
 * The enum type that describes a result for a gather-structure operation
*/
typedef enum { 
    GATHER_IDLE, 
    GATHER_ENABLE, 
    GATHER_KEEP, 
    GATHER_ERROR 
} gather_code;

/* FUNCTIONS */


/**
 * Starts two threads, one that listens to the canbus and another that listens for the gps. Both threads parse the messages and fill the data structure. 
 * They will be stopped and destroyed after a certain amount of time.
 * @param document The data structure variable to fill with the data obtained parsing the can and gps messages
 * @result the gather code resulted from the function. GATHER_IDLE and GATHER ENABLED if a steering wheel message to enable or 
 * disable the telemetry was received. GATHER_KEEP if it was succesfull and no message to change he telemetry status was received 
 * and GATHER_ERROR if there was an error.
*/
gather_code gatherStructure(data_t* document);


#endif