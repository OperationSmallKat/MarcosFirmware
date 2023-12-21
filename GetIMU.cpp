/*
 * GetIMU.cpp
 *
 *  Created on: Jun 7, 2018
 *      Author: hephaestus
 */

#include "GetIMU.h"
#include <Wire.h>
//User function to be called when a packet comes in
// Buffer contains data from the packet cming in at the start of the function
// User data is written into the buffer to send it back
void GetIMU::event(float * buffer) {

  bufferINTERNAL[9]=bno->orientationY;
  bufferINTERNAL[10]=bno->orientationX;
  bufferINTERNAL[11]=bno->orientationZ;


	for (int i = 0; i < NUM_IMU_VALUES; i++) {
		buffer[i] = bufferINTERNAL[i];
	}
  //print();
}

void GetIMU::setXPosition(float x){
	bufferINTERNAL[12] =x;
}
void GetIMU::setYPosition(float y){
	bufferINTERNAL[13] =y;
}
void GetIMU::setZPosition(float z){
	bufferINTERNAL[14] =z;
}
float GetIMU::getLINEARACCEL_X() {
	return bufferINTERNAL[0];
}
float GetIMU::getLINEARACCEL_Y() {
	return bufferINTERNAL[1];
}
float GetIMU::getLINEARACCEL_Z() {
	return bufferINTERNAL[2];
}
float GetIMU::getGYROSCOPE_X() {
	return bufferINTERNAL[3];
}
float GetIMU::getGYROSCOPE_Y() {
	return bufferINTERNAL[4];
}
float GetIMU::getGYROSCOPE_Z() {
	return bufferINTERNAL[5];
}
float GetIMU::getGRAVITY_X() {
	return bufferINTERNAL[6];
}
float GetIMU::getGRAVITY_Y() {
	return bufferINTERNAL[7];
}
float GetIMU::getGRAVITY_Z() {
	return bufferINTERNAL[8];
}
float GetIMU::getEULER_azimuth() {
	return bufferINTERNAL[11];
}
float GetIMU::getEULER_elevation() {
	return bufferINTERNAL[10];
}
float GetIMU::getEULER_tilt() {
	return bufferINTERNAL[9];
}

void GetIMU::startSensor(EasyBNO055_ESP * _bno) {

	bno = _bno;
	Serial.println("BNO 055 started");

}
void GetIMU::print() {

	Serial.print("\r\n Euler= " + String(bufferINTERNAL[9]) + " , "
					+ String(bufferINTERNAL[10]) + " , "
					+ String(bufferINTERNAL[11]) + "\r\n ");
	/* Display calibration status for each sensor. */
	/*
	 uint8_t system, gyro, accel, mag = 0;
	 bno->getCalibration(&system, &gyro, &accel, &mag);
	 Serial.print("\r\n CALIBRATION: Sys=");
	 Serial.print(system, DEC);
	 Serial.print(" Gyro=");
	 Serial.print(gyro, DEC);
	 Serial.print(" Accel=");
	 Serial.print(accel, DEC);
	 Serial.print(" Mag=");
	 Serial.println(mag, DEC);
	 */
}
