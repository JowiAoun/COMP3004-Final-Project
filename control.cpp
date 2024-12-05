#include "control.h"

static const std::string filepath = "users.txt";

Control::Control() {}

Control::~Control() {
    for (Hardware* hardware : connectedHardware) {
        delete hardware;
    }
}

void Control::addUser(const User& user) {
    QVector<User> users = loadUsersFromFile(filepath);
    users.append(user);
    saveUsersToFile(users, filepath);
    qDebug() << "Added user " << user.getName();
}

void Control::deleteUser(const QString& name) {
    bool userExists = false;
    QVector<User> users = loadUsersFromFile(filepath);
    for (int i=0; i<users.size(); i++) {
        if (users[i].getName() == name) {
            users.remove(i);
            userExists = true;
            break;
        }
    }
    if (userExists == false) {
        throw std::runtime_error("User does not exist");
    }
    qDebug() << "Deleted user " << name;
    saveUsersToFile(users, filepath);
}

void Control::updateUser(const QString& name, const User& user) {
    bool userExists = false;
    QVector<User> users = loadUsersFromFile(filepath);
    for (int i=0; i<users.size(); i++) {
        if (users[i].getName() == name) {
            users.replace(i, user);
            userExists = true;
            break;
        }
    }
    if (userExists == false) {
        throw std::runtime_error("User does not exist");
    }
    qDebug() << "Updated user " << name;
    saveUsersToFile(users, filepath);
}

// HealthData* Control::processData(rawdata? ) {
// }

void Control::displayHistoricalData(const QVector<HealthData>& historicalData) {
    for (int i=0; i<historicalData.size(); i++) {
        historicalData[i].displayData();
    }
}

bool Control::connectToHardware(Hardware* hardware) {
    connectedHardware.append(hardware);
}

bool Control::createNewScan() {
}
bool Control::createCharts() {}


void Control::listScans(const User& user) {
    // displayHistoricalData();
}