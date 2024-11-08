#pragma once

enum Orientation {
    VERTICAL,
    HORIZOTNTAL
};

enum SegmentStatus {
    HEALTHY,
    DAMAGED,
    DESTROYED
};

enum CellStatus {
    UNNKOWN,
    EMPTY,
    SHIP,
    UNSIGNED
};

enum Ability {
    DoubleDamage = 0,
    Scanner = 1,
    Shelling = 2
};
