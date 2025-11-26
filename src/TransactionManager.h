#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <vector>
#include <string>
#include <map>
#include "Transaction.h"

class TransactionManager
{
public:
	void addTransaction(const std::string& type,
						const std::string& category,
						double amount,
						const std::string& date);
	
	bool editTransaction(int id,
						 const std::string& type,
						 const std::string& category,
						 double amount,
						 const std::string& date);
	
	bool deleteTransaction(int id);

	void showMonthlySummary(const std::string& yearMonth) const;

	std::vector<Transaction>& getAll() { return transactions; };

	double getTotalBalance();
private:
	std::vector<Transaction> transactions;

	int nextId() const;
	int findById(int id) const;
};

#endif // !TRANSACTION_MANAGER_H
