#include "hardware.h"

Hardware::Hardware(int hardwareid): hardwareid(hardwareid) {

}


HealthData* Hardware::takeMeasurements() const{
	// im gonna simulate fake data being inputted since im not sure how were
	// gonna get actual measurements from the device
	
    //QVector;

    //HealthData cleandata = new HealthData();

	// deplete the device's battery by a random amount between the values of 1 and 10
	this->battery -= (rand() % 10) + 1;
}


bool Hardware::isLowPower() {
	return this->battery <= 15 and this->battery > 5;
}

bool Hardware::isCriticalPower() {
	return this->battery <= 5;
}

bool Hardware::gracefulShutdown() {
	// save user data
	

	exit(0);
	return true;
}

bool Hardware::connectionLoss() {
	return this->powerConnected;
}

