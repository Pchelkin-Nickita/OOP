#pragma once

enum Orientation {
    VERTICAL = 0,
    HORIZONTAL = 1
};

enum SegmentStatus {
    HEALTHY,
    DAMAGED,
    DESTROYED
};

enum CellStatus {
    EMPTY,
    SHIP,
    UNSIGNED
};

enum Ability {
    DoubleDamage = 0,
    Scanner = 1,
    Shelling = 2
};
