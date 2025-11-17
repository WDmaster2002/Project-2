#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include "Transaction.h"

class FileManager {
public:
    static void save(const std::vector<Transaction>& transactions,
        const std::string& filename);

    static void load(std::vector<Transaction>& transactions,
        const std::string& filename);
};

#endif // !FILE_MANAGER_H
