#ifndef USER_H
#define USER_H

#include "QString"
#include "QVector"
#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <stdexcept>

#include "healthData.h"

class User {
  public:
    User();
    User(QString email, QString name, QString gender, int age, float weight, float height);
    User(QString email, QString name, QString gender, int age, float weight, float height, QVector<HealthData>);
    ~User();

    QString getEmail() const;
    void setEmail(QString email);

    QString getName() const;
    void setName(QString name);

    QString getGender() const;
    void setGender(QString gender);

    int getAge() const;
    void setAge(int age);

    float getWeight() const;
    void setWeight(float weight);

    float getHeight() const;
    void setHeight(float height);

    QVector<HealthData> getHistoricalHealthData();
    void setHistoricalHealthData(QVector<HealthData> historicalHealthData);

  private:
    QString email;
    QString name;
    QString gender;
    int     age;
    float   weight;
    float   height;
    QVector<HealthData> historicalHealthData;

    // Allow serialization access to private members
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version);
};

void saveUsersToFile(const QVector<User>& users, const std::string& filename);
QVector<User> loadUsersFromFile(const std::string& filename);

#endif // USER_H
