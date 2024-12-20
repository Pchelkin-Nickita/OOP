#pragma once

#include "ShipManager.h"

struct ScannerArgs;
struct DoubleDamageArgs;
struct ShellingArgs;

class Visitor {
public:
    virtual void visit(DoubleDamageArgs& args) = 0;
    virtual void visit(ScannerArgs& args) = 0;
    virtual void visit(ShellingArgs& args) = 0;
};

class IArgs {
public:
    virtual void acceptVisitor(Visitor& visit) = 0;
    virtual ~IArgs() = default;
};

struct ScannerArgs : public IArgs {
    ScannerArgs(std::pair<int, int> coords, Battlefield* field) : coords(coords), field(field) {}
    void acceptVisitor(Visitor& visitor) override { visitor.visit(*this); }
    std::pair<int, int> coords;
    Battlefield* field;
};

struct DoubleDamageArgs : public IArgs {
    DoubleDamageArgs(Battlefield* field) : field(field) {}
    void acceptVisitor(Visitor& visitor) override { visitor.visit(*this); }
    Battlefield* field;
};

struct ShellingArgs : public IArgs {
    ShellingArgs(ShipManager* manager) : manager(manager) {}
    void acceptVisitor(Visitor& visitor) override { visitor.visit(*this); }
    ShipManager* manager;
};