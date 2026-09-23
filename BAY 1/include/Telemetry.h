#ifndef NETWORK_H
#define NETWORK_H
 
#include <WiFiClient.h>
#include <PubSubClient.h>
 
extern WiFiClient espClient;
extern PubSubClient mqtt; 
void connectWiFi();
void connectMQTT();
 
void publishTelemetry();
float recentAvgCurrent();
 
 
#endif
