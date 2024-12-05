#ifndef CONTROL_H
#define CONTROL_H

#include "user.h"
#include "hardware.h"
#include "healthdata.h"
#include "QVector"
#include "QDebug"

class Control {
    public:
        Control();
        ~Control();

        void addUser(const User& user);
        void deleteUser(const QString& name);
        void updateUser(const QString& name, const User& user);
        //HealthData* processData(SomeRawData);
        void displayHistoricalData(const QVector<HealthData>& historicalData);

        bool connectToHardware(Hardware* hardware);
        // disconnect?
        bool createNewScan();
        bool createCharts();
        void listScans(const User& user);
    private:
        QVector<Hardware*> connectedHardware;

}

#endif

