#include <iostream>
#include "../headers/AbilityManager.h"


int main() {
    try {
        srand(time(0));
        int m, n;
        std::cin >> m >> n;
        Battlefield field1(m, n);
        field1.print();
        int a[4];
        for (int i = 0; i < 4; i++)
            std::cin >> a[i];
        ShipManager manager(a);
        while (!manager.end_of_setting()) {
            std::cout << "=========\n";
            int length;
            char o;
            std::cin >> length >> m >> n >> o;
            Orientation orient;
            if (o == 'h')
                orient = Orientation::HORIZOTNTAL;
            else
                orient = Orientation::VERTICAL;
            manager.set_ship(field1, length, m, n, orient);
            manager.setting_info();
            field1.print();
        }
        AbilityManager ab_manager;
        IArgs* args;
        std::pair<int, int> coords{ 0, 0 };
        while (!manager.game_over()) {
            std::cout << "=========\n";
            std::cin >> m;
            if (m == 1) {
                std::cout << "Available ability is " << ab_manager.viewAbility() << "\n";
                switch (ab_manager.viewAbility())
                {
                case 0:
                    args = new DoubleDamageArgs(&field1);
                    ab_manager.useAbility(*args);
                    delete args;
                    break;
                case 1:
                    args = new ScannerArgs(coords, &field1);
                    ab_manager.useAbility(*args);
                    delete args;
                    break;
                case 2:
                    args = new ShellingArgs(&manager);
                    ab_manager.useAbility(*args);
                    delete args;
                    break;
                }
            }
            std::cin >> m >> n;
            field1.attack(m, n);
            field1.print();
            if (manager.updateInfo())
                ab_manager.createAbility();
        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << "\n";
    }
    return 0;
}
