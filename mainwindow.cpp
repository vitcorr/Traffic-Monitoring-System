#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Create a graphics scene
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, 800, 600); // Scene size

    // Timer to add cars randomly
    spawnTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, this, &MainWindow::spawnCar);
    spawnTimer->start(2000); // New car every 2 seconds
}

void MainWindow::spawnCar() {
    bool priority = QRandomGenerator::global()->bounded(2) == 1;
    int id = 1;
    if (priority) {
        id = QRandomGenerator::global()->bounded(1, 4); // Generates 1, 2, or 3
    } else {
        id = QRandomGenerator::global()->bounded(1, 16); // Generates 1 to 15
    }

    int direction = (QRandomGenerator::global()->bounded(2) == 0) ? 1 : -1; // Randomly left/right

    Vehicle *car = new Vehicle(priority, id, direction);
    scene->addItem(car);
}

MainWindow::~MainWindow() {
    delete ui;
}
