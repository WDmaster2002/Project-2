#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>

namespace Menu {

    inline void printMainMenu() {
        std::cout << "\n===== Finance Tracker =====\n"
            << "1. Add Transaction\n"
            << "2. Edit Transaction\n"
            << "3. Delete Transaction\n"
            << "4. Monthly Summary\n"
            << "5. Save\n"
            << "6. Load\n"
            << "0. Exit\n"
            << "Choice: ";
    }

    inline void getTransactionInput(std::string& type,
        std::string& category,
        double& amount,
        std::string& date)
    {
        std::cout << "Type (income/expense): ";
        std::cin >> type;

        std::cout << "Category: ";
        std::cin >> category;

        std::cout << "Amount: ";
        std::cin >> amount;

        std::cout << "Date (YYYY-MM-DD): ";
        std::cin >> date;
    }

} // namespace Menu

#endif // !MENU_H
