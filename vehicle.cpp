#include "vehicle.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>

Vehicle::Vehicle(bool priority, int id, int direction) {
    this ->priority;
    this ->id = id;
    this ->direction = direction;

    // Assign speed based on ID
    if (!priority) {    //random speed depending on cars
        if (id < 8) {
            speed = QRandomGenerator::global()->bounded(7,9);
        } else {
            speed = QRandomGenerator::global()->bounded(8, 11);
        }
    } else {    //priority vehicles are faster
        speed = QRandomGenerator::global()->bounded(10, 13);
    }


    // Set image based on ID
    setPixmap(QPixmap(getVehicleImage(priority)).scaled(50, 30));

    // Random Y position
    int randomY = QRandomGenerator::global()->bounded(100, 500);
    setPos(direction == 1 ? 0 : 750, randomY); // Start at left or right

    // Timer to move the Vehicle
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Vehicle::move);
    timer->start(50); // Move every 50ms
}

void Vehicle::move() {
    setPos(x() + (speed * direction), y());

    // Remove Vehicle if it moves off-screen
    if (x() < -50 || x() > 850) {
        delete this;
    }
}

// Helper function to get image path
QString Vehicle::getVehicleImage(bool p) {
    if (p) {
        return QString(":/vehicles/Images/vehicles/priority%1.png").arg(id);
    } else {
        return QString(":/vehicles/Images/vehicles/car%1.png").arg(id);
    }
}
