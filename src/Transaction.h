#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

struct Transaction {
	int id;
	std::string type;
	std::string category;
	double amount;
	std::string date;
};


#endif // !TRANSACTION_H