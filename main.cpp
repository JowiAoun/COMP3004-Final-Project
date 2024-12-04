#include "mainwindow.h"
#include "user.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    User user("Alice", "Female", 25, 55.0f, 165.0f);

    std::string fileName = "user_data.txt";

    // Save user to file
    saveUserToFile(user, fileName);

    // Load user from file
    User loadedUser = loadUserFromFile(fileName);

    // Verify loaded data
    qDebug() << "Name:" << loadedUser.getName();
    qDebug() << "Gender:" << loadedUser.getGender();
    qDebug() << "Age:" << loadedUser.getAge();
    qDebug() << "Weight:" << loadedUser.getWeight();
    qDebug() << "Height:" << loadedUser.getHeight();
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    */
}
