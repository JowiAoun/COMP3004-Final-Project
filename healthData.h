#ifndef HEALTHDATA_H
#define HEALTHDATA_H

#include <ctime>
#include <QString>

class HealthData {
  public:
    HealthData(float energyLevel, float immuneSystem, float metabolism, 
               float psychoEmotionalState, float musculoskeletalSystem);
    ~HealthData();

    float  getEnergyLevel() const;
    float  getImmuneSystem() const;
    float  getMetabolism() const;
    float  getPsychoEmotionalState() const;
    float  getMusculoskeletalSystem() const;
    time_t getCreatedOn() const;

    float  getAverage() const;
    QString displayData() const;

  private:
    float  energyLevel;
    float  immuneSystem;
    float  metabolism;
    float  psychoEmotionalState;
    float  musculoskeletalSystem;
    time_t createdOn;
};

#endif // HEALTHDATA_H
