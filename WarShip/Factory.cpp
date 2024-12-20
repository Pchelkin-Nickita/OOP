#include "Factory.h"


IAbility& Factory::getAbility() {
    return *ability;
}
void Factory::visit(DoubleDamageArgs& args) {
    ability = new class DoubleDamage(args);
}
void Factory::visit(ScannerArgs& args) {
    ability = new class Scanner(args);
}
void Factory::visit(ShellingArgs& args) {
    ability = new class Shelling(args);
}
