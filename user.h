#ifndef USER_H
#define USER_H

#include "QString"
#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <stdexcept>

class User {
  public:
    User(QString name, QString gender, int age, float weight, float height);
    ~User();

    QString getName() const;
    QString setName(QString name);

    QString getGender() const;
    QString setGender(QString gender);

    int getAge() const;
    int setAge(int age);

    float getWeight() const;
    float setWeight(float weight);

    float setHeight() const;
    float getHeight(float height);
    
  private:
    QString name;
    QString gender;
    int     age;
    float   weight;
    float   height;

    // Allow serialization access to private members
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version);
}

#endif // USER_H
