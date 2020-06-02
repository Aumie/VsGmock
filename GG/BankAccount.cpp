#include "BankAccount.h"

void BankAccount::deposit(int amount) {
	balance += amount;
}

bool BankAccount::withdraw(int amount) {
	if (amount <= balance)
	{
		balance -= amount;
		return true;
	}
	return false;
}