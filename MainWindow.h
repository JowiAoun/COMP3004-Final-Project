#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <control.h>

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


    void populate_list(QListWidget* listWidget, QVector<User>& users);

private:
    Ui::MainWindow *ui;
    Control* control;

};
#endif // MAINWINDOW_H
