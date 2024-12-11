#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "QStackedWidget"
#include "QIntValidator"
#include "QDoubleValidator"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->control = NULL;
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    // Get the stacked widget and the button from the UI
    ui->createAge->setValidator(new QIntValidator(0, 150, this));
    ui->createHeight->setValidator(new QDoubleValidator(0, 999, 2, this));
    ui->createWeight->setValidator(new QDoubleValidator(0, 999, 2, this));

    // Connect the button's clicked signal to the slot
    connect(ui->createPushButton, &QPushButton::clicked, this, &MainWindow::on_create_profile_clicked);
    connect(ui->viewProfilesPushButton, &QPushButton::clicked, this, &MainWindow::on_profiles_clicked);
    connect(ui->saveUserPushButton, &QPushButton::clicked, this, &MainWindow::on_finish_profile_clicked);
    connect(ui->updatePushButton, &QPushButton::clicked, this, &MainWindow::on_update_profile_clicked);
    connect(ui->updateUserPushButton, &QPushButton::clicked, this, &MainWindow::on_finish_update_profile_clicked);
    connect(ui->deletePushButton, &QPushButton::clicked, this, &MainWindow::on_delete_profile_clicked);
    connect(ui->btnMeasureNow1, &QPushButton::clicked, this, &MainWindow::on_btnMeasureNow_clicked);
    connect(ui->btnMeasureNow2, &QPushButton::clicked, this, &MainWindow::on_btnMeasureNow_clicked);
    connect(ui->btnMenu, &QPushButton::clicked, this, &MainWindow::on_btnMenu_clicked);
    connect(ui->btnNextStep, &QPushButton::clicked, this, &MainWindow::on_btnNextStep_clicked);
    connect(ui->btnClose, &QPushButton::clicked, this, &MainWindow::on_btnClose_clicked);
    connect(ui->btnHome, &QPushButton::clicked, this, &MainWindow::on_btnHome_clicked);
    connect(ui->btnLogout, &QPushButton::clicked, this, &MainWindow::on_btnLogout_clicked);
    connect(ui->btnCreateProfile, &QPushButton::clicked, this, &MainWindow::on_btnCreateProfile_clicked);
    connect(ui->btnEnter, &QPushButton::clicked, this, &MainWindow::on_btnEnter_clicked);
    connect(ui->btnMetering, &QPushButton::clicked, this, &MainWindow::on_btnMetering_clicked);

    this->control = new Control();

    populate_list(ui->listProfiles, this->control->allUsers);
}

// Function to populate a QListWidget from a QVector<User>
void MainWindow::populate_list(QListWidget* listWidget, QVector<User>& users) {
    listWidget->clear(); // Clear existing items in the list

    // Iterate through the QVector and add items to the QListWidget
    for (int i = 0; i < users.size(); ++i) {
        QListWidgetItem* item = new QListWidgetItem(users[i].getName(), listWidget);

        // Store the index of the user in the item's data for retrieval
        item->setData(Qt::UserRole, i);
    }

    // Connect the itemClicked signal to a lambda to handle clicks
    QObject::connect(listWidget, &QListWidget::itemClicked, this, [this, &users](QListWidgetItem* item) {
        int userIndex = item->data(Qt::UserRole).toInt();
        User& clickedUser = users[userIndex];

        // Perform actions with the clicked user, e.g., print the name
        qDebug() << "Clicked User:" << clickedUser.getName();
        this->control->setCurrentUser(&clickedUser);

        QStackedWidget* stackedWidget = ui->stackedWidget;
        stackedWidget->setCurrentIndex(2);
        // If needed, pass the reference elsewhere
        // Example: someFunction(clickedUser);
    });
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

void MainWindow::on_profiles_clicked() {
    QStackedWidget* stackedWidget = ui->stackedWidget;
    stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_create_profile_clicked() {
    QStackedWidget* stackedWidget = ui->stackedWidget;
    stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_finish_profile_clicked() {
    QStackedWidget* stackedWidget = ui->stackedWidget;

    QString name = ui->createFirst->text();
    QString gender = ui->createGender->text();
    QString email = ui->createEmail->text();
    QString age = ui->createAge->text();
    QString weight = ui->createWeight->text();
    QString height = ui->createHeight->text();

    this->control->addUser(User(email, name, gender, age, weight, height));

    ui->createFirst->setText("");
    ui->createGender->setText("");
    ui->createEmail->setText("");
    ui->createAge->setText("");
    ui->createWeight->setText("");
    ui->createHeight->setText("");

    populate_list(ui->listProfiles, this->control->allUsers);

    stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_update_profile_clicked() {
    if (control->currentUser == NULL) {
        qDebug() << "No current user";
        return;
    }

    QStackedWidget* stackedWidget = ui->stackedWidget;

    ui->updateFirst->setText(control->currentUser->getName());
    ui->updateGender->setText(control->currentUser->getGender());
    ui->updateEmail->setText(control->currentUser->getEmail());
    ui->updateAge->setText(control->currentUser->getAge());
    ui->updateWeight->setText(control->currentUser->getWeight());
    ui->updateHeight->setText(control->currentUser->getHeight());

    QString name = ui->updateFirst->text();
    QString gender = ui->updateGender->text();
    QString email = ui->updateEmail->text();
    QString age = ui->updateAge->text();
    QString weight = ui->updateWeight->text();
    QString height = ui->updateHeight->text();

    this->control->currentUser->setName(name);
    this->control->currentUser->setGender(gender);
    this->control->currentUser->setEmail(email);
    this->control->currentUser->setAge(age);
    this->control->currentUser->setWeight(weight);
    this->control->currentUser->setHeight(height);

    stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_finish_update_profile_clicked() {
    if (control->currentUser == NULL) {
        return;
    }

    QStackedWidget* stackedWidget = ui->stackedWidget;

    QString name = ui->updateFirst->text();
    QString gender = ui->updateGender->text();
    QString email = ui->updateEmail->text();
    QString age = ui->updateAge->text();
    QString weight = ui->updateWeight->text();
    QString height = ui->updateHeight->text();

    this->control->currentUser->setName(name);
    this->control->currentUser->setGender(gender);
    this->control->currentUser->setEmail(email);
    this->control->currentUser->setAge(age);
    this->control->currentUser->setWeight(weight);
    this->control->currentUser->setHeight(height);

    ui->updateFirst->setText("");
    ui->updateGender->setText("");
    ui->updateEmail->setText("");
    ui->updateAge->setText("");
    ui->updateWeight->setText("");
    ui->updateHeight->setText("");

    control->saveUsers();

    populate_list(ui->listProfiles, this->control->allUsers);

    stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_delete_profile_clicked() {
    control->deleteCurrentUser();
    populate_list(ui->listProfiles, this->control->allUsers);
}

void MainWindow::on_btnMeasureNow_clicked() {
    QStackedWidget *stackedWidget = ui->stackedWidget;
    stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_btnMenu_clicked() {
    QStackedWidget *stackedWidget = ui->stackedWidget;
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_btnNextStep_clicked() {
    QStackedWidget *stackedWidget = ui->stackedWidget;
    stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_btnClose_clicked() {
    QStackedWidget *stackedWidget = ui->stackedWidget;
    stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_btnHome_clicked() {
    QStackedWidget *stackedWidget = ui->stackedWidget;
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btnLogout_clicked() {
    QStackedWidget *stackedWidget = ui->stackedWidget;
    stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_btnCreateProfile_clicked() {
    QStackedWidget *stackedWidget = ui->stackedWidget;
    stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_btnEnter_clicked() {
    QStackedWidget *stackedWidget = ui->stackedWidget;
    stackedWidget->setCurrentIndex(5);
}

int point = 0;
int measurements[24][10];

void MainWindow::on_btnMetering_clicked() {
    QPushButton *btnMetering = ui->btnMetering;
    btnMetering->setText("PRESS");

    QString imagePath = QString(":/images/point%1.png").arg(point + 1);  // Adjust the point number for images
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        ui->imageBodyPoint->setPixmap(pixmap);
        ui->imageBodyPoint->setScaledContents(true);
    } else {
        qDebug() << "Failed to load image:" << imagePath;
    }

    ui->labelBodyPoint->setText(QString("Point %1").arg(point + 1));

    if (point == 0) {
        // Simulate the measurements for 24 skin contact points, each with 10 measurements
        int lowerBound = 5;
        int upperBounds[24] = {191, 191, 171, 171, 151, 151, 171, 171, 201, 201, 201, 201, 161, 161, 131, 131, 151, 151, 151, 151, 131, 131, 151, 151};

        QString skinContactPoints[24] = { "H1-L", "H1-R", "H2-L", "H2-R", "H3-L", "H3-R", "H4-L", "H4-R", "H5-L", "H5-R", "H6-L", "H6-R",
                                          "F1-L", "F1-R", "F2-L", "F2-R", "F3-L", "F3-R", "F4-L", "F4-R", "F5-L", "F5-R", "F6-L", "F6-R"};

        // Populate the measurements array with random values
        for (int i = 0; i < 24; ++i) {
            for (int j = 0; j < 10; ++j) {
                measurements[i][j] = QRandomGenerator::global()->bounded(lowerBound, upperBounds[i]);
            }
        }

        RawHealthData rawHealthData(measurements);  // Assuming RawHealthData is a class that takes 2D data

        // Print the data to debug
        for (int i = 0; i < 24; ++i) {
            QDebug debug = qDebug();
            debug << skinContactPoints[i] << ":";
            for (int j = 0; j < 10; ++j) {
                debug << measurements[i][j];
            }
        }
    }

    // Update the graph with the data for the current point
    updateGraphData(point);

    // Move to the next point
    ++point;
    if (point >= 24) {
        point = 0;
    }
}

void MainWindow::updateGraphData(int point) {
    // Get the measurements for the current point
    QVector<double> xData, yData;

    for (int i = 0; i < 10; ++i) {
        xData.append(i);  // X axis values (0, 1, 2, ..., 9)
        yData.append(measurements[point][i]);  // Y axis values (measurement data)
    }

    // Clear any previous data in the graph
    ui->graphMetering->clearGraphs();

    // Create a new bar chart
    QCPBars *bars = new QCPBars(ui->graphMetering->xAxis, ui->graphMetering->yAxis);
    bars->setData(xData, yData);

    // Set graph styling (optional)
    bars->setPen(QPen(Qt::blue));  // Set border color of bars
    bars->setBrush(QBrush(Qt::blue));  // Set fill color of bars

    // Redraw the graph
    ui->graphMetering->replot();
}
