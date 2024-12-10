#include "control.h"

namespace {
const std::string filepath = "users.txt";
}

Control::Control() : currentUser(NULL), connectedHardware(NULL) {
  allUsers = loadUsersFromFile(filepath);
}

Control::~Control() {
  int userSize = allUsers.size();
  for (int i = 0; i < userSize; i++) {
    // delete allUsers[i];
  }
  if (connectedHardware != NULL) {
    delete connectedHardware;
  }
  currentUser = NULL;
}

User* Control::getCurrentUser() {
  return (this->currentUser);
}

bool Control::doesUserExist(QString email) {
  bool userExists = false;

  for (int i = 0; i < allUsers.size(); i++) {
    if (allUsers[i].getEmail() == email) {
      userExists = true;
      break;
    }
  }

  if (userExists == false) {
    QDebug() << "User does not exist";
    return false;
  }

  return true;
}

int Control::getUserIndex(QString email) {
  for (int i = 0; i < allUsers.size(); i++) {
    if (allUsers[i].getEmail() == email) {
      return i;
    }
  }

  throw std::runtime_error("User does not exist");
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
  if (doesUserExist(user.getEmail())) {
    qDebug() << "User with email " << user.getEmail()
             << " already exists, skipping addUser call." return;
  }

  allUsers.append(User(user.getEmail(), user.getName(), user.getGender(), user.getAge(),
                       user.getWeight(), user.getHeight()));

  saveUsersToFile(allUsers, filepath);
  qDebug() << "Added user " << user.getName();
}

void Control::updateUser(QString email, const User& user) {
  if (!doesUserExist(email)) return;

  user.setEmail(user.getEmail());
  user.setName(user.getName());
  user.setGender(user.getGender());
  user.setAge(user.getAge());
  user.setWeight(user.getWeight());
  user.setHeight(user.getHeight());
  
  saveUsersToFile(allUsers, filepath);
  qDebug() << "Updated user " << user.getName();
}

bool Control::saveUser(QString email, const User& user) {
  if (!doesUserExist(email)) {
    qDebug() << "User with email " << email << " does not exist, skipping deleteUser call."
             << "Throwing runtime error...";

    throw std::runtime_error("User does not exist");

    return;
  }

  name = user.getName();
  user.setEmail(user.getEmail());
  user.setName(user.getName());
  user.setGender(user.getGender());
  user.setAge(user.getAge());
  user.setWeight(user.getWeight());
  user.setHeight(user.getHeight());

  saveUsersToFile(allUsers, filepath);
  qDebug() << "Updated user " << name;
}

void Control::deleteUser(QString email) {
  if (!doesUserExist(email)) {
    qDebug() << "User with email " << email << " does not exist, skipping deleteUser call."
             << "Throwing runtime error...";

    throw std::runtime_error("User does not exist");

    return;
  }

  if (email == currentUser->getEmail()) {
    currentUser = NULL;
    qDebug() << "Current user account deleted. Log in again";
  }

  User user = Control::getUserByEmail(email);
  int userIndex = Control::getUserIndex(email);

  name = user.getName();
  allUsers.remove(userIndex);

  saveUsersToFile(allUsers, filepath);
  qDebug() << "Deleted user " << name;
}

bool Control::login(QString email) {
  bool loggedIn = false;
  for (int i = 0; i < allUsers.size(); i++) {
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

bool Control::createAccount(QString email, QString password, QString name, int age, QString gender,
                            float height, float weight) {
  bool userExists = false;
  // if user already exists
  for (int i = 0; i < allUsers.size(); i++) {
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
  for (int i = 0; i < historicalData.size(); i++) {
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
  // RawHealthData rawData = hardware.takeMeasurements();
  // HealthData* processedData = processData(rawData);
  // TODO: handle currentUser
  // QVector<HealthData*> historicalData = currentUser...
  // createCharts(historicalData);
  // displayHistoricalData();
  // TODO
}

bool Control::createCharts() {
  // TODO
}
