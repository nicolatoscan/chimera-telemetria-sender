#ifndef TELEMETRY_GATHER_MASTER_SERVICE
#define TELEMETRY_GATHER_MASTER_SERVICE

/* IMPORTS */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/timeb.h>
#include <sys/sysinfo.h>
#include "../../state_machine/state_machine_condition.h"

/* EXTERN */

extern condition_t condition;

/* FUNCTIONS */

void gatherMasterWait();
void gatherMasterSwap();

#endif