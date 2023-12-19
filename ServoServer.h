/*
 * ServoServer.h
 *
 *  Created on: Ded 30, 2022
 *      Author: kbisland
 */

#ifndef SRC_SERVOSERVER_H_
#define SRC_SERVOSERVER_H_
#include <stdint.h>
#include <SimplePacketComs.h>
#include <PacketEvent.h>
#include <ESP32Servo.h>
#include "pinmap_smallkat.h"

#define MAX_DUMMY_SERVO 4
#define MAX_SERVO 16
#define MAX_POSSIBLE_SERVOS (MAX_DUMMY_SERVO+MAX_SERVO)

class ServoServer : public PacketEventAbstract {
private :
  Servo * servos[MAX_POSSIBLE_SERVOS];
public:
	ServoServer();
	virtual ~ServoServer();
	//User function to be called when a packet comes in
	// Buffer contains data from the packet coming in at the start of the function
	// User data is written into the buffer to send it back
	void event(float * buffer);

};

#endif /* SRC_SERVOSERVER_H_ */
