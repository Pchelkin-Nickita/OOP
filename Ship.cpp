#include "Ship.h"


SegmentStatus Ship::Segment::getStatus() const {
    return status;
}

void Ship::Segment::takeDamage() {
    if (status == SegmentStatus::HEALTHY)
        status = SegmentStatus::DAMAGED;
    else if (status == SegmentStatus::DAMAGED)
        status = SegmentStatus::DESTROYED;
}

Ship::Ship(int length) :length(length) {
    segments.resize(length);
    for (int i = 0; i < length; i++) {
        segments.emplace_back(Segment());
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
