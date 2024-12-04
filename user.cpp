#include "user.h"

User::User(QString name, QString gender, int age, float weight, float height) {
  this->name = name;
  this->gender = gender;
  this->age = age;
  this->weight = weight;
  this->height = height;
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
QString User::setGender() {
  this-gender = gender;
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

float User::setHeight() const {
  return this->height;
}
float User::getHeight(float height) {
  this->height = height;
}