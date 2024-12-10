#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "QStackedWidget"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Get the stacked widget and the button from the UI
    QStackedWidget* stackedWidget = ui->stackedWidget;

    // Connect the button's clicked signal to the slot
    connect(ui->createPushButton, &QPushButton::clicked, this, &MainWindow::on_switchButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_switchButton_clicked()
{
    QStackedWidget* stackedWidget = ui->stackedWidget;
    // Switch to the next page in the stacked widget
    int currentIndex = stackedWidget->currentIndex();
    int nextIndex = (currentIndex + 1) % stackedWidget->count();  // Loop back to the first page after the last one
    stackedWidget->setCurrentIndex(nextIndex);  // Change the current page
}

