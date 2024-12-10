#ifndef USER_H
#define USER_H

#include "QString"
#include "QVector"
#include "QDebug"
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
    User(QString email, QString name, QString gender, QString age, QString weight, QString height);
    User(QString email, QString name, QString gender, QString age, QString weight, QString height, QVector<HealthData>);
    ~User();

    QString getEmail() const;
    void setEmail(QString email);

    QString getName() const;
    void setName(QString name);

    QString getGender() const;
    void setGender(QString gender);

    QString getAge() const;
    void setAge(QString age);

    QString getWeight() const;
    void setWeight(QString weight);

    QString getHeight() const;
    void setHeight(QString height);

    QVector<HealthData> getHistoricalHealthData();
    void setHistoricalHealthData(QVector<HealthData> historicalHealthData);

  private:
    QString email;
    QString name;
    QString gender;
    QString age;
    QString weight;
    QString height;
    QVector<HealthData> historicalHealthData;

    // Allow serialization access to private members
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version);
};

void saveUsersToFile(const QVector<User>& users, const std::string& filename);
QVector<User> loadUsersFromFile(const std::string& filename);

#endif // USER_H
