#include "hardware.h"

#include "control.h"


Hardware::Hardware(int hardwareid)
    : battery(100),
      hardwareid(hardwareid),         // Initialize battery level
      powerConnected(true)  // Initialize power status
{}

RawHealthData* Hardware::takeMeasurements() {
  // Create new HealthData object with simulated measurements
  RawHealthData* rawhealth = new RawHealthData();

  // Simulate taking measurements and populate healthData

  // Deplete battery using random number from 1 to 10
  this->battery -= (rand() % 10) - 1;

  // Ensure battery doesn't go below 0
  this->battery = std::max(0, this->battery);

  return rawhealth;
}

bool Hardware::setBatteryPower(int power) {
  // Add validation
  if (power < 0 || power > 100) {
    return false;
  }
  this->battery = power;
  return true;
}

bool Hardware::isLowPower() { return (this->battery <= 15 && this->battery > 5); }

bool Hardware::isCriticalPower() { return (this->battery <= 5); }

bool Hardware::gracefulShutdown() {
  try {

    // disconnect hardware
    this->powerConnected = false;

    // any additional cleanup here

    exit(0);
    return true;
  } catch (const std::exception& e) {
    // Log the exception
    printf("Exception ouccrred: ");
    printf(e.what());

    return false;
  }
}

int Hardware::getBattery() const {
	return this->battery;
}


bool Hardware::connectionLoss() {
  // Add actual connection checking logic
  return !this->powerConnected;
}
