#include "MainWindow.h"
#include "user.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QVector<User> users;

    // Add users to the QVector
    users.append(User("jane.doe@example.com", "Jane Doe", "Female", 28, 65.0, 170.0));
    users.append(User("john.smith@example.com", "John Smith", "Male", 35, 80.0, 180.0));

    // Add Health Data for the users
    QVector<HealthData> healthData1;
    healthData1.append(HealthData(80.0, 70.0, 90.0, 60.0, 85.0));

        QVector<HealthData> healthData2;
        healthData2.append(HealthData(75.0, 65.0, 85.0, 60.0, 80.0));

        users[0].setHistoricalHealthData(healthData1);
        users[1].setHistoricalHealthData(healthData2);

        // Access and modify users
        for (int i = 0; i < users.size(); ++i) {
            qDebug() << "User" << (i + 1) << ":"
                     << users[i].getName()
                     << "(" << users[i].getEmail() << ")";

            // Display historical health data for each user
            QVector<HealthData> healthData = users[i].getHistoricalHealthData();
            for (int j = 0; j < healthData.size(); ++j) {
                qDebug() << "Health Data " << (j + 1) << ":"
                         << healthData[j].displayData();
            }
        }

        // Save users to file
        saveUsersToFile(users, "users.txt");

        // Load users from file
        QVector<User> loadedUsers = loadUsersFromFile("users.txt");

        // Output loaded users
        for (int i = 0; i < loadedUsers.size(); ++i) {
            qDebug() << "Loaded User" << (i + 1) << ":"
                     << loadedUsers[i].getName()
                     << "(" << loadedUsers[i].getEmail() << ")";

            QVector<HealthData> loadedHealthData = loadedUsers[i].getHistoricalHealthData();
            for (int j = 0; j < loadedHealthData.size(); ++j) {
                qDebug() << "Loaded Health Data " << (j + 1) << ":"
                         << loadedHealthData[j].displayData();
            }
        }

        return 0;
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    */
}
