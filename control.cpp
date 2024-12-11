#define C_HEALTHY_BATTERY 0
#define C_LOW_POWER_BATTERY 1
#define C_CRITICAL_BATTERY 2

#include "hardware.h"
#include "control.h"

namespace{
    const std::string filepath = "users.txt";
}
Control::Control(): currentUser(NULL), connectedHardware(NULL) {
    allUsers = loadUsersFromFile(filepath);
}

Control::~Control() {

    int userSize = allUsers.size();
    for (int i=0; i<userSize; ++i) {
        //delete allUsers[i];
    }
    if (connectedHardware != NULL) {
        delete connectedHardware;
    }
    currentUser = NULL;
}

User* Control::getCurrentUser() {
  return (this->currentUser);
}


User Control::getUserByEmail(QString email) {
  for (int i = 0; i < allUsers.size(); i++) {
    if (allUsers[i].getEmail() == email) {
      return allUsers[i];
    }
  }

  throw std::runtime_error("User does not exist");
}

void Control::addUser(User user) {
    if (allUsers.size() >= 5) {
        qDebug() << "5 user limit reached";
    }
    allUsers.append(User(user.getEmail(), user.getName(), user.getGender(), user.getAge(), user.getWeight(), user.getHeight()));
    saveUsersToFile(allUsers, filepath);
    qDebug() << "Added user " << user.getName();
}

void Control::deleteUser(QString email) {
    bool userExists = false;
    QString name = "";
    for (int i=0; i<allUsers.size(); ++i) {
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
    for (int i=0; i<allUsers.size(); ++i) {
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
    for (int i=0; i<allUsers.size(); ++i) {
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

bool Control::createAccount(QString email, QString name, QString age, QString gender, QString height, QString weight) {
    bool userExists = false;
    // if user already exists
    for (int i=0; i<allUsers.size(); ++i) {
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

HealthData* Control::processData(RawHealthData& rawHealthData) {
    /*if (rawHealthData == NULL) {
        throw std::runtime_error("RawHealthData data validation failed");
    }*/
    //get only the last measurement from each 24 skin contact points
    int measurements24[SKIN_CONTACT_POINTS];
    for (int i=0; i<SKIN_CONTACT_POINTS; ++i) {
        measurements24[i] = rawHealthData.getMeasurements()[i][NUM_DATA-1];
    }

    // map into healthData
    float energyLevel = 0.0f;
    float immuneSystem = 0.0f;
    float metabolism = 0.0f;
    float psychoEmotionalState = 0.0f;
    float musculoskeletalSystem = 0.0f;

    for (int i=0; i<SKIN_CONTACT_POINTS; ++i) {
        energyLevel += measurements24[i]/3.0f;
        immuneSystem += measurements24[i]/50.0f;
        metabolism += measurements24[i]/100.0f;
        psychoEmotionalState += measurements24[i]/150.0f;
        musculoskeletalSystem += measurements24[i]/90.0f;
    }

    energyLevel /= SKIN_CONTACT_POINTS;
    immuneSystem /=SKIN_CONTACT_POINTS;
    metabolism /= SKIN_CONTACT_POINTS;
    psychoEmotionalState /= SKIN_CONTACT_POINTS;
    musculoskeletalSystem /= SKIN_CONTACT_POINTS;

    HealthData* healthData = new HealthData(energyLevel, immuneSystem, metabolism, 
            psychoEmotionalState, musculoskeletalSystem);

    return healthData;
}

bool Control::saveHealthData(const HealthData& healthData) {
    QVector<HealthData> currentHistoricData = currentUser->getHistoricalHealthData();
    currentHistoricData.append(healthData);
    if (currentUser==NULL) {
        throw std::runtime_error("Does not have a Current User");
    }
    currentUser->setHistoricalHealthData(currentHistoricData);
    saveUsersToFile(allUsers, filepath);
    return true;
}

void Control::displayHistoricalData(const QVector<HealthData>& historicalData) {
    for (int i=0; i<historicalData.size(); ++i) {
        historicalData[i].displayData();
    }
    // TODO: what else?
}

bool Control::connectToHardware(Hardware* hardware) {
    if (hardware == NULL) {
        throw std::runtime_error("Hardware NULL");
    }
    if (connectedHardware != NULL) {
        delete connectedHardware;
    }
    connectedHardware = hardware;
    return true;
}

bool Control::disconnectFromHardware() {
    if (connectedHardware != NULL) {
      delete connectedHardware;
      connectedHardware = NULL;
    }
    return true;
}

int Control::getBatteryStatus() const {
    if (connectedHardware == NULL) {
        throw std::runtime_error("No connected Hardware");
    }
    if (connectedHardware->isCriticalPower()) {
        qDebug() << "Critical Power:" << connectedHardware->getBattery();
        qDebug() << "Shutting down..." ;
        return C_CRITICAL_BATTERY;
    }
    if (connectedHardware->isLowPower()) {
        qDebug() << "Low Power warning:" << connectedHardware->getBattery();
        return C_LOW_POWER_BATTERY;
    }
    qDebug() << "Healthy Battery:" << connectedHardware->getBattery();
    // TODO: send info to ui?
    return C_HEALTHY_BATTERY;
}

    // TODO:
    // 1. get info from hardware
    // 2. select profile (must happen prior to this method)
    // 3. measure each skin point
    // 4. processData
    // 5. save to user
    // 6. display?

RawHealthData* Control::startNewScan() {
    if (connectedHardware == NULL) {
        throw std::runtime_error("No connected Hardware");
    }

    if (getBatteryStatus() == 0) {
        connectedHardware->gracefulShutdown();
        disconnectFromHardware();
        return NULL;
    }
    if (currentUser == NULL) {
        throw std::runtime_error("User not selected");
    }
    else {
        RawHealthData* rawHealthData = connectedHardware->takeMeasurements();
        return rawHealthData;
    }
    return NULL;
}

bool Control::receiveNewScan(RawHealthData& rawData) {
    if (currentUser == NULL) {
        throw std::runtime_error("User not selected");
    }
    HealthData* processedData = processData(rawData);
    if (processedData == NULL) {
        throw std::runtime_error("Data Processing error");
    }
    if (saveHealthData(*processedData)) {
        QVector<HealthData> historicalData = currentUser->getHistoricalHealthData();
        displayHistoricalData(historicalData);
        // TODO:
        createCharts();
        delete processedData;
        return true;
    }
    delete processedData;
    return false;
}
 


bool Control::createCharts() {
    // TODO

    return false;
}

void Control::setCurrentUser(User* user) {
    this->currentUser = user;
    if (currentUser != NULL) {
        qDebug() << "Current user set to " << user->getName();
    }
}

void Control::deleteCurrentUser() {
    if (currentUser == NULL) {
        qDebug() << "No current user";
        return;
    }

    auto it = std::find_if(allUsers.begin(), allUsers.end(),
                           [this](const User& user) {
                               return &user == this->currentUser;
                           });

    if (it != allUsers.end()) {
        int index = std::distance(allUsers.begin(), it);
        // Remove the object
        allUsers.removeAt(index);
    }

    setCurrentUser(NULL);
    saveUsers();
}


void Control::saveUsers() {
    saveUsersToFile(allUsers, filepath);
}

