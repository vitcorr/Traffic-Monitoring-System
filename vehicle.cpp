#include "vehicle.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>

Vehicle::Vehicle(bool priority, int id, int direction) {
    this->priority = priority;  // Corrected assignment
    this->id = id;
    this->direction = direction;

    // Assign speed based on ID
    if (!priority) {    // Random speed depending on cars
        if (id < 8) {
            speed = QRandomGenerator::global()->bounded(7, 9);
        } else {
            speed = QRandomGenerator::global()->bounded(8, 11);
        }
    } else {    // Priority vehicles are faster
        speed = QRandomGenerator::global()->bounded(10, 13);
    }

    // Set image based on ID
    QPixmap scaledPixmap = QPixmap(getVehicleImage()).scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaledPixmap);

    // Apply rotation based on direction
    QTransform transform;
    switch (direction) {
        case 0: transform.rotate(270); break; // Move up
        case 1: transform.rotate(90); break;  // Move down
        case 2: transform.rotate(180); break;   // Move left
        case 3: transform.rotate(0); break; // Move right
    }
    setPixmap(pixmap().transformed(transform));

    // Set initial position based on direction
    int randomY = QRandomGenerator::global()->bounded(100, 500);
    int randomX = QRandomGenerator::global()->bounded(100, 700);

    switch (direction) {
        case 0: setPos(randomX, 750); break;  // Starts at bottom (moves up)
        case 1: setPos(randomX, 0); break;    // Starts at top (moves down)
        case 2: setPos(750, randomY); break;  // Starts at right (moves left)
        case 3: setPos(0, randomY); break;    // Starts at left (moves right)
    }

    // Timer to move the Vehicle
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Vehicle::move);
    timer->start(50); // Move every 50ms
}

void Vehicle::move() {
    switch (direction) {
        case 0: setY(y() - speed); break; // Move up
        case 1: setY(y() + speed); break; // Move down
        case 2: setX(x() - speed); break; // Move left
        case 3: setX(x() + speed); break; // Move right
    }
}

// Helper function to get image path
QString Vehicle::getVehicleImage() const {
    if (priority) { // Use the class member `priority`
        return QString(":/vehicles/Images/vehicles/priority%1.png").arg(id);
    } else {
        return QString(":/vehicles/Images/vehicles/car%1.png").arg(id);
    }
}
