#ifndef CONFIG_H
#define CONFIG_H

// ---------------------------------------------------------------------
// Pin configuration — SRS Section 8.1
// ---------------------------------------------------------------------
#define VOLTAGE_PIN 34
#define CURRENT_PIN 35
#define DHT_PIN 15
#define RELAY_PIN 26
#define BTN_PLUGIN 32
#define BTN_PLUGOUT 33
#define LED_GREEN 18
#define LED_YELLOW 19
#define LED_RED 21

#define DHT_TYPE DHT22

// ---------------- WiFi Details ----------------
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

// ---------------- ThingsBoard Details ----------------
extern const char* MQTT_SERVER;
extern const int MQTT_PORT;

// ThingsBoard Device Access Token
extern const char* TB_TOKEN;
extern const char* BAY_ID;

#endif