/*
 * ServoServer.cpp
 *
 *  Created on: Mar 1, 2019
 *      Author: jmmckinney
 */

#include "ServoServer.h"

int servoPins[MAX_POSSIBLE_SERVOS] = {
  FRONT_RIGHT_NECK,  //0
  FRONT_LEFT_NECK,   //1
  REAR_RIGHT_TAIL,   //2
  REAR_LEFT_TAIL,    //3

  FRONT_RIGHT_SHOULDER_TILT,              //4
  FRONT_RIGHT_SHOULDER_FORWARD_BACKWARD,  //5
  FRONT_RIGHT_ELBOW,                      //6

  FRONT_LEFT_SHOULDER_TILT,              //7
  FRONT_LEFT_SHOULDER_FORWARD_BACKWARD,  //8
  FRONT_LEFT_ELBOW,                      //9

  REAR_RIGHT_SHOULDER_TILT,              //10
  REAR_RIGHT_SHOULDER_FORWARD_BACKWARD,  //11
  REAR_RIGHT_ELBOW,                      //12

  REAR_LEFT_SHOULDER_TILT,              //13
  REAR_LEFT_SHOULDER_FORWARD_BACKWARD,  //14
  REAR_LEFT_ELBOW,                      //15

  PAN_NECK,   //16
  TILT_NECK,  //17
  PAN_TAIL,   //18
  TILT_TAIL   //19
};

ServoServer::ServoServer()
  : PacketEventAbstract(1962) {

  for (int i = 0; i < MAX_POSSIBLE_SERVOS; i++) {
    if (servoPins[i] < 0) {
      servos[i] = NULL;
      continue;
    }
    servos[i] = new Servo();
    servos[i]->attach(servoPins[i],1000,2000);
    servos[i]->write(90);
  }
}

ServoServer::~ServoServer() {
  // TODO Auto-generated destructor stub
}


//User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
void ServoServer::event(float *buffer) {
  uint8_t *bBuffer = (uint8_t *)buffer;
  //Serial.print("\r\n Servo Packet ");
  for (int i = 0; i < MAX_POSSIBLE_SERVOS; i++) {
    if (servoPins[i] < 0) {
      continue;
    }
    int value = bBuffer[i];
    //Serial.print("[ "+String(i)+" , "+String(servoPins[i])+" , "+String(value)+" ]");

    //if(value>0&& value<254)
    	servos[i]->write(constrain(value, 0, 180));
  }
}
