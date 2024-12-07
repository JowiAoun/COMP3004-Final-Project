#ifndef CONTROL_H
#define CONTROL_H

#include "user.h"
#include "hardware.h"
#include "healthdata.h"
#include "rawHealthData.h"

#include "QVector"
#include "QDebug"

class Control {
    public:
        Control();
        ~Control();

        void addUser(const User& user);
        void deleteUser(QString email);
        void updateUser(QString email, const User& user);
        // bool login(QString email, QString password);
        bool login(QString email);
        bool createAccount(QString email, QString password, QString name, int age, QString gender, float height, float weight);

        HealthData* processData(const RawHealthData& rawHealthData);
        void displayHistoricalData(const QVector<HealthData>& historicalData);

        bool connectToHardware(Hardware* hardware);
        // bool disconnectFromHardware(Hardware* hardware);

        bool createNewScan();
        bool createCharts();
    private:
        Hardware* connectedHardware;
        QVector<User*> allUsers;
        User* currentUser;

}

#endif

