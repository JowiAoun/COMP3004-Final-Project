#include "user.h"

User::User() {
  this->email = QString("");
  this->name = QString("");
  this->gender = QString("");
  this->age = 0;
  this->weight = 0;
  this->height = 0;
}

User::User(QString email, QString name, QString gender, int age, float weight, float height) {
  this->email = email;
  this->name = name;
  this->gender = gender;
  this->age = age;
  this->weight = weight;
  this->height = height;
}

User::User(QString email, QString name, QString gender, int age, float weight, float height, QVector<HealthData> historicalHealthData) {
  this->email = email;
  this->name = name;
  this->gender = gender;
  this->age = age;
  this->weight = weight;
  this->height = height;
  this->historicalHealthData = historicalHealthData;
}

User::~User() {

}

QString User::getEmail() const {
  return this->email;
}
void User::setEmail(QString email) {
  this->email = email;
}

QString User::getName() const {
  return this->name;
}
void User::setName(QString name) {
  this->name = name;
}

QString User::getGender() const {
  return this->gender;
}
void User::setGender(QString gender) {
  this->gender = gender;
}

int User::getAge() const {
  return this->age;
}
void User::setAge(int age) {
  this->age = age;
}

float User::getWeight() const {
  return this->weight;
}
void User::setWeight(float weight) {
  this->weight = weight;
}

float User::getHeight() const {
  return this->height;
}
void User::setHeight(float height) {
  this->height = height;
}

QVector<HealthData> User::getHistoricalHealthData() {
    return this->historicalHealthData;
}
void User::setHistoricalHealthData(QVector<HealthData> historicalHealthData) {
    this->historicalHealthData = historicalHealthData;
}

template<class Archive>
void User::serialize(Archive& ar, const unsigned int version) {
    std::string nameStd = name.toStdString();
    std::string genderStd = gender.toStdString();
    std::string emailStd = email.toStdString();

    ar & emailStd;
    ar & nameStd;
    ar & genderStd;
    ar & age;
    ar & weight;
    ar & height;

    // Convert QVector to std::vector for serialization
    std::vector<HealthData> healthDataVec(historicalHealthData.begin(), historicalHealthData.end());
    ar & healthDataVec;

    if constexpr (Archive::is_loading::value) {
        email = QString::fromStdString(emailStd);
        name = QString::fromStdString(nameStd);
        gender = QString::fromStdString(genderStd);
        historicalHealthData = QVector<HealthData>(healthDataVec.begin(), healthDataVec.end());
    }
}

void saveUsersToFile(const QVector<User>& users, const std::string& filename) {
    std::ofstream ofs(filename);
    if (!ofs) throw std::runtime_error("Unable to open file for writing");

    boost::archive::text_oarchive oa(ofs);
    std::vector<User> stdUsers(users.begin(), users.end()); // Convert QVector to std::vector
    oa << stdUsers;
}

QVector<User> loadUsersFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        qDebug() << "Unable to open file for reading. Creating new file.";
        QVector<User> users;
        saveUsersToFile(users, filename);
        return users;
    }

    boost::archive::text_iarchive ia(ifs);
    std::vector<User> stdUsers;
    ia >> stdUsers;

    return QVector<User>(stdUsers.begin(), stdUsers.end()); // Convert std::vector to QVectorstd::ifstream ifs(filename);
}
