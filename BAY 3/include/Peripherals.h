#ifndef PERIPHERALS_H
#define PERIPHERALS_H
#include <DHT.h>

extern DHT dht;


void sample_sensor(void);
void plug_status(void);
void update_led_status(void);
void publishTelemetry(void);
float recentAvgCurrent(void);
#endif