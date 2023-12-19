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

#include <Adafruit_Sensor.h>
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
void setup() {
  manager.setup();
  sensor = new GetIMU();
  sensor->startSensor(&bno);
  Serial.println("Loading with name: " + name[0]);
  servos = new ServoServer();
  coms.attach(new NameCheckerServer(name));
  coms.attach((PacketEvent*)sensor);
  coms.attach((PacketEvent*)servos);
}

void loop() {
  manager.loop();
  if(manager.getState()==Connected)
    coms.server();
}
