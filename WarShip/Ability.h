#pragma once

#include <iostream>
#include <queue>
#include <random>
#include <vector>

#include "enums.h"
#include "Args.h"


class IAbility {
public:
    virtual void useAbility() = 0;
    virtual ~IAbility() = default;
};


class DoubleDamage : public IAbility {
private:
    Battlefield* field;
public:
    DoubleDamage(DoubleDamageArgs& args);
    void useAbility() override;
};

class Scanner : public IAbility {
private:
    std::pair<int, int> coords;
    Battlefield* field;
public:
    Scanner(ScannerArgs& args);
    void useAbility();
};

class Shelling : public IAbility {
private:
    ShipManager* manager;
public:
    Shelling(ShellingArgs& args);
    void useAbility() override;
};