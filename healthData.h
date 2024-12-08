#ifndef HEALTHDATA_H
#define HEALTHDATA_H

#include <ctime>
#include <QString>
#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <stdexcept>

class HealthData {
  public:
    HealthData();
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

    // Allow serialization access to private members
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version);
};

#endif // HEALTHDATA_H
