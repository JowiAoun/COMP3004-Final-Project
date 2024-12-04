#include "mainwindow.h"
#include "user.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QVector<User> users;
    users.append(User("Alice", "Female", 25, 55.0f, 165.0f));
    users.append(User("Bob", "Male", 30, 70.0f, 175.0f));
    users.append(User("Charlie", "Non-Binary", 22, 65.0f, 170.0f));

    saveUsersToFile(users, "users_data.txt");

    QVector<User> loadedUsers = loadUsersFromFile("users_data.txt");

    for (const User& user : loadedUsers) {
        qDebug() << "Name:" << user.getName();
        qDebug() << "Gender:" << user.getGender();
        qDebug() << "Age:" << user.getAge();
        qDebug() << "Weight:" << user.getWeight();
        qDebug() << "Height:" << user.getHeight();
    }

    return 0;
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    */
}
