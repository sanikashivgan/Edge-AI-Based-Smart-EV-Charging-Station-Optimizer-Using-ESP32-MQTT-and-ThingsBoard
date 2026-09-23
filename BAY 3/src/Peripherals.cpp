#include <Arduino.h>
#include <DHT.h>
#include "State.h"
#include "Peripherals.h"
#include "config.h"


DHT   dht(DHT_PIN , DHT_TYPE);

float mapFloat(long x, long inMin, long inMax, float outMin, float outMax) 
{
  return (x - inMin) * (outMax - outMin) / (float)(inMax - inMin) + outMin;
}

void sample_sensor(void)
{
    int raw_current = analogRead(CURRENT_PIN); // 0 to 4095 //0 to 32A
    int raw_voltage = analogRead(VOLTAGE_PIN); // 0 to 4095 // 0 to 250v
    
    //map voltage 0 to 250v
    voltage = mapFloat(raw_voltage, 0 , 4095 , 0 , 250);

    if(bayStatus="CHARGING")
    {
    //map current 0 to 32A
    current = mapFloat(raw_current, 0 , 4095 , 0 , 32);
    }
    
    //power
    power= voltage*current;


    //to read temperature 
    float t= dht.readTemperature(DHT_PIN );
    if(!(isnan(t)))temperature= t;


}

float recentAvgCurrent()
{
    float sum = 0;
    //read recent 5 current values
    for(int i = 0; i < 5; i++)
    {
        sum = sum + current;

    }

    return sum/5;
}





bool plugin_flag_once=1;
bool plugout_flag_once =1;

;void plug_status(void)
{
   bool pluginReading = digitalRead(BTN_PLUGIN);

   // detect the sw is pressed
   if(pluginReading== LOW && plugin_flag_once)
   {
      sessionStartMs = millis();
// plug in switch is pressed
    plugin_flag_once =0;
   // change bay_status FREE to charging
   if(bayStatus == "FREE")
   {
      bayStatus="CHARGING";
      Serial.println("Bay1 plugin detected,Bay is Charging");
      digitalWrite(RELAY_PIN,HIGH);//TRUN ON RELAY

   }
     //update leds
   }
   if (pluginReading==HIGH)
   {
      plugin_flag_once =1;
   }
  

   // plug out switch is pressed
   // change bay_status  charging to FREE
   //update leds

   bool plugoutReading =digitalRead(BTN_PLUGOUT);

   // detect the sw is pressed
   if(plugoutReading == LOW && plugout_flag_once)
   {
   // plug out switch is pressed
    plugout_flag_once =0;
   // change bay_status  charging to free
   if(bayStatus == "CHARGING")
   {
      bayStatus="FREE";
      Serial.println("Bay1 plugout detected,Bay is Free")
   ;}
   
     //update leds
   }
   if (plugoutReading==HIGH)
   {
      plugout_flag_once=1;
   }
}

