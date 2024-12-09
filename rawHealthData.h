#ifndef RAWHEALTHDATA_H
#define RAWHEALTHDATA_H

const int SKIN_CONTACT_POINTS = 24;
const int NUM_DATA = 10;

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
