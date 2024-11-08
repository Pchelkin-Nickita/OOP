#include "../headers/Battlefield.h"
#include <iostream>


CellStatus Battlefield::Cell::getState() const{
    return state;
}
void Battlefield::Cell::attack(bool& is_double_damage_active) {
    if (was_attacked) {
        std::cout << "You have already attacked this cell!\n";
        return;
    }
    switch (state)
    {
    case CellStatus::EMPTY:
        was_attacked = true;
        break;
    case CellStatus::SHIP:
        if (ptr_ship->getStatus() == SegmentStatus::DESTROYED)
            std::cout << "You have already destroyed segment in this cell\n";
        else {
            ptr_ship->takeDamage();
            if (is_double_damage_active) {
                ptr_ship->takeDamage();
                is_double_damage_active = false;
            }
        }
    }
}
void Battlefield::Cell::setSegment(Ship::Segment* segment) {
    ptr_ship = segment;
    state = CellStatus::SHIP;
}
Ship::Segment* Battlefield::Cell::getSegment() const{
    return ptr_ship;
}
bool Battlefield::Cell::isChecked() const{
    return was_attacked;
}

Battlefield::Battlefield(const int length, const int width):length(length), width(width) {
    field.resize(length);
    for (int x = 0; x < length; x++) {
        field[x].resize(width);
        for (int y = 0; y < width; y++)
            field[x][y] = Cell();
    }
}
Battlefield::Battlefield(const Battlefield& copy) :Battlefield(copy.length, copy.width) {}
Battlefield::Battlefield(Battlefield&& moved) {
    length = std::move(moved.length);
    width = std::move(moved.width);
    field = std::move(moved.field);
}
Battlefield& Battlefield::operator = (const Battlefield& copy) {
    if (&copy != this) {
        length = copy.length;
        width = copy.width;
        field.resize(length);
        for (int y = 0; y < length; y++) {
            field.resize(width);
            for (int x = 0; x < width; x++)
                field[y][x] = copy.field[y][x];
        }
    }
    return *this;
}
Battlefield& Battlefield::operator = (Battlefield&& moved) {
    if (&moved != this) {
        length = std::move(moved.length);
        width = std::move(moved.width);
        field = std::move(moved.field);
    }
    return *this;
}

CellStatus Battlefield::getState(int x, int y) const {
    if (x >= 0 and y >= 0 and x < length and y < width)
        return field[x][y].getState();
    else {
        return CellStatus::UNSIGNED;
    }
}

bool Battlefield::getVicinity(int x, int y) const {
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
            if (getState(x + i, y + j) == CellStatus::SHIP)
                return true;
    return false;
}

void Battlefield::setDoubleDamage() {
    is_double_damage_active = true;
}

bool Battlefield::setShip(Ship& ship, int x, int y, Orientation orient) {
    int horizontal_offset, vertical_offset;
    if (orient == Orientation::VERTICAL) {
        horizontal_offset = 0;
        vertical_offset = ship.size() - 1;
    }
    else {
        horizontal_offset = ship.size() - 1;
        vertical_offset = 0;
    }
    if (scanner(x, y) or scanner(x + vertical_offset, y + horizontal_offset) or getState(x, y) == UNSIGNED_REGISTER or getState(x + vertical_offset, y + horizontal_offset) == UNSIGNED_REGISTER) {
        return false;
    }
    for (int i = x; i <= x + vertical_offset; i++)
        for (int j = y; j <= y + horizontal_offset; j++)
            field[i][j].setSegment(ship.getSegment(i + j - (x + y)));
    return true;
}

void Battlefield::attack(int x, int y) {
    if (getState(x, y) != UNSIGNED_REGISTER)
        field[x][y].attack(is_double_damage_active);
    else
        throw std::length_error("Can't attack this cell!\n");
}

void Battlefield::print() const {
    std::cout << "  ";
    for (int i = 0; i < width; i++)
        std::cout << i << ' ';
    std::cout << '\n';
    for (int y = 0; y < length; y++) {
        std::cout << y << ' ';
        for (int x = 0; x < width; x++) {
            char cell_info;
            if (field[y][x].getState() == CellStatus::SHIP) {
                SegmentStatus tmp = field[y][x].getSegment()->getStatus();
                switch (field[y][x].getSegment()->getStatus()) {
                case SegmentStatus::HEALTHY:
                    cell_info = HEALTHY_SEGMENT_REGISTER;
                    break;
                case SegmentStatus::DAMAGED:
                    cell_info = DAMAGED_SEGMENT_REGISTER;
                    break;
                case SegmentStatus::DESTROYED:
                    cell_info = DESTROYED_SEGMENT_REGISTER;
                    break;
                }
            }
            else if (field[y][x].isChecked())
                cell_info = MISS_REGISTER;
            else
                cell_info = EMPTY_REGISTER;
            std::cout << cell_info << ' ';
        }
        std::cout << '\n';
    }
}
