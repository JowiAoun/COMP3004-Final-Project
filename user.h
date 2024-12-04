#ifndef USER_H
#define USER_H

#include "QString"

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
    QString name
    QString gender
    int     age
    float   weight
    float   height
}

#endif // USER_H
