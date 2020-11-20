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
	data->inverters.right.speed_size = 500;
	data->inverters.right.speed = (inverters_right_speed_data*) malloc(sizeof(inverters_right_speed_data) * data->inverters.right.speed_size);
	data->inverters.right.speed_count = 0;
	data->inverters.right.temperature_igbt_size = 500;
	data->inverters.right.temperature_igbt = (inverters_right_temperature_igbt_data*) malloc(sizeof(inverters_right_temperature_igbt_data) * data->inverters.right.temperature_igbt_size);
	data->inverters.right.temperature_igbt_count = 0;
	data->inverters.right.temperature_motors_size = 500;
	data->inverters.right.temperature_motors = (inverters_right_temperature_motors_data*) malloc(sizeof(inverters_right_temperature_motors_data) * data->inverters.right.temperature_motors_size);
	data->inverters.right.temperature_motors_count = 0;
	data->inverters.right.torque_size = 500;
	data->inverters.right.torque = (inverters_right_torque_data*) malloc(sizeof(inverters_right_torque_data) * data->inverters.right.torque_size);
	data->inverters.right.torque_count = 0;
	data->inverters.left.speed_size = 500;
	data->inverters.left.speed = (inverters_left_speed_data*) malloc(sizeof(inverters_left_speed_data) * data->inverters.left.speed_size);
	data->inverters.left.speed_count = 0;
	data->inverters.left.temperature_igbt_size = 500;
	data->inverters.left.temperature_igbt = (inverters_left_temperature_igbt_data*) malloc(sizeof(inverters_left_temperature_igbt_data) * data->inverters.left.temperature_igbt_size);
	data->inverters.left.temperature_igbt_count = 0;
	data->inverters.left.temperature_motors_size = 500;
	data->inverters.left.temperature_motors = (inverters_left_temperature_motors_data*) malloc(sizeof(inverters_left_temperature_motors_data) * data->inverters.left.temperature_motors_size);
	data->inverters.left.temperature_motors_count = 0;
	data->inverters.left.torque_size = 500;
	data->inverters.left.torque = (inverters_left_torque_data*) malloc(sizeof(inverters_left_torque_data) * data->inverters.left.torque_size);
	data->inverters.left.torque_count = 0;
	data->bms_hv.temperature_size = 500;
	data->bms_hv.temperature = (bms_hv_temperature_data*) malloc(sizeof(bms_hv_temperature_data) * data->bms_hv.temperature_size);
	data->bms_hv.temperature_count = 0;
	data->bms_hv.voltage_size = 500;
	data->bms_hv.voltage = (bms_hv_voltage_data*) malloc(sizeof(bms_hv_voltage_data) * data->bms_hv.voltage_size);
	data->bms_hv.voltage_count = 0;
	data->bms_hv.current_size = 500;
	data->bms_hv.current = (bms_hv_current_data*) malloc(sizeof(bms_hv_current_data) * data->bms_hv.current_size);
	data->bms_hv.current_count = 0;
	data->bms_hv.errors_size = 500;
	data->bms_hv.errors = (bms_hv_errors_data*) malloc(sizeof(bms_hv_errors_data) * data->bms_hv.errors_size);
	data->bms_hv.errors_count = 0;
	data->bms_hv.warnings_size = 500;
	data->bms_hv.warnings = (bms_hv_warnings_data*) malloc(sizeof(bms_hv_warnings_data) * data->bms_hv.warnings_size);
	data->bms_hv.warnings_count = 0;
	data->bms_lv.values_size = 500;
	data->bms_lv.values = (bms_lv_values_data*) malloc(sizeof(bms_lv_values_data) * data->bms_lv.values_size);
	data->bms_lv.values_count = 0;
	data->bms_lv.errors_size = 500;
	data->bms_lv.errors = (bms_lv_errors_data*) malloc(sizeof(bms_lv_errors_data) * data->bms_lv.errors_size);
	data->bms_lv.errors_count = 0;
	data->gps.new.gga_size = 500;
	data->gps.new.gga = (gps_new_gga_data*) malloc(sizeof(gps_new_gga_data) * data->gps.new.gga_size);
	data->gps.new.gga_count = 0;
	data->gps.new.gll_size = 500;
	data->gps.new.gll = (gps_new_gll_data*) malloc(sizeof(gps_new_gll_data) * data->gps.new.gll_size);
	data->gps.new.gll_count = 0;
	data->gps.new.vtg_size = 500;
	data->gps.new.vtg = (gps_new_vtg_data*) malloc(sizeof(gps_new_vtg_data) * data->gps.new.vtg_size);
	data->gps.new.vtg_count = 0;
	data->gps.new.rmc_size = 500;
	data->gps.new.rmc = (gps_new_rmc_data*) malloc(sizeof(gps_new_rmc_data) * data->gps.new.rmc_size);
	data->gps.new.rmc_count = 0;
	data->gps.old.location_size = 500;
	data->gps.old.location = (gps_old_location_data*) malloc(sizeof(gps_old_location_data) * data->gps.old.location_size);
	data->gps.old.location_count = 0;
	data->gps.old.time_size = 500;
	data->gps.old.time = (gps_old_time_data*) malloc(sizeof(gps_old_time_data) * data->gps.old.time_size);
	data->gps.old.time_count = 0;
	data->gps.old.true_track_mode_size = 500;
	data->gps.old.true_track_mode = (gps_old_true_track_mode_data*) malloc(sizeof(gps_old_true_track_mode_data) * data->gps.old.true_track_mode_size);
	data->gps.old.true_track_mode_count = 0;
	data->imu_old.gyro_size = 500;
	data->imu_old.gyro = (imu_old_gyro_data*) malloc(sizeof(imu_old_gyro_data) * data->imu_old.gyro_size);
	data->imu_old.gyro_count = 0;
	data->imu_old.accel_size = 500;
	data->imu_old.accel = (imu_old_accel_data*) malloc(sizeof(imu_old_accel_data) * data->imu_old.accel_size);
	data->imu_old.accel_count = 0;
	data->imu.gyro_size = 500;
	data->imu.gyro = (imu_gyro_data*) malloc(sizeof(imu_gyro_data) * data->imu.gyro_size);
	data->imu.gyro_count = 0;
	data->imu.accel_size = 500;
	data->imu.accel = (imu_accel_data*) malloc(sizeof(imu_accel_data) * data->imu.accel_size);
	data->imu.accel_count = 0;
	data->front_wheels_encoders.right.speed_size = 500;
	data->front_wheels_encoders.right.speed = (front_wheels_encoders_right_speed_data*) malloc(sizeof(front_wheels_encoders_right_speed_data) * data->front_wheels_encoders.right.speed_size);
	data->front_wheels_encoders.right.speed_count = 0;
	data->front_wheels_encoders.right.speed_rads_size = 500;
	data->front_wheels_encoders.right.speed_rads = (front_wheels_encoders_right_speed_rads_data*) malloc(sizeof(front_wheels_encoders_right_speed_rads_data) * data->front_wheels_encoders.right.speed_rads_size);
	data->front_wheels_encoders.right.speed_rads_count = 0;
	data->front_wheels_encoders.right.angle_size = 500;
	data->front_wheels_encoders.right.angle = (front_wheels_encoders_right_angle_data*) malloc(sizeof(front_wheels_encoders_right_angle_data) * data->front_wheels_encoders.right.angle_size);
	data->front_wheels_encoders.right.angle_count = 0;
	data->front_wheels_encoders.left.speed_size = 500;
	data->front_wheels_encoders.left.speed = (front_wheels_encoders_left_speed_data*) malloc(sizeof(front_wheels_encoders_left_speed_data) * data->front_wheels_encoders.left.speed_size);
	data->front_wheels_encoders.left.speed_count = 0;
	data->front_wheels_encoders.left.speed_rads_size = 500;
	data->front_wheels_encoders.left.speed_rads = (front_wheels_encoders_left_speed_rads_data*) malloc(sizeof(front_wheels_encoders_left_speed_rads_data) * data->front_wheels_encoders.left.speed_rads_size);
	data->front_wheels_encoders.left.speed_rads_count = 0;
	data->front_wheels_encoders.left.angle_size = 500;
	data->front_wheels_encoders.left.angle = (front_wheels_encoders_left_angle_data*) malloc(sizeof(front_wheels_encoders_left_angle_data) * data->front_wheels_encoders.left.angle_size);
	data->front_wheels_encoders.left.angle_count = 0;
	data->distance_size = 500;
	data->distance = (distance_data*) malloc(sizeof(distance_data) * data->distance_size);
	data->distance_count = 0;
	data->pedals.throttle_size = 500;
	data->pedals.throttle = (pedals_throttle_data*) malloc(sizeof(pedals_throttle_data) * data->pedals.throttle_size);
	data->pedals.throttle_count = 0;
	data->pedals.brake_size = 500;
	data->pedals.brake = (pedals_brake_data*) malloc(sizeof(pedals_brake_data) * data->pedals.brake_size);
	data->pedals.brake_count = 0;
	data->steering_wheel.encoder_size = 500;
	data->steering_wheel.encoder = (steering_wheel_encoder_data*) malloc(sizeof(steering_wheel_encoder_data) * data->steering_wheel.encoder_size);
	data->steering_wheel.encoder_count = 0;
	data->steering_wheel.gears_size = 500;
	data->steering_wheel.gears = (steering_wheel_gears_data*) malloc(sizeof(steering_wheel_gears_data) * data->steering_wheel.gears_size);
	data->steering_wheel.gears_count = 0;
	
	return data;
}

void gatherDeleteData(data_t *data) {
	free(data->inverters.right.speed);
	free(data->inverters.right.temperature_igbt);
	free(data->inverters.right.temperature_motors);
	free(data->inverters.right.torque);
	free(data->inverters.left.speed);
	free(data->inverters.left.temperature_igbt);
	free(data->inverters.left.temperature_motors);
	free(data->inverters.left.torque);
	free(data->bms_hv.temperature);
	free(data->bms_hv.voltage);
	free(data->bms_hv.current);
	free(data->bms_hv.errors);
	free(data->bms_hv.warnings);
	free(data->bms_lv.values);
	free(data->bms_lv.errors);
	free(data->gps.new.gga);
	free(data->gps.new.gll);
	free(data->gps.new.vtg);
	free(data->gps.new.rmc);
	free(data->gps.old.location);
	free(data->gps.old.time);
	free(data->gps.old.true_track_mode);
	free(data->imu_old.gyro);
	free(data->imu_old.accel);
	free(data->imu.gyro);
	free(data->imu.accel);
	free(data->front_wheels_encoders.right.speed);
	free(data->front_wheels_encoders.right.speed_rads);
	free(data->front_wheels_encoders.right.angle);
	free(data->front_wheels_encoders.left.speed);
	free(data->front_wheels_encoders.left.speed_rads);
	free(data->front_wheels_encoders.left.angle);
	free(data->distance);
	free(data->pedals.throttle);
	free(data->pedals.brake);
	free(data->steering_wheel.encoder);
	free(data->steering_wheel.gears);
	free(data);
	
}

void gatherResetDataId() {
    condition.structure.id = 0;
}