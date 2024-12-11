#include "rawHealthData.h"

RawHealthData::RawHealthData() {    
    for (int i=0; i< SKIN_CONTACT_POINTS; ++i) {
        // each point gets 10 numbers
        for (int j=0; j< NUM_DATA; ++j) {
            measurements[i][j] = QRandomGenerator::global()->bounded(lowerBound, upperBounds[i]);
        }
    }

}

RawHealthData::RawHealthData(int newMeasurements[SKIN_CONTACT_POINTS][NUM_DATA]) {
    for (int i=0; i<SKIN_CONTACT_POINTS; ++i) {
        for (int j=0; j<NUM_DATA; ++j) {
            measurements[i][j] = newMeasurements[i][j]; 
        }
    }
}

RawHealthData::~RawHealthData() {

}

int (*RawHealthData::getMeasurements()) [NUM_DATA] {
    return this->measurements;
}
