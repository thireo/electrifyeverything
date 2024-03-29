/*
 * obd.h
 *
 * Created: 09-09-2018 20:21:29
 *  Author: Andreas
 */ 


#ifndef OBD_H_
#define OBD_H_

#include "asf.h"
#include "status_codes.h"

#define INIT_CMD1 "ATZ\r"	//RESET 
#define INIT_CMD2 "ATE0\r"	//ECHO OFF
#define INIT_CMD3 "ATH0\r"	//HEADERS OFF

// Mode 1 PIDs
#define PID_MONITOR_STATUS 0x01
#define PID_ENGINE_LOAD 0x04
#define PID_COOLANT_TEMP 0x05
#define PID_SHORT_TERM_FUEL_TRIM_1 0x06
#define PID_LONG_TERM_FUEL_TRIM_1 0x07
#define PID_SHORT_TERM_FUEL_TRIM_2 0x08
#define PID_LONG_TERM_FUEL_TRIM_2 0x09
#define PID_FUEL_PRESSURE 0x0A
#define PID_INTAKE_MAP 0x0B
#define PID_RPM 0x0C
#define PID_SPEED 0x0D
#define PID_TIMING_ADVANCE 0x0E
#define PID_INTAKE_TEMP 0x0F
#define PID_MAF_FLOW 0x10
#define PID_THROTTLE 0x11
#define PID_AUX_INPUT 0x1E
#define PID_RUNTIME 0x1F
#define PID_DISTANCE_WITH_MIL 0x21
#define PID_COMMANDED_EGR 0x2C
#define PID_EGR_ERROR 0x2D
#define PID_COMMANDED_EVAPORATIVE_PURGE 0x2E
#define PID_FUEL_LEVEL 0x2F
#define PID_WARMS_UPS 0x30
#define PID_DISTANCE 0x31
#define PID_EVAP_SYS_VAPOR_PRESSURE 0x32
#define PID_BAROMETRIC 0x33
#define PID_CATALYST_TEMP_B1S1 0x3C
#define PID_CATALYST_TEMP_B2S1 0x3D
#define PID_CATALYST_TEMP_B1S2 0x3E
#define PID_CATALYST_TEMP_B2S2 0x3F
#define PID_CONTROL_MODULE_VOLTAGE 0x42
#define PID_ABSOLUTE_ENGINE_LOAD 0x43
#define PID_AIR_FUEL_EQUIV_RATIO 0x44
#define PID_RELATIVE_THROTTLE_POS 0x45
#define PID_AMBIENT_TEMP 0x46
#define PID_ABSOLUTE_THROTTLE_POS_B 0x47
#define PID_ABSOLUTE_THROTTLE_POS_C 0x48
#define PID_ACC_PEDAL_POS_D 0x49
#define PID_ACC_PEDAL_POS_E 0x4A
#define PID_ACC_PEDAL_POS_F 0x4B
#define PID_COMMANDED_THROTTLE_ACTUATOR 0x4C
#define PID_TIME_WITH_MIL 0x4D
#define PID_TIME_SINCE_CODES_CLEARED 0x4E
#define PID_ETHANOL_FUEL 0x52
#define PID_FUEL_RAIL_PRESSURE 0x59
#define PID_HYBRID_BATTERY_PERCENTAGE 0x5B
#define PID_ENGINE_OIL_TEMP 0x5C
#define PID_FUEL_INJECTION_TIMING 0x5D
#define PID_ENGINE_FUEL_RATE 0x5E
#define PID_ENGINE_TORQUE_DEMANDED 0x61
#define PID_ENGINE_TORQUE_PERCENTAGE 0x62
#define PID_ENGINE_REF_TORQUE 0x63

// non-OBD/custom PIDs (no mode number)
#define PID_GPS_LATITUDE 0xA
#define PID_GPS_LONGITUDE 0xB
#define PID_GPS_ALTITUDE 0xC
#define PID_GPS_SPEED 0xD
#define PID_GPS_HEADING 0xE
#define PID_GPS_SAT_COUNT 0xF
#define PID_GPS_TIME 0x10
#define PID_GPS_DATE 0x11
#define PID_ACC 0x20
#define PID_GYRO 0x21
#define PID_COMPASS 0x22
#define PID_MEMS_TEMP 0x23
#define PID_BATTERY_VOLTAGE 0x24

// custom PIDs for calculated data
#define PID_TRIP_DISTANCE 0x30

typedef enum {
	PROTO_AUTO = 0,
	PROTO_ISO_9141_2 = 3,
	PROTO_KWP2000_5KBPS = 4,
	PROTO_KWP2000_FAST = 5,
	PROTO_CAN_11B_500K = 6,
	PROTO_CAN_29B_500K = 7,
	PROTO_CAN_29B_250K = 8,
	PROTO_CAN_11B_250K = 9,
} OBD_PROTOCOLS;

uint8_t dataMode;
uint8_t errors;
uint8_t pidmap[4 * 4];



uint16_t hex2uint16(const char *p);
uint8_t hex2uint8(const char *p);
void obd_init(void);
enum status_code obd_send_query_pid(uint8_t service, uint8_t pid, uint8_t data_length, uint8_t *read_read);
enum status_code obd_send_query_string(uint8_t *string, uint8_t data_length, uint8_t *read_read);

uint8_t get_engine_load(void);
int get_coolant_temp(void);
uint8_t get_intake_manifold_pressure(void);
int get_intake_air_temp(void);
uint16_t get_engine_rpm(void);
uint8_t get_vehicle_speed(void);
uint8_t get_monitor_status(void);
float get_battery_voltage(void);

#endif /* OBD_H_ */