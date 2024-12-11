#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTimer>
#include <control.h>
#include <hardware.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void on_switchButton_clicked();
    void on_profiles_clicked();
    void on_create_profile_clicked();
    void on_finish_profile_clicked();
    void on_update_profile_clicked();
    void on_finish_update_profile_clicked();
    void on_delete_profile_clicked();
    void on_btnMeasureNow_clicked();
    void on_btnMenu_clicked();

    void show_battery();

    void on_btnNextStep_clicked();
    void on_btnClose_clicked();
    void on_btnHome_clicked();
    void on_btnLogout_clicked();
    void on_btnCreateProfile_clicked();
    void on_btnEnter_clicked();
    void on_btnMetering_clicked();
    void updateGraphData(int point);

    void populate_list(QListWidget* listWidget, QVector<User>& users);

private:
    Ui::MainWindow *ui;
    Control* control;
    Hardware* hardware;
    QTimer* timer;

};
#endif // MAINWINDOW_H
