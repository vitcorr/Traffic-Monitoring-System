#include "road.h"

Road::Road(RoadType type, int lanes) : roadType(type), laneCount(lanes) {}

Road::RoadType Road::getType() const {
    return roadType;
}

int Road::getLaneCount() const {
    return laneCount;
}

void Road::setLaneCount(int lanes) {
    laneCount = lanes;
}

void Road::setupRoad() {
    // Override in subclasses
}
