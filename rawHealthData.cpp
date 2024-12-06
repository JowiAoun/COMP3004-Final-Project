#include "rawHealthData.h"

RawHealthData::RawHealthData() : measurements{20, 21, 23, 25, 25, 25, 25, 25, 25, 25}{

}

RawHealthData::~RawHealthData() {

}

int* RawHealthData::getMeasurements() {
    return this->measurements;
}
