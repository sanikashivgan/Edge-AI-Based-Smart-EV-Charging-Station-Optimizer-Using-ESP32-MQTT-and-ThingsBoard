#include <Arduino.h>
#include "optimization.h"
#include "config.h"
#include "state.h"

// ---------------------------------------------------------------------
// SRS 8.7 optimization - skipped entirely while manualOverrideActive
// (an RPC call is in effect).
// ---------------------------------------------------------------------
void runOptimization() {
    float totalStationPower = power; // Phase 5 aggregates real total on ThingsBoard
    overloadActive = false;

    if (bayStatus != "CHARGING") {
        bool peakHour = (lastHourOfDay >= peakTariffStartHr && lastHourOfDay <= peakTariffEndHr);

        if (peakHour && predictedArrivalProb >= predictionThreshold) {
            loadDecision = "STANDBY_EXPECTING";
        } else if (peakHour) {
            loadDecision = "LOW_DEMAND";
        }
        return;
    }

    if (bayStatus == "CHARGING") {
        if (current > overloadCurrentA) {
            loadDecision = "THROTTLE";
            throttleLevel = 50;
            overloadActive = true;
            Serial.println("!! Overcurrent -> THROTTLE @ 50%.");
        } else if (totalStationPower > maxStationLoadW) {
            // Peak load reached - prioritize bays with lower predictedDurationMin
            // (i.e., sessions closer to completion keep full power; others throttle)
            if (predictedDurationMin > 10) {
                loadDecision = "THROTTLE";
                throttleLevel = 70;
                Serial.println("!! Station power cap exceeded -> THROTTLE @ 70%.");
            } else {
                loadDecision = "ALLOW";
                throttleLevel = 100;
            }
        } else {
            loadDecision = "ALLOW";
            throttleLevel = 100;
        }
    }
}

// ---------------------------------------------------------------------
// FR-6: apply throttleLevel to the relay via duty-cycling.
// ---------------------------------------------------------------------
void applyRelayDutyCycle() {
    if (bayStatus != "CHARGING") {
        digitalWrite(RELAY_PIN, LOW);
        return;
    }
    if (throttleLevel >= 100) {
        digitalWrite(RELAY_PIN, HIGH);
        return;
    }
    if (throttleLevel <= 0) {
        digitalWrite(RELAY_PIN, LOW);
        return;
    }
    unsigned long phase = millis() % 2000;
    unsigned long onTime = (2000 * throttleLevel) / 100;
    digitalWrite(RELAY_PIN, phase < onTime ? HIGH : LOW);
}

void updateLeds() {
    digitalWrite(LED_RED, overloadActive ? HIGH : LOW);
    digitalWrite(LED_GREEN, (bayStatus == "FREE" && !overloadActive) ? HIGH : LOW);
    digitalWrite(LED_YELLOW, (bayStatus == "CHARGING" && !overloadActive) ? HIGH : LOW);
}