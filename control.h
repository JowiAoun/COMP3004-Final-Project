#ifndef CONTROL_H
#define CONTROL_H

#include <string>

#include "QDebug"
#include "QVector"
#include "hardware.h"
#include "healthData.h"
#include "rawHealthData.h"
#include "user.h"

class Control {
 public:
  Control();
  ~Control();

  // Getters
  User* getCurrentUser();
  User getUserByEmail(QString email);

  // Validity Checkers
  int getUserIndex(QString email);
  bool doesUserExist(QString email);

  // CRUD Methods
  void addUser(User user);
  void deleteUser(QString email);
  void updateUser(QString email, const User& user);
  void saveUser(QString email, const User& user);
  // bool login(QString email, QString password);

  // Authentication Methods
  bool login(QString email);
  bool createAccount(QString email, QString password, QString name, int age, QString gender,
                     float height, float weight);

  // Data Processing Methods
  HealthData* processData(const RawHealthData& rawHealthData);
  void displayHistoricalData(const QVector<HealthData>& historicalData);

  // Hardware Methods
  bool connectToHardware(Hardware* hardware);
  bool disconnectFromHardware(Hardware* hardware);

  bool createNewScan(const Hardware&);
  bool createCharts();

 private:
  Hardware* connectedHardware;
  QVector<User> allUsers;
  User* currentUser;
};

#endif
