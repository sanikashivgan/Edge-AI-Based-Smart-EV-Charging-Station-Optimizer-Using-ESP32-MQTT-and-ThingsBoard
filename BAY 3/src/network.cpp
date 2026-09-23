#include <WiFi.h>
#include <ArduinoJson.h>

#include "network.h"
#include "config.h"
#include "State.h"

// These functions are implemented elsewhere in the project.
// Their declarations should ideally be placed in a header file.
void requestSharedAttributes();
void handleRpc(String requestId, char* payload);
void applySharedAttributes(JsonObject attrs);

WiFiClient espClient;
PubSubClient mqtt(espClient);

// ---------------------------------------------------------------------
// WiFi connection
// ---------------------------------------------------------------------

void connectWiFi() {
  Serial.print("Connecting to WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long start = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - start < 15000) {

    delay(300);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(" connected.");
  } else {
    Serial.println(" FAILED (will retry).");
  }
}

// ---------------------------------------------------------------------
// MQTT connection
// ---------------------------------------------------------------------

void connectMQTT() {

  if (WiFi.status() != WL_CONNECTED) {
    return;
  }

  Serial.print("Connecting to ThingsBoard MQTT...");

  if (mqtt.connect(BAY_ID, TB_TOKEN, NULL)) {

    Serial.println(" connected.");

    mqtt.subscribe("v1/devices/me/attributes");
    mqtt.subscribe("v1/devices/me/attributes/response/+");
    mqtt.subscribe("v1/devices/me/rpc/request/+");

    requestSharedAttributes();

  } else {

    Serial.print(" failed, rc=");
    Serial.println(mqtt.state());

    delay(1000);
  }
}

// ---------------------------------------------------------------------
// MQTT callback
// ---------------------------------------------------------------------

void mqttCallback(char* topic, byte* payload, unsigned int length) {

  String topicStr = String(topic);

  char buf[400];

  unsigned int n =
      length < sizeof(buf) - 1
          ? length
          : sizeof(buf) - 1;

  memcpy(buf, payload, n);
  buf[n] = '\0';

  Serial.print("[MQTT <<] ");
  Serial.print(topicStr);
  Serial.print(" ");
  Serial.println(buf);

  // ---------------------------------------------------------------
  // RPC request
  // ---------------------------------------------------------------

  if (topicStr.startsWith("v1/devices/me/rpc/request/")) {

    String requestId =
        topicStr.substring(topicStr.lastIndexOf('/') + 1);

    handleRpc(requestId, buf);

    return;
  }

  // ---------------------------------------------------------------
  // Shared attributes / attribute response
  // ---------------------------------------------------------------

  JsonDocument doc;

  DeserializationError err =
      deserializeJson(doc, buf);

  if (err) {
    Serial.print("JSON parse error: ");
    Serial.println(err.c_str());
    return;
  }

  JsonObject attrs;

  if (doc.containsKey("shared")) {
    attrs = doc["shared"].as<JsonObject>();
  } else {
    attrs = doc.as<JsonObject>();
  }

  applySharedAttributes(attrs);
}