#pragma once

#include <vector>
#include "enums.h"


class Ship
{
public:
    class Segment {
    private:
        SegmentStatus status = SegmentStatus::HEALTHY;
    public:
        Segment() = default;

        SegmentStatus getStatus() const;

        void takeDamage();

    };
    Ship() = default;
    explicit Ship(int length);

    int size();

    bool isDestroyed();

    Segment* getSegment(int index);
private:
    int length;
    std::vector<Segment> segments;
};
