#ifndef CONTROL_H
#define CONTROL_H


#include "user.h"
#include "healthData.h"
#include "rawHealthData.h"

#include <string>

#include "QVector"
#include "QDebug"

class Hardware;

class Control {
    public:
        Control();
        ~Control();

        // Getters
        User* getCurrentUser();
        User getUserByEmail(QString email);

        //CRUD
        void addUser(User user);
        void deleteUser(QString email);
        void updateUser(QString email, const User& user);
        void saveUser(QString email, const User& user);
        // Authentication
        bool login(QString email);
        bool createAccount(QString email, QString name, QString age, QString gender, QString height, QString weight);

        // Data processing
        HealthData* processData(RawHealthData& rawHealthData);
        bool saveHealthData(const HealthData& healthData);
        void displayHistoricalData(const QVector<HealthData>& historicalData);

        // Hardware
        bool connectToHardware(Hardware* hardware);
        bool disconnectFromHardware();
        int getBatteryStatus() const;

        RawHealthData* startNewScan() const;
        bool receiveNewScan(RawHealthData& rawData);
        bool createCharts();

        void deleteCurrentUser();

        void setCurrentUser(User* user);

        void saveUsers();
        User* currentUser;
        QVector<User> allUsers;
        Hardware* connectedHardware;

};

#endif
