#pragma once

#include <vector>
#include <string>
#include "enums.h"


class Ship
{
public:
    class Segment {
    private:
        SegmentStatus status = SegmentStatus::HEALTHY;
    public:
        Segment() = default;
        Segment(int state);

        SegmentStatus getStatus() const;

        void takeDamage();

        void repair();

        std::string getSegmentMap();

    };
    Ship() = default;
    Ship(std::vector<int> map_segments);
    explicit Ship(int length);

    int size();

    bool isDestroyed();

    Segment* getSegment(int index);

    void repair();

    std::string getShipMap();
private:
    int length;
    std::vector<Segment> segments;
};
