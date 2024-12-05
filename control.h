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
        void deleteUser(QString name);
        void updateUser(QString name, const User& user);
        bool login(QString username, QString password);
        bool createAccount(QString username, QString password, QString name, int age, QString gender, float height, float weight);

        //HealthData* processData(SomeRawData);
        void displayHistoricalData(const QVector<HealthData>& historicalData);

        bool connectToHardware(Hardware* hardware);
        // disconnect?
        bool createNewScan();
        bool createCharts();
        void listScans(const User& user);
    private:
        QVector<Hardware*> connectedHardware;
        QVector<User*> currentUser;

}

#endif

