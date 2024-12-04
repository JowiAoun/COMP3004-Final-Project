#include "user.h"

User::User() {
  this->name = QString("");
  this->gender = QString("");
  this->age = 0;
  this->weight = 0;
  this->height = 0;
}

User::User(QString name, QString gender, int age, float weight, float height) {
  this->name = name;
  this->gender = gender;
  this->age = age;
  this->weight = weight;
  this->height = height;
}

User::~User() {

}

QString User::getName() const {
  return this->name;
}
QString User::setName(QString name) {
  this->name = name;
}

QString User::getGender() const {
  return this->gender;
}
QString User::setGender(QString gender) {
  this->gender = gender;
}

int User::getAge() const {
  return this->age;
}
int User::setAge(int age) {
  this->age = age;
}

float User::getWeight() const {
  return this->weight;
}
float User::setWeight(float weight) {
  this->weight = weight;
}

float User::getHeight() const {
  return this->height;
}
float User::setHeight(float height) {
  this->height = height;
}

template<class Archive>
void User::serialize(Archive& ar, const unsigned int version) {
    std::string nameStd = name.toStdString();
    std::string genderStd = gender.toStdString();

    ar & nameStd;
    ar & genderStd;
    ar & age;
    ar & weight;
    ar & height;

    if constexpr (Archive::is_loading::value) {
        name = QString::fromStdString(nameStd);
        gender = QString::fromStdString(genderStd);
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
    if (!ifs) throw std::runtime_error("Unable to open file for reading");

    boost::archive::text_iarchive ia(ifs);
    std::vector<User> stdUsers;
    ia >> stdUsers;

    return QVector<User>(stdUsers.begin(), stdUsers.end()); // Convert std::vector to QVectorstd::ifstream ifs(filename);
}
