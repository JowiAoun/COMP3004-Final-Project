#include "control.h"
namespace{
    const std::string filepath = "users.txt";
}
Control::Control(): currentUser(NULL), connectedHardware(NULL) {
    allUsers = loadUsersFromFile(filepath);

}

Control::~Control() {

    int userSize = allUsers.size();
    for (int i=0; i<userSize; i++) {
        //delete allUsers[i];
    }
    if (connectedHardware != NULL) {
        delete connectedHardware;
    }
    currentUser = NULL;
}

void Control::addUser(User user) {
    allUsers.append(User(user.getEmail(), user.getName(), user.getGender(), user.getAge(), user.getWeight(), user.getHeight()));
    saveUsersToFile(allUsers, filepath);
    qDebug() << "Added user " << user.getName();
}

void Control::deleteUser(QString email) {
    bool userExists = false;
    QString name = "";
    for (int i=0; i<allUsers.size(); i++) {
        if (allUsers[i].getEmail() == email) {
            if (allUsers[i].getEmail() == currentUser->getEmail()) {
                currentUser = NULL;
                qDebug() << "Current user account deleted. Log in again";
            }

            name = allUsers[i].getName();
            allUsers.remove(i);
            userExists = true;
            
            break;
        }
    }
    if (userExists == false) {
        throw std::runtime_error("User does not exist");
    }
    saveUsersToFile(allUsers, filepath);
    qDebug() << "Deleted user " << name;

}

void Control::updateUser(QString email, const User& user) {
    bool userExists = false;
    QString name = "";
    for (int i=0; i<allUsers.size(); i++) {
        if (allUsers[i].getEmail() == email) {
            name = allUsers[i].getName();
            allUsers[i].setEmail(user.getEmail());
            allUsers[i].setName(user.getName());
            allUsers[i].setGender(user.getGender());
            allUsers[i].setAge(user.getAge());
            allUsers[i].setWeight(user.getWeight());
            allUsers[i].setHeight(user.getHeight());
            userExists = true;
            break;
        }
    }
    if (userExists == false) {
        throw std::runtime_error("User does not exist");
    }
    saveUsersToFile(allUsers, filepath);
    qDebug() << "Updated user " << name;
}


bool Control::login(QString email) {
    bool loggedIn = false;
    for (int i=0; i<allUsers.size(); i++) {
        if (allUsers[i].getEmail() == email) {
            currentUser = &allUsers[i];
            loggedIn = true;
            qDebug() << "Logged in as user " << allUsers[i].getName();
            break;
        }
    }
    if (loggedIn == false) {
        throw std::runtime_error("Authentication error");
    }
    return true;
}

bool Control::createAccount(QString email, QString password, QString name, int age, QString gender, float height, float weight) {
    bool userExists = false;
    // if user already exists
    for (int i=0; i<allUsers.size(); i++) {
        if (allUsers[i].getEmail() == email) {
            qDebug() << "User already exists: " << allUsers[i].getEmail();
            userExists = true;
            return false;
        }
    }
    // otherwise add new user
    if (userExists == false) {
        addUser(User(email, name, gender, age, weight, height));
    }
    return true;
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
    if (connectedHardware != NULL) {
        delete connectedHardware;
    }
    connectedHardware = hardware;
    return true;
}

bool Control::disconnectFromHardware(Hardware* hardware) {
    // for graceful shutdown??
}

bool Control::createNewScan(const Hardware& hardware) {
    // TODO: class
    //RawHealthData rawData = hardware.takeMeasurements();
    //HealthData* processedData = processData(rawData);
    // TODO: handle currentUser 
    // QVector<HealthData*> historicalData = currentUser...
    //createCharts(historicalData);
    //displayHistoricalData();
    // TODO
}


bool Control::createCharts() {
    // TODO

}

