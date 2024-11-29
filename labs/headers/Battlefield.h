#pragma once
#include "Ship.h"

#define HEALTHY_SEGMENT_REGISTER 'O'
#define DAMAGED_SEGMENT_REGISTER 'X'
#define DESTROYED_SEGMENT_REGISTER '.'
#define EMPTY_REGISTER ' '
#define INVISIBLE_REGISTER '*'
#define UNSIGNED_REGISTER '/'


class Battlefield {
    class Cell {
    private:
        CellStatus state = CellStatus::EMPTY;
        Ship::Segment* ptr_ship = nullptr;
        bool was_attacked = false;
    public:
        Cell() = default;
        Cell(bool was_attacked);

        CellStatus getState() const;

        Ship::Segment* getSegment() const;

        bool isChecked() const;

        void setSegment(Ship::Segment* segment);

        bool attack(bool& is_double_damage_active);

        std::string getCellMap();
    };
private:
    std::vector<std::vector<Cell>> field;
    bool is_double_damage_active = false;
    bool is_visible = false;
public:
    int length;
    int width;
    Battlefield() = default;
    Battlefield(const int length, const int width, bool is_visible);
    Battlefield(const int length, const int width, std::vector<std::vector<bool>> field, bool is_visible);
    Battlefield(const Battlefield& copy);
    Battlefield(Battlefield&& moved);
    Battlefield& operator = (const Battlefield& copy);
    Battlefield& operator = (Battlefield&& moved);

    CellStatus getCellState(int x, int y) const;
    
    bool isValidPosition(int x, int y, int length, Orientation orient) const;

    bool placeShip(Ship& ship, int x, int y, Orientation orient);

    void setDoubleDamage();

    bool attack(int x, int y);

    void clear();

    void print() const;

    std::string getFieldMap();
};