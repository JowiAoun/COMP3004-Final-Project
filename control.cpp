#include "control.h"

static const std::string filepath = "users.txt";

Control::Control() {}

Control::~Control() {
    for (Hardware* hardware : connectedHardware) {
        delete hardware;
    }
    for (User* user : currentUser) {
        delete user;
    }
}

void Control::addUser(const User& user) {
    QVector<User> users = loadUsersFromFile(filepath);
    users.append(user);
    saveUsersToFile(users, filepath);
    qDebug() << "Added user " << user.getName();
}

void Control::deleteUser(QString name) {
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
    saveUsersToFile(users, filepath);
    qDebug() << "Deleted user " << name;

}

void Control::updateUser(QString name, const User& user) {
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
    saveUsersToFile(users, filepath);
    qDebug() << "Updated user " << name;

}

bool Control::login(QString username, QString password) {
    bool loggedIn = false;
    QVector<User> users = loadUsersFromFile(filepath);
    for (int i=0; i<users.size(); i++) {
        if (users[i].getName() == name) {
            currentUser.append(users[i]);
            loggedIn = true;
            qDebug() << "Logged in as user " << name;
            break;
        }
    }
    if (loggedIn == false) {
        throw std::runtime_error("Wrong credentials");
    }

}

bool Control::createAccount(QString username, QString password, QString name, int age, QString gender, float height, float weight) {
    // TODO: need username and password variables in User
    User newUser = new User(username, password, name, gender, age, weight, height);
    addUser(user);
}

HealthData* Control::processData(const RawHealthData& rawHealthData) {
    // TODO
}

void Control::displayHistoricalData(const QVector<HealthData>& historicalData) {
    for (int i=0; i<historicalData.size(); i++) {
        historicalData[i].displayData();
    }
    // what else
}

bool Control::connectToHardware(Hardware* hardware) {
    if (hardware == NULL) {
        return false;
    }
    connectedHardware.append(hardware);
    return true;
}

bool Control::createNewScan(const Hardware& hardware) {
    // TODO: class
    RawHealthData rawData = hardware.takeMeasurements();
    HealthData* processedData = processData(rawData);
    // TODO: handle currentUser 
    QVector<HealthData*> historicalData = currentUser...
    createCharts(historicalData);
    displayHistoricalData();
    // TODO
}


bool Control::createCharts() {

}

