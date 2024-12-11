#ifndef RAWHEALTHDATA_H
#define RAWHEALTHDATA_H

#include "QString"
#include <QRandomGenerator>


const int SKIN_CONTACT_POINTS = 24;
const int NUM_DATA = 10;

const int measurements[24][10];
const int lowerBound = 5;
const int upperBounds[24] = { 191, 191, 171, 171, 151, 151, 171, 171, 201, 201, 201, 201, 161, 161, 131, 131, 151, 151, 151,151,  131, 131, 151, 151};
// QString skinContactPoints[24] = { "H1-L", "H1-R", "H2-L", "H2-R", "H3-L", "H3-R", "H4-L", "H4-R", "H5-L", "H5-R", "H6-L", "H6-R", 
//                                   "F1-L", "F1-R", "F2-L", "F2-R", "F3-L", "F3-R", "F4-L", "F4-R", "F5-L", "F5-R", "F6-L", "F6-R"};

class RawHealthData {
  public:
    RawHealthData();
    RawHealthData(int[SKIN_CONTACT_POINTS][NUM_DATA]);
    ~RawHealthData();

    int (*getMeasurements()) [NUM_DATA] ;

  private:
    int measurements[SKIN_CONTACT_POINTS][NUM_DATA];
};

#endif // RAWHEALTHDATA_H
