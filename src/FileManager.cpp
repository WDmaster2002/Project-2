#include "FileManager.h"
#include <fstream>
#include <sstream>

void FileManager::save(const std::vector<Transaction>& transactions,
    const std::string& filename) {
    std::ofstream out(filename);
    for (const auto& t : transactions) {
        out << t.id << ","
            << t.type << ","
            << t.category << ","
            << t.amount << ","
            << t.date << "\n";
    }
}

void FileManager::load(std::vector<Transaction>& transactions,
    const std::string& filename) {
    std::ifstream in(filename);
    if (!in.good()) return;

    transactions.clear();
    std::string line;

    while (std::getline(in, line)) {
        std::stringstream ss(line);
        Transaction t;
        std::string amountStr, idStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, t.type, ',');
        std::getline(ss, t.category, ',');
        std::getline(ss, amountStr, ',');
        std::getline(ss, t.date, ',');

        t.id = std::stoi(idStr);
        t.amount = std::stod(amountStr);

        transactions.push_back(t);
    }
}
