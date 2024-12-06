#include "hardware.h"

Hardware::Hardware(int hardwareid): hardwareid(hardwareid) {};


HealthData* Hardware::takeMeasurements() {
	// im gonna simulate fake data being inputted since im not sure how were
	// gonna get actual measurements from the device
	
	QVector 

	HealthData cleandata = new HealthData();
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

bool connectionLoss() {
	return this->powerConnected;
}

