#include "Arduino.h"
#include <SimplePacketComs.h>
#include <WiFi.h>
#include <PacketEvent.h>
#include <Esp32SimplePacketComs.h>
#include <server/UDPSimplePacket.h>
#include <Preferences.h>
#include <Esp32WifiManager.h>
#include <wifi/WifiManager.h>
#include <server/NameCheckerServer.h>
#include <ESP32Servo.h>
#include <EasyBNO055_ESP.h>

#include "ServoServer.h"
#include "GetIMU.h"

#include <Adafruit_Sensor.h> // Adafruit_Unified_Sensor
#include <Adafruit_BNO055.h>

#include <Wire.h>

// SImple packet coms implementation useing WiFi
UDPSimplePacket coms;

// WIfi stack managment state machine
WifiManager manager;
//The setup function is called once at startup of the sketch
String* name = new String("midnight");
GetIMU* sensor;
ServoServer* servos;
EasyBNO055_ESP bno;
void otherI2CUpdate(){
	//Serial.println("otherI2CUpdate");
}

void setup() {
  manager.setupAP();
  servos = new ServoServer();
  manager.startThread();
  while(manager.getState()!=Connected){
    vTaskDelay(10); //sleep 10ms
  }
  Serial.println("Starting Firmware Setup after WiFi connection");
  sensor = new GetIMU();
	bno.start(&otherI2CUpdate);
  sensor->startSensor(&bno);
  Serial.println("Loading with name: " + name[0]);

  coms.attach(new NameCheckerServer(name));
  coms.attach((PacketEvent*)sensor);
  coms.attach((PacketEvent*)servos);
  Serial.println("Starting Firmware Loop");
//int test =ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED;
}

void loop() {
  if(manager.getState()==Connected)
    coms.server();
}
