#pragma once
class BankAccount
{
public:
	int balance = 0;
	BankAccount() {}
	explicit BankAccount(const int balance) : balance{ balance }
	{}
	void deposit(int amount);

	bool withdraw(int amount);
};

