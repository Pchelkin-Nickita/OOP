#pragma once
#include "Ship.h"

#define HEALTHY_SEGMENT_REGISTER 'O'
#define DAMAGED_SEGMENT_REGISTER 'X'
#define DESTROYED_SEGMENT_REGISTER '.'
#define EMPTY_REGISTER '*'
#define MISS_REGISTER ' '
#define UNSIGNED_REGISTER '/'


class Battlefield {
    class Cell {
    private:
        CellStatus state = CellStatus::EMPTY;
        Ship::Segment* ptr_ship = nullptr;
        bool was_attacked = false;
    public:
        Cell() = default;

        CellStatus getState() const;

        Ship::Segment* getSegment() const;

        bool isChecked() const;

        void setSegment(Ship::Segment* segment);

        void attack(bool& is_double_damage_active);
    };
private:
    std::vector<std::vector<Cell>> field;
    int length;
    int width;
    bool is_double_damage_active = false;
public:
    Battlefield() = default;
    Battlefield(const int length, const int width);
    Battlefield(const Battlefield& copy);
    Battlefield(Battlefield&& moved);
    Battlefield& operator = (const Battlefield& copy);
    Battlefield& operator = (Battlefield&& moved);

    CellStatus getState(int x, int y) const;
    
    bool getVicinity(int x, int y) const;

    bool setShip(Ship& ship, int x, int y, Orientation orient);

    void setDoubleDamage();

    void attack(int x, int y);

    void print() const;
};
