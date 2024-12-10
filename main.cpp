#include "MainWindow.h"
#include "user.h"
#include "control.h"
#include "rawHealthData.h"
#include "healthData.h"

#include <QApplication>
#include <QDebug>
#include <QRandomGenerator>

int main(int argc, char *argv[])
{
    QVector<User> users;
    //Control control;

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
    /*
    // Scan
    // TODO: connect to hardware

    // TODO: select user profile

    // Raw health data
    int measurements[24][10];
    int lowerBound = 5;
    int upperBounds[24] = { 191, 191, 171, 171, 151, 151, 171, 171, 201, 201, 201, 201, 161, 161, 131, 131, 151, 151, 151,151,  131, 131, 151, 151};
    QString skinContactPoints[24] = { "H1-L", "H1-R", "H2-L", "H2-R", "H3-L", "H3-R", "H4-L", "H4-R", "H5-L", "H5-R", "H6-L", "H6-R", 
                                      "F1-L", "F1-R", "F2-L", "F2-R", "F3-L", "F3-R", "F4-L", "F4-R", "F5-L", "F5-R", "F6-L", "F6-R"};
    // Measure 24 points of skin contact
    for (int i=0; i< 24; ++i) {
        // each point gets 10 numbers
        for (int j=0; j< 10; ++j) {
            measurements[i][j] = QRandomGenerator::global()->bounded(lowerBound, upperBounds[i]);
        }
    }
    RawHealthData rawHealthData(measurements);
    
    // print rawHealthData measurements
    for (int i=0; i< 24; ++i) {
        QDebug debug = qDebug();
        debug << skinContactPoints[i] << ":"; 
        for (int j=0; j< 10; ++j) {
            debug << measurements[i][j];
        }
    }

    // Data processing
    HealthData* newHealthData = control.processData(rawHealthData);
    qDebug() << "Display processed Data:" << newHealthData->displayData();

    // TODO: save data to current user
    // control.saveHealthData(newHealthData);
    
    delete newHealthData;

    // TODO: Test scan methods
    // RawHealthData* newRawData = control.startNewScan();
    // control.receiveNewScan(*newRawData)

    // TODO: hardware shutdown

    return 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
