#include "TransactionManager.h"
#include <iostream>
#include <iomanip>

int TransactionManager::nextId() const {
	if (transactions.empty()) {
		return 1;
	}
	return transactions.back().id + 1;
}

int TransactionManager::findById(int id) const {
	for (size_t i = 0; i < transactions.size(); i++)
	{
		if (transactions[i].id == id) return static_cast<int>(i);
	}
	return -1;
}

void TransactionManager::addTransaction(const std::string& type,
										const std::string& category,
										double amount,
										const std::string& date) {
	Transaction t;
	t.id = nextId();
	t.type = type;
	t.category = category;
	t.amount = amount;
	t.date = date;

	transactions.push_back(t);
}

bool TransactionManager::editTransaction(int id,
										 const std::string& type,
									 	 const std::string& category,
										 double amount,
										 const std::string& date) {
	int idx = findById(id);
	if (idx == -1)
		return false;
	transactions[idx].type = type;
	transactions[idx].category = category;
	transactions[idx].amount = amount;
	transactions[idx].date = date;
	return true;
}

bool TransactionManager::deleteTransaction(int id) {
	int idx = findById(id);
	if (idx == -1)
	{
		return false;
	}
	transactions.erase(transactions.begin() + idx);
	return true;
}

void TransactionManager::showMonthlySummary(const std::string& yearMonth) const {
	double totalIncome = 0.0;
	double totalExpense = 0.0;
	std::map<std::string, double> categoryTotals;

	for (const auto& t : transactions) {
		if (t.date.rfind(yearMonth, 0) == 0) { 
			if (t.type == "income") totalIncome += t.amount;
			else totalExpense += t.amount;

			categoryTotals[t.category] += t.amount;
		}
	}

	std::cout << "\n===== Summary for " << yearMonth << " =====\n";
	std::cout << "Total Income:  " << totalIncome << "\n";
	std::cout << "Total Expense: " << totalExpense << "\n";
	std::cout << "Net Balance:   " << (totalIncome - totalExpense) << "\n\n";

	std::cout << "Category Totals:\n";
	for (auto& c : categoryTotals) {
		std::cout << " - " << c.first << ": " << c.second << "\n";
	}
	std::cout << "=====================================\n\n";
}

double TransactionManager::getTotalBalance()
{
	double totalIncome = 0.0;
	double totalExpense = 0.0;

	for (const auto& t : transactions)
	{
		if (t.type == "income") totalIncome += t.amount;
		else totalExpense += t.amount;
	}
	return totalIncome - totalExpense;
}