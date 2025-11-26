#include <iostream>
#include "TransactionManager.h"
#include "FileManager.h"
#include "Gui.h"

int main() {
    TransactionManager manager;
    const std::string filename = "data/transactions.txt";

    FileManager::load(manager.getAll(), filename);

    Gui gui(manager);
    gui.run();

    FileManager::save(manager.getAll(), filename);

    return 0;
}
