#include "rawHealthData.h"

RawHealthData::RawHealthData() {   
    int measurements[24][10];
    int lowerBound = 5;
    int upperBounds[24] = { 191, 191, 171, 171, 151, 151, 171, 171, 201, 201, 201, 201, 161, 161, 131, 131, 151, 151, 151,151,  131, 131, 151, 151};
    // QString skinContactPoints[24] = { "H1-L", "H1-R", "H2-L", "H2-R", "H3-L", "H3-R", "H4-L", "H4-R", "H5-L", "H5-R", "H6-L", "H6-R", 
    //                                   "F1-L", "F1-R", "F2-L", "F2-R", "F3-L", "F3-R", "F4-L", "F4-R", "F5-L", "F5-R", "F6-L", "F6-R"};
 
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
