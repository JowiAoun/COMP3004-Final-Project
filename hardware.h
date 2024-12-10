#ifndef HARDWARE_H
#define HARDWARE_H

#include <QVector>

#include "control.h"
#include "healthData.h"

class Hardware {
 public:
  Hardware(int hardwareid);

  int battery = 0;
  int hardwareid = 1;
  bool powerConnected = false;

  HealthData* takeMeasurements();

  bool isLowPower();
  bool isCriticalPower();
  bool gracefulShutdown(Control controlInstance);
  bool connectionLoss();
  const bool setBatteryPower(int power);


  QVector<int> rawdata;  // a series of number values for each Hn from H1 to H6 then F1 to F6
};

#endif
