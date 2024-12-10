#include "hardware.h"

Hardware::Hardware(int hardwareid): hardwareid(hardwareid) {

}

RawHealthData* Hardware::takeMeasurements() const{
	// im gonna simulate fake data being inputted since im not sure how were
	// gonna get actual measurements from the device
	
    //QVector;

    //HealthData cleandata = new HealthData();
}


bool Hardware::isLowPower() {
	return this->battery <= 15 and this->battery > 5;
}

bool Hardware::isCriticalPower() {
	return this->battery <= 5;
}

bool Hardware::gracefulShutdown() {
	exit(0);
	return true;
}

int Hardware::getBattery() const {
	return this->battery;
}


bool Hardware::connectionLoss() {
	return this->powerConnected;
}

