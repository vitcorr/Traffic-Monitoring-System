#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsItem>

class Road : public QGraphicsItem {
public:
    enum RoadType { Highway, Roundabout, FourWay , ThreeWay};

    Road(RoadType type, int lanes = 1);

    RoadType getType() const;
    int getLaneCount() const;
    void setLaneCount(int lanes);

    virtual void setupRoad();  // Override in subclasses

protected:
    RoadType roadType;
    int laneCount;
};

#endif
