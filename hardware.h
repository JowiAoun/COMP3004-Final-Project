#ifndef HARDWARE_H
#define HARDWARE_H

#include <QVector>

#include "control.h"
#include "healthData.h"
#include "rawHealthData.h"

class Hardware {
 public:
  Hardware(int hardwareid);

  int battery = 0;
  int hardwareid = 1;
  bool powerConnected = false;

  RawHealthData* takeMeasurements();

  bool isLowPower();
  bool isCriticalPower();
  bool gracefulShutdown();
  bool connectionLoss();
  bool setBatteryPower(int power);
  int getBattery() const;



		QVector<int> rawdata; // a series of number values for each Hn from H1 to H6 then F1 to F6
};

#endif
