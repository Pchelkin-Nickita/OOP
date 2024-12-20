#include "Battlefield.h"
#include <iostream>


CellStatus Battlefield::Cell::getState() const{
    return state;
}

Battlefield::Cell::Cell(bool was_attacked) : was_attacked(was_attacked){}

bool Battlefield::Cell::attack(bool& is_double_damage_active) {
    was_attacked = true;
    if (state == CellStatus::SHIP){
        ptr_ship->takeDamage();
        if (is_double_damage_active) {
            ptr_ship->takeDamage();
            is_double_damage_active = false;
        }
        return true;
    }
    return false;
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

std::string Battlefield::Cell::getCellMap() {
    int map_state = was_attacked ? 1 : 0;
    return std::to_string(map_state) + '\n';
}

Battlefield::Battlefield(const int length, const int width, bool is_visible):length(length), width(width), is_visible(is_visible){
    field.resize(length);
    for (int x = 0; x < length; x++) {
        field[x].resize(width);
        for (int y = 0; y < width; y++)
            field[x][y] = Cell();
    }
}
Battlefield::Battlefield(const Battlefield& copy) :Battlefield(copy.length, copy.width, copy.is_visible) {}
Battlefield::Battlefield(Battlefield&& moved) {
    length = std::move(moved.length);
    width = std::move(moved.width);
    field = std::move(moved.field);
    is_visible = std::move(moved.is_visible);
}
Battlefield::Battlefield(const int length, const int width, std::vector<std::vector<bool>> field, bool is_visible) :length(length), width(width), is_visible(is_visible) {
    this->field.resize(length);
    for (int x = 0; x < length; x++) {
        this->field[x].resize(width);
        for (int y = 0; y < width; y++)
            this->field[x][y] = Cell(field[x][y]);
    }
}
Battlefield& Battlefield::operator = (const Battlefield& copy) {
    if (&copy != this) {
        length = copy.length;
        width = copy.width;
        is_visible = copy.is_visible;
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
        is_visible = std::move(moved.is_visible);
    }
    return *this;
}

CellStatus Battlefield::getCellState(int x, int y) const {
    if (x >= 0 and y >= 0 and x < length and y < width)
        return field[x][y].getState();
    else {
        return CellStatus::UNSIGNED;
    }
}

bool Battlefield::isValidPosition(int x, int y, int length, Orientation orient) const {
    int horizontal_offset, vertical_offset;
    if (orient == Orientation::VERTICAL) {
        horizontal_offset = 1;
        vertical_offset = length;
    }
    else {
        horizontal_offset = length;
        vertical_offset = 1;
    }
    for (int i = -1; i <= vertical_offset; i++)
        for (int j = -1; j <= horizontal_offset; j++)
            if (getCellState(x + i, y + j) == CellStatus::SHIP)
                return false;
    if (getCellState(x, y) == UNSIGNED or getCellState(x + vertical_offset - 1, y + horizontal_offset - 1) == UNSIGNED)
        return false;
    return true;
}

void Battlefield::setDoubleDamage() {
    is_double_damage_active = true;
}

bool Battlefield::placeShip(Ship& ship, int x, int y, Orientation orient) {
    int horizontal_offset, vertical_offset;
    if (orient == Orientation::VERTICAL) {
        horizontal_offset = 0;
        vertical_offset = ship.size() - 1;
    }
    else {
        horizontal_offset = ship.size() - 1;
        vertical_offset = 0;
    }
    if (!isValidPosition(x, y, ship.size(), orient)) {
        return false;
    }
    for (int i = x; i <= x + vertical_offset; i++)
        for (int j = y; j <= y + horizontal_offset; j++)
            field[i][j].setSegment(ship.getSegment(i + j - (x + y)));
    return true;
}

bool Battlefield::attack(int x, int y) {
    try {
        if (getCellState(x, y) != UNSIGNED_REGISTER)
            return field[x][y].attack(is_double_damage_active);
        else {
            throw std::length_error("Can't attack this cell!\n");
        }
    } catch(std::exception& e) {
        std::cout << e.what() << '\n';
        return true;
    }

}

void Battlefield::clear() {
    for (int x = 0; x < field.size(); x++) {
        for (int y = 0; y < field[x].size(); y++)
            field[x][y] = Cell();
    }
}

void Battlefield::print(InterfaceSymbols& registers) const {
    std::cout << "  ";
    for (int i = 0; i < width; i++)
        std::cout << i+1 << ' ';
    std::cout << '\n';
    for (int y = 0; y < length; y++) {
        std::cout << y+1 << ' ';
        for (int x = 0; x < width; x++) {
            char cell_info;
            if (!field[y][x].isChecked() and !is_visible)
                cell_info = registers.invisible;
            else if (field[y][x].getState() == CellStatus::SHIP) {
                SegmentStatus tmp = field[y][x].getSegment()->getStatus();
                switch (field[y][x].getSegment()->getStatus()) {
                case SegmentStatus::HEALTHY:
                    cell_info = registers.healthy;
                    break;
                case SegmentStatus::DAMAGED:
                    cell_info = registers.damaged;
                    break;
                case SegmentStatus::DESTROYED:
                    cell_info = registers.destroyed;
                    break;
                }
            }
            else
                cell_info = registers.empty;
            std::cout << cell_info << ' ';
        }
        std::cout << '\n';
    }
}

std::string Battlefield::getFieldMap() {
    std::string map = std::to_string(length) + "\n" + std::to_string(width) + "\n";
    map += is_visible ? "1" : "0";
    map += "\n";
    for (int i = 0; i < length; i++)
        for (int j = 0; j < width; j++)
            map += field[i][j].getCellMap();
    return map;
}
