#include <Arduino.h>
#include "State.h"
#include <WiFi.h>
#include "config.h"
#include "Peripherals.h"
#include "Network.h"
#include "edge_ai.h"
#include "optimization.h"
#include "rpc.h"
#include "attributes.h"


void setup()
{

    Serial.begin(115200);
    dht.begin();  // initialise sesnor
    pinMode(BTN_PLUGIN, INPUT_PULLUP );
    pinMode(BTN_PLUGOUT, INPUT_PULLUP );
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_RED, OUTPUT);

//connect Board to wifi
    connectWiFi();


// Configure MQTT server
mqtt.setServer(MQTT_SERVER, MQTT_PORT); //mqtt server addr of things and port number
//call back function
mqtt.setCallback(mqttCallback);
mqtt.setBufferSize(512);

//connect board to the cloud
connectMQTT() ; // TOKEN , device id
  
}

unsigned long now;
unsigned long last_print;

void loop()
{
    mqtt.loop();
    //print vals every 2 sec
    now = millis();
    if((now - last_print) > 5000)
    {
        last_print = now;
        //read data from sensor//V,I,P,baystatus
        sample_sensor();
        

       //run ai to get the prediction
        runEdgeAIInference();
       // decide load based on the prediction
       if( manualOverrideActive == 0)
       {
            runOptimization();
        }


       //publish the data
        publishTelemetry();
        

        

    }
      
    plug_status();
    updateLeds();
}

   

