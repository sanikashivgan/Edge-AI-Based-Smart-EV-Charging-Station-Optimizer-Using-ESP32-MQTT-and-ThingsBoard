#include <time.h>
#include "edge_ai.h"
#include "state.h"
#include "telemetry.h"
#include "model.h"
// Same commute-hour pattern used to generate the training data
// (ai_training/generate_dataset.py). In a later phase this can be
// replaced with a table learned from real historical telemetry.
float historicalArrivalRate(int hour) {
  if (hour >= 8 && hour <= 10) return 0.62;
  if (hour >= 18 && hour <= 21) return 0.58;
  if (hour >= 0 && hour <= 5) return 0.06;
  if (hour >= 11 && hour <= 17) return 0.30;
  return 0.18;
}

void runEdgeAIInference() {
  struct tm timeinfo;
  int hourOfDay = 12, dayOfWeek = 0;
  if (getLocalTime(&timeinfo, 100)) {
    hourOfDay = timeinfo.tm_hour;
    dayOfWeek = timeinfo.tm_wday;
  }
  lastHourOfDay = hourOfDay;

  float bayOccupiedF = (bayStatus == "CHARGING") ? 1.0f : 0.0f;
  float sessionElapsedMin = (bayStatus == "CHARGING") ? (millis() - sessionStartMs) / 60000.0f : 0.0f;
  float histRate = historicalArrivalRate(hourOfDay);

  predictedArrivalProb = predictArrival(hourOfDay, dayOfWeek, bayOccupiedF,
                                         recentAvgCurrent(), sessionElapsedMin, histRate);
  predictedDurationMin = (bayStatus == "CHARGING")
      ? (int)predictDuration(hourOfDay, dayOfWeek, bayOccupiedF,
                              recentAvgCurrent(), sessionElapsedMin, histRate)
      : 0;
}