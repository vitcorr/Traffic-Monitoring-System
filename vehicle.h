#ifndef VEHICLE_H
#define VEHICLE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Vehicle : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Vehicle(bool priority, int id, int direction); // Constructor with car ID and direction

public slots:
    void move();

private:
    bool priority;
    int id;
    int direction; // 1 = right, -1 = left
    int speed;
    QString getVehicleImage(bool priority); // Helper function to get image path
};

#endif // VEHICLE_H

