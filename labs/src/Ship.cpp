#include "../Ship.h"


Ship::Segment::Segment(int state) {
    switch (state)
    {
    case 2:
        status = HEALTHY;
        break;
    case 1:
        status = DAMAGED;
        break;
    case 0:
        status = DESTROYED;
        break;
    }
}

SegmentStatus Ship::Segment::getStatus() const {
    return status;
}

void Ship::Segment::takeDamage() {
    if (status == SegmentStatus::HEALTHY)
        status = SegmentStatus::DAMAGED;
    else if (status == SegmentStatus::DAMAGED)
        status = SegmentStatus::DESTROYED;
}

void Ship::Segment::repair() {
    status = HEALTHY;
}

std::string Ship::Segment::getSegmentMap() {
    int map_info;
    switch (status)
    {
    case HEALTHY:
        map_info = 2;
        break;
    case DAMAGED:
        map_info = 1;
        break;
    case DESTROYED:
        map_info = 0;
        break;
    }
    return std::to_string(map_info) + "\n";
}

Ship::Ship(int length) :length(length) {
    segments.resize(length);
    for (int i = 0; i < length; i++) {
        segments.emplace_back(Segment());
    }
}

Ship::Ship(std::vector<int> map_segments) {
    length = map_segments.size();
    for (int i = 0; i < length; i++) {
        segments.push_back(Segment(map_segments[i]));
    }
}

int Ship::size() {
    return length;
}

bool Ship::isDestroyed() {
    for (int i = 0; i < length; i++)
        if (segments[i].getStatus() != SegmentStatus::DESTROYED)
            return false;
    return true;
}

Ship::Segment* Ship::getSegment(int index) {
    return &segments[index];
}

std::string Ship::getShipMap() {
    std::string map = "";
    for (int i = 0; i < length; i++)
        map += segments[i].getSegmentMap();
    return map;
}

void Ship::repair(){
    for (auto& segment : segments) {
        segment.repair();
    }
}
