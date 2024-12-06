#ifndef RAWHEALTHDATA_H
#define RAWHEALTHDATA_H

class RawHealthData {
  public:
    RawHealthData();
    ~RawHealthData();

    int* getMeasurements();

  private:
    int measurements[10];
};

#endif // RAWHEALTHDATA_H
