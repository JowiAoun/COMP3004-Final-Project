#include "healthData.h"

#include <QString>
#include <QDateTime>

HealthData::HealthData(float energyLevel, float immuneSystem, float metabolism, 
                       float psychoEmotionalState, float musculoskeletalSystem)
    : energyLevel(energyLevel),
      immuneSystem(immuneSystem),
      metabolism(metabolism),
      psychoEmotionalState(psychoEmotionalState),
      musculoskeletalSystem(musculoskeletalSystem),
      createdOn(std::time(nullptr))
{}

HealthData::~HealthData() {}

float  HealthData::getEnergyLevel() const { return this->energyLevel; }
float  HealthData::getImmuneSystem() const { return this->immuneSystem; }
float  HealthData::getMetabolism() const { return this->metabolism; }
float  HealthData::getPsychoEmotionalState() const { return this->psychoEmotionalState; }
float  HealthData::getMusculoskeletalSystem() const { return this->musculoskeletalSystem; }
time_t HealthData::getCreatedOn() const { return this->createdOn; }

float HealthData::getAverage() const {
    return (energyLevel + immuneSystem + metabolism + 
            psychoEmotionalState + musculoskeletalSystem) / 5.0f;  //TODO: Define a proper average
}

QString HealthData::displayData() const {
    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(createdOn);
    QString formattedDate = dateTime.toString("yyyy-MM-dd HH:mm:ss");

    return QString(
        "Health Data:\n"
        "Energy Level: %1\n"
        "Immune System: %2\n"
        "Metabolism: %3\n"
        "Psycho-Emotional State: %4\n"
        "Musculoskeletal System: %5\n"
        "Average Score: %6\n"
        "Created On: %7")
        .arg(energyLevel)
        .arg(immuneSystem)
        .arg(metabolism)
        .arg(psychoEmotionalState)
        .arg(musculoskeletalSystem)
        .arg(getAverage())
        .arg(formattedDate);
}