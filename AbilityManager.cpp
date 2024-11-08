#include "AbilityManager.h"


AbilityManager::AbilityManager() {
    std::vector<Ability> initial_abilities{ Ability::DoubleDamage, Ability::Scanner, Ability::Shelling };
    for (Ability code : initial_abilities)
        abilities.push(code);
}

void AbilityManager::createAbility() {
    int randomCode = rand() % 3;
    Ability code;
    switch (randomCode)
    {
    case 0:
        code = Ability::DoubleDamage;
        break;
    case 1:
        code = Ability::Scanner;
        break;
    case 2:
        code = Ability::Shelling;
        break;
    }
    abilities.push(code);
}

void AbilityManager::useAbility(IArgs& args) {
    Factory& visitor = *(new Factory);
    args.acceptVisitor(visitor);
    IAbility& ability = visitor.getAbility();
    ability.useAbility();
    abilities.pop();
    delete& visitor;
    delete& ability;
}

Ability AbilityManager::viewAbility() const {
    if (abilities.size() == 0) {
        throw std::length_error("There is no available ability!\n");
    }
    return abilities.front();
}