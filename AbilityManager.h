#pragma once
#include "Factory.h"
#include <algorithm>

class AbilityManager {
private:
    std::queue<Ability> abilities;
public:
    AbilityManager();

    void createAbility();

    void useAbility(IArgs& args);

    Ability viewAbility() const;

};