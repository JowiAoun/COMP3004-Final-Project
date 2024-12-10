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

    // Get the stacked widget and the button from the UI
    QStackedWidget* stackedWidget = ui->stackedWidget;
    ui->createAge->setValidator(new QIntValidator(0, 150, this));
    ui->createHeight->setValidator(new QDoubleValidator(0, 999, 2, this));
    ui->createWeight->setValidator(new QDoubleValidator(0, 999, 2, this));

    // Connect the button's clicked signal to the slot
    connect(ui->createPushButton, &QPushButton::clicked, this, &MainWindow::on_create_profile_clicked);
    connect(ui->viewProfilesPushButton, &QPushButton::clicked, this, &MainWindow::on_profiles_clicked);
    connect(ui->saveUserPushButton, &QPushButton::clicked, this, &MainWindow::on_finish_profile_clicked);
    connect(ui->updatePushButton, &QPushButton::clicked, this, &MainWindow::on_update_profile_clicked);
    connect(ui->updateUserPushButton, &QPushButton::clicked, this, &MainWindow::on_finish_update_profile_clicked);

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

    control->saveUsers();

    populate_list(ui->listProfiles, this->control->allUsers);

    stackedWidget->setCurrentIndex(3);
}

