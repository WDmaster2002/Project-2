#include <iostream>
#include "TransactionManager.h"
#include "FileManager.h"
#include "Menu.h"

int main() {
    TransactionManager manager;
    const std::string filename = "data/transactions.txt";

    FileManager::load(manager.getAll(), filename);

    bool running = true;

    while (running) {
        Menu::printMainMenu();

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string type, category, date;
            double amount;

            Menu::getTransactionInput(type, category, amount, date);
            manager.addTransaction(type, category, amount, date);
            break;
        }

        case 2: {
            int id;
            std::cout << "Enter ID to edit: ";
            std::cin >> id;

            std::string type, category, date;
            double amount;
            Menu::getTransactionInput(type, category, amount, date);

            if (!manager.editTransaction(id, type, category, amount, date))
                std::cout << "Invalid ID.\n";
            break;
        }

        case 3: {
            int id;
            std::cout << "Enter ID to delete: ";
            std::cin >> id;

            if (!manager.deleteTransaction(id))
                std::cout << "Invalid ID.\n";
            break;
        }

        case 4: {
            std::string month;
            std::cout << "Enter month (YYYY-MM): ";
            std::cin >> month;

            manager.showMonthlySummary(month);
            break;
        }

        case 5:
            FileManager::save(manager.getAll(), filename);
            std::cout << "Saved.\n";
            break;

        case 6:
            FileManager::load(manager.getAll(), filename);
            std::cout << "Loaded.\n";
            break;

        case 0:
            running = false;
            break;

        default:
            std::cout << "Invalid choice.\n";
        }
    }

    FileManager::save(manager.getAll(), filename);

    return 0;
}
