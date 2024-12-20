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
    try {
        abilities.pop();
        Factory& visitor = *(new Factory);
        args.acceptVisitor(visitor);
        IAbility& ability = visitor.getAbility();
        ability.useAbility();

        delete& visitor;
        delete& ability;
    }
    catch (...) {
        std::cout << "There is no available ability!\n";
    }
    
}

Ability AbilityManager::viewAbility() const {
    try {
        return abilities.front();
    }
    catch(...){
        std::cout << "There is no available ability!\n";
    }
    
}