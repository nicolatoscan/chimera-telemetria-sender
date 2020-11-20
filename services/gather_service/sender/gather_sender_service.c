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
	*bson_document = bson_new();
	bson_t *children = (bson_t*)malloc(sizeof(bson_t) * 5);
	BSON_APPEND_INT32(*bson_document, "id", data->id);
	BSON_APPEND_INT64(*bson_document, "timestamp", data->timestamp);
	BSON_APPEND_UTF8(*bson_document, "sessionName", data->sessionName);
	BSON_APPEND_DOCUMENT_BEGIN(*bson_document, "inverters", &children[0]);
	BSON_APPEND_DOCUMENT_BEGIN(&children[0], "right", &children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "speed", &children[2]);
	for (int i = 0; i < (data->inverters.right.speed_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->inverters.right.speed[i].timestamp);
		BSON_APPEND_DOUBLE(&children[3], "value", data->inverters.right.speed[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "temperature_igbt", &children[2]);
	for (int i = 0; i < (data->inverters.right.temperature_igbt_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->inverters.right.temperature_igbt[i].timestamp);
		BSON_APPEND_DOUBLE(&children[3], "value", data->inverters.right.temperature_igbt[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "temperature_motors", &children[2]);
	for (int i = 0; i < (data->inverters.right.temperature_motors_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->inverters.right.temperature_motors[i].timestamp);
		BSON_APPEND_DOUBLE(&children[3], "value", data->inverters.right.temperature_motors[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "torque", &children[2]);
	for (int i = 0; i < (data->inverters.right.torque_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->inverters.right.torque[i].timestamp);
		BSON_APPEND_DOUBLE(&children[3], "value", data->inverters.right.torque[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	bson_append_document_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_DOCUMENT_BEGIN(&children[0], "left", &children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "speed", &children[2]);
	for (int i = 0; i < (data->inverters.left.speed_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->inverters.left.speed[i].timestamp);
		BSON_APPEND_DOUBLE(&children[3], "value", data->inverters.left.speed[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "temperature_igbt", &children[2]);
	for (int i = 0; i < (data->inverters.left.temperature_igbt_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->inverters.left.temperature_igbt[i].timestamp);
		BSON_APPEND_DOUBLE(&children[3], "value", data->inverters.left.temperature_igbt[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "temperature_motors", &children[2]);
	for (int i = 0; i < (data->inverters.left.temperature_motors_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->inverters.left.temperature_motors[i].timestamp);
		BSON_APPEND_DOUBLE(&children[3], "value", data->inverters.left.temperature_motors[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "torque", &children[2]);
	for (int i = 0; i < (data->inverters.left.torque_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->inverters.left.torque[i].timestamp);
		BSON_APPEND_DOUBLE(&children[3], "value", data->inverters.left.torque[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	bson_append_document_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	bson_append_document_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_DOCUMENT_BEGIN(*bson_document, "bms_hv", &children[0]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "temperature", &children[1]);
	for (int i = 0; i < (data->bms_hv.temperature_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->bms_hv.temperature[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_DOUBLE(&children[3], "max", data->bms_hv.temperature[i].value.max);
		BSON_APPEND_DOUBLE(&children[3], "min", data->bms_hv.temperature[i].value.min);
		BSON_APPEND_DOUBLE(&children[3], "average", data->bms_hv.temperature[i].value.average);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "voltage", &children[1]);
	for (int i = 0; i < (data->bms_hv.voltage_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->bms_hv.voltage[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_DOUBLE(&children[3], "max", data->bms_hv.voltage[i].value.max);
		BSON_APPEND_DOUBLE(&children[3], "min", data->bms_hv.voltage[i].value.min);
		BSON_APPEND_DOUBLE(&children[3], "total", data->bms_hv.voltage[i].value.total);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "current", &children[1]);
	for (int i = 0; i < (data->bms_hv.current_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->bms_hv.current[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_DOUBLE(&children[3], "current", data->bms_hv.current[i].value.current);
		BSON_APPEND_DOUBLE(&children[3], "pow", data->bms_hv.current[i].value.pow);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "errors", &children[1]);
	for (int i = 0; i < (data->bms_hv.errors_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->bms_hv.errors[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_INT32(&children[3], "fault_id", data->bms_hv.errors[i].value.fault_id);
		BSON_APPEND_INT32(&children[3], "fault_index", data->bms_hv.errors[i].value.fault_index);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "warnings", &children[1]);
	for (int i = 0; i < (data->bms_hv.warnings_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->bms_hv.warnings[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_INT32(&children[3], "fault_id", data->bms_hv.warnings[i].value.fault_id);
		BSON_APPEND_INT32(&children[3], "fault_index", data->bms_hv.warnings[i].value.fault_index);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	bson_append_document_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_DOCUMENT_BEGIN(*bson_document, "bms_lv", &children[0]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "values", &children[1]);
	for (int i = 0; i < (data->bms_lv.values_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->bms_lv.values[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_DOUBLE(&children[3], "voltage", data->bms_lv.values[i].value.voltage);
		BSON_APPEND_DOUBLE(&children[3], "temperature", data->bms_lv.values[i].value.temperature);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "errors", &children[1]);
	for (int i = 0; i < (data->bms_lv.errors_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->bms_lv.errors[i].timestamp);
		BSON_APPEND_INT32(&children[2], "value", data->bms_lv.errors[i].value);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	bson_append_document_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_DOCUMENT_BEGIN(*bson_document, "gps", &children[0]);
	BSON_APPEND_DOCUMENT_BEGIN(&children[0], "new", &children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "gga", &children[2]);
	for (int i = 0; i < (data->gps.new.gga_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->gps.new.gga[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[3], "value", &children[4]);
		BSON_APPEND_DOUBLE(&children[4], "latitude_safe", data->gps.new.gga[i].value.latitude_safe);
		BSON_APPEND_DOUBLE(&children[4], "longitude_safe", data->gps.new.gga[i].value.longitude_safe);
		BSON_APPEND_DOUBLE(&children[4], "latitude", data->gps.new.gga[i].value.latitude);
		BSON_APPEND_DOUBLE(&children[4], "longitude", data->gps.new.gga[i].value.longitude);
		BSON_APPEND_DOUBLE(&children[4], "altitude", data->gps.new.gga[i].value.altitude);
		BSON_APPEND_UTF8(&children[4], "ns_indicator", data->gps.new.gga[i].value.ns_indicator);
		BSON_APPEND_UTF8(&children[4], "ew_indicator", data->gps.new.gga[i].value.ew_indicator);
		BSON_APPEND_UTF8(&children[4], "utc_time", data->gps.new.gga[i].value.utc_time);
		bson_append_document_end(&children[3], &children[4]);
		bson_destroy(&children[4]);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "gll", &children[2]);
	for (int i = 0; i < (data->gps.new.gll_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->gps.new.gll[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[3], "value", &children[4]);
		BSON_APPEND_DOUBLE(&children[4], "latitude", data->gps.new.gll[i].value.latitude);
		BSON_APPEND_DOUBLE(&children[4], "longitude", data->gps.new.gll[i].value.longitude);
		BSON_APPEND_UTF8(&children[4], "ns_indicator", data->gps.new.gll[i].value.ns_indicator);
		BSON_APPEND_UTF8(&children[4], "ew_indicator", data->gps.new.gll[i].value.ew_indicator);
		BSON_APPEND_UTF8(&children[4], "utc_time", data->gps.new.gll[i].value.utc_time);
		bson_append_document_end(&children[3], &children[4]);
		bson_destroy(&children[4]);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "vtg", &children[2]);
	for (int i = 0; i < (data->gps.new.vtg_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->gps.new.vtg[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[3], "value", &children[4]);
		BSON_APPEND_DOUBLE(&children[4], "ground_speed_knots", data->gps.new.vtg[i].value.ground_speed_knots);
		BSON_APPEND_DOUBLE(&children[4], "ground_speed_human", data->gps.new.vtg[i].value.ground_speed_human);
		bson_append_document_end(&children[3], &children[4]);
		bson_destroy(&children[4]);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "rmc", &children[2]);
	for (int i = 0; i < (data->gps.new.rmc_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->gps.new.rmc[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[3], "value", &children[4]);
		BSON_APPEND_DOUBLE(&children[4], "latitude", data->gps.new.rmc[i].value.latitude);
		BSON_APPEND_DOUBLE(&children[4], "longitude", data->gps.new.rmc[i].value.longitude);
		BSON_APPEND_UTF8(&children[4], "ns_indicator", data->gps.new.rmc[i].value.ns_indicator);
		BSON_APPEND_UTF8(&children[4], "ew_indicator", data->gps.new.rmc[i].value.ew_indicator);
		BSON_APPEND_UTF8(&children[4], "utc_time", data->gps.new.rmc[i].value.utc_time);
		BSON_APPEND_UTF8(&children[4], "date", data->gps.new.rmc[i].value.date);
		BSON_APPEND_DOUBLE(&children[4], "ground_speed_knots", data->gps.new.rmc[i].value.ground_speed_knots);
		bson_append_document_end(&children[3], &children[4]);
		bson_destroy(&children[4]);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	bson_append_document_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_DOCUMENT_BEGIN(&children[0], "old", &children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "location", &children[2]);
	for (int i = 0; i < (data->gps.old.location_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->gps.old.location[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[3], "value", &children[4]);
		BSON_APPEND_DOUBLE(&children[4], "latitude_m", data->gps.old.location[i].value.latitude_m);
		BSON_APPEND_INT32(&children[4], "latitude_o", data->gps.old.location[i].value.latitude_o);
		BSON_APPEND_DOUBLE(&children[4], "longitude_m", data->gps.old.location[i].value.longitude_m);
		BSON_APPEND_INT32(&children[4], "longitude_o", data->gps.old.location[i].value.longitude_o);
		BSON_APPEND_DOUBLE(&children[4], "speed", data->gps.old.location[i].value.speed);
		BSON_APPEND_DOUBLE(&children[4], "altitude", data->gps.old.location[i].value.altitude);
		bson_append_document_end(&children[3], &children[4]);
		bson_destroy(&children[4]);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "time", &children[2]);
	for (int i = 0; i < (data->gps.old.time_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->gps.old.time[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[3], "value", &children[4]);
		BSON_APPEND_INT32(&children[4], "hours", data->gps.old.time[i].value.hours);
		BSON_APPEND_INT32(&children[4], "minutes", data->gps.old.time[i].value.minutes);
		BSON_APPEND_INT32(&children[4], "seconds", data->gps.old.time[i].value.seconds);
		bson_append_document_end(&children[3], &children[4]);
		bson_destroy(&children[4]);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "true_track_mode", &children[2]);
	for (int i = 0; i < (data->gps.old.true_track_mode_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->gps.old.true_track_mode[i].timestamp);
		BSON_APPEND_INT32(&children[3], "value", data->gps.old.true_track_mode[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	bson_append_document_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	bson_append_document_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_DOCUMENT_BEGIN(*bson_document, "imu_old", &children[0]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "gyro", &children[1]);
	for (int i = 0; i < (data->imu_old.gyro_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->imu_old.gyro[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_DOUBLE(&children[3], "x", data->imu_old.gyro[i].value.x);
		BSON_APPEND_DOUBLE(&children[3], "y", data->imu_old.gyro[i].value.y);
		BSON_APPEND_DOUBLE(&children[3], "z", data->imu_old.gyro[i].value.z);
		BSON_APPEND_DOUBLE(&children[3], "scale", data->imu_old.gyro[i].value.scale);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "accel", &children[1]);
	for (int i = 0; i < (data->imu_old.accel_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->imu_old.accel[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_DOUBLE(&children[3], "x", data->imu_old.accel[i].value.x);
		BSON_APPEND_DOUBLE(&children[3], "y", data->imu_old.accel[i].value.y);
		BSON_APPEND_DOUBLE(&children[3], "z", data->imu_old.accel[i].value.z);
		BSON_APPEND_DOUBLE(&children[3], "scale", data->imu_old.accel[i].value.scale);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	bson_append_document_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_DOCUMENT_BEGIN(*bson_document, "imu", &children[0]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "gyro", &children[1]);
	for (int i = 0; i < (data->imu.gyro_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->imu.gyro[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_DOUBLE(&children[3], "x", data->imu.gyro[i].value.x);
		BSON_APPEND_DOUBLE(&children[3], "y", data->imu.gyro[i].value.y);
		BSON_APPEND_DOUBLE(&children[3], "z", data->imu.gyro[i].value.z);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "accel", &children[1]);
	for (int i = 0; i < (data->imu.accel_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->imu.accel[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_DOUBLE(&children[3], "x", data->imu.accel[i].value.x);
		BSON_APPEND_DOUBLE(&children[3], "y", data->imu.accel[i].value.y);
		BSON_APPEND_DOUBLE(&children[3], "z", data->imu.accel[i].value.z);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	bson_append_document_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_DOCUMENT_BEGIN(*bson_document, "front_wheels_encoders", &children[0]);
	BSON_APPEND_DOCUMENT_BEGIN(&children[0], "right", &children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "speed", &children[2]);
	for (int i = 0; i < (data->front_wheels_encoders.right.speed_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->front_wheels_encoders.right.speed[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[3], "value", &children[4]);
		BSON_APPEND_DOUBLE(&children[4], "speed", data->front_wheels_encoders.right.speed[i].value.speed);
		BSON_APPEND_INT32(&children[4], "error_flag", data->front_wheels_encoders.right.speed[i].value.error_flag);
		bson_append_document_end(&children[3], &children[4]);
		bson_destroy(&children[4]);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "speed_rads", &children[2]);
	for (int i = 0; i < (data->front_wheels_encoders.right.speed_rads_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->front_wheels_encoders.right.speed_rads[i].timestamp);
		BSON_APPEND_DOUBLE(&children[3], "value", data->front_wheels_encoders.right.speed_rads[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "angle", &children[2]);
	for (int i = 0; i < (data->front_wheels_encoders.right.angle_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->front_wheels_encoders.right.angle[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[3], "value", &children[4]);
		BSON_APPEND_DOUBLE(&children[4], "angle_0", data->front_wheels_encoders.right.angle[i].value.angle_0);
		BSON_APPEND_DOUBLE(&children[4], "angle_1", data->front_wheels_encoders.right.angle[i].value.angle_1);
		BSON_APPEND_DOUBLE(&children[4], "angle_delta", data->front_wheels_encoders.right.angle[i].value.angle_delta);
		bson_append_document_end(&children[3], &children[4]);
		bson_destroy(&children[4]);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	bson_append_document_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_DOCUMENT_BEGIN(&children[0], "left", &children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "speed", &children[2]);
	for (int i = 0; i < (data->front_wheels_encoders.left.speed_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->front_wheels_encoders.left.speed[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[3], "value", &children[4]);
		BSON_APPEND_DOUBLE(&children[4], "speed", data->front_wheels_encoders.left.speed[i].value.speed);
		BSON_APPEND_INT32(&children[4], "error_flag", data->front_wheels_encoders.left.speed[i].value.error_flag);
		bson_append_document_end(&children[3], &children[4]);
		bson_destroy(&children[4]);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "speed_rads", &children[2]);
	for (int i = 0; i < (data->front_wheels_encoders.left.speed_rads_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->front_wheels_encoders.left.speed_rads[i].timestamp);
		BSON_APPEND_DOUBLE(&children[3], "value", data->front_wheels_encoders.left.speed_rads[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "angle", &children[2]);
	for (int i = 0; i < (data->front_wheels_encoders.left.angle_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->front_wheels_encoders.left.angle[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[3], "value", &children[4]);
		BSON_APPEND_DOUBLE(&children[4], "angle_0", data->front_wheels_encoders.left.angle[i].value.angle_0);
		BSON_APPEND_DOUBLE(&children[4], "angle_1", data->front_wheels_encoders.left.angle[i].value.angle_1);
		BSON_APPEND_DOUBLE(&children[4], "angle_delta", data->front_wheels_encoders.left.angle[i].value.angle_delta);
		bson_append_document_end(&children[3], &children[4]);
		bson_destroy(&children[4]);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	bson_append_document_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	bson_append_document_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_ARRAY_BEGIN(*bson_document, "distance", &children[0]);
	for (int i = 0; i < (data->distance_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[0], "0", &children[1]);
		BSON_APPEND_INT64(&children[1], "timestamp", data->distance[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "value", &children[2]);
		BSON_APPEND_DOUBLE(&children[2], "meters", data->distance[i].value.meters);
		BSON_APPEND_DOUBLE(&children[2], "rotations", data->distance[i].value.rotations);
		BSON_APPEND_DOUBLE(&children[2], "angle", data->distance[i].value.angle);
		BSON_APPEND_DOUBLE(&children[2], "clock_period", data->distance[i].value.clock_period);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
		bson_append_document_end(&children[0], &children[1]);
		bson_destroy(&children[1]);
	}
	bson_append_array_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_DOCUMENT_BEGIN(*bson_document, "pedals", &children[0]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "throttle", &children[1]);
	for (int i = 0; i < (data->pedals.throttle_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->pedals.throttle[i].timestamp);
		BSON_APPEND_INT32(&children[2], "value", data->pedals.throttle[i].value);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "brake", &children[1]);
	for (int i = 0; i < (data->pedals.brake_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->pedals.brake[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_INT32(&children[3], "is_breaking", data->pedals.brake[i].value.is_breaking);
		BSON_APPEND_DOUBLE(&children[3], "pressure_front", data->pedals.brake[i].value.pressure_front);
		BSON_APPEND_DOUBLE(&children[3], "pressure_back", data->pedals.brake[i].value.pressure_back);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	bson_append_document_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_DOCUMENT_BEGIN(*bson_document, "steering_wheel", &children[0]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "encoder", &children[1]);
	for (int i = 0; i < (data->steering_wheel.encoder_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->steering_wheel.encoder[i].timestamp);
		BSON_APPEND_DOUBLE(&children[2], "value", data->steering_wheel.encoder[i].value);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "gears", &children[1]);
	for (int i = 0; i < (data->steering_wheel.gears_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->steering_wheel.gears[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_INT32(&children[3], "control", data->steering_wheel.gears[i].value.control);
		BSON_APPEND_INT32(&children[3], "cooling", data->steering_wheel.gears[i].value.cooling);
		BSON_APPEND_INT32(&children[3], "map", data->steering_wheel.gears[i].value.map);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_INT32(&children[0], "marker", data->steering_wheel.marker);
	bson_append_document_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	
}