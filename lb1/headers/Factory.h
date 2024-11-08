#pragma once

#include "Ability.h"

class Factory : public Visitor {
private:
    IAbility* ability = nullptr;
public:
    IAbility& getAbility();
    void visit(DoubleDamageArgs& args) override;
    void visit(ScannerArgs& args) override;
    void visit(ShellingArgs& args) override;
};