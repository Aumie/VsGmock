#include <ostream>

#include "pch.h"
#include <gmock/gmock.h>

#include "../GG/BankAccount.h"
#include "../GG/Mathh.h"
#include "../GG/MyClass.h"
#include "../GG/Stack.h"

TEST(TestCaseName, TestName) {
	auto m = new Mathh();
	EXPECT_EQ(m->add(1,1), 2);
}


TEST(ClassTest, Incrementby5) {
	MyClass mc(100);

	mc.Increment(5);

	ASSERT_EQ(mc.getValue(), 105);
}

struct MyclassTest : public testing::Test {
	MyClass* mct;
	void SetUp() { std::cout << "Alive\n"; mct = new MyClass(100); }
	void TearDown() { std::cout << "Dead"; delete mct; }
};

TEST_F(MyclassTest, Incrementby10) {
	mct->Increment(10);
	std::cout << "Test_F\n";
	ASSERT_EQ(mct->getValue(), 110);
}


struct stackTest : public testing::Test {
	Stack sl;
	void SetUp() {
		int value[] = { 1,2,3,4,5,6 };
		for (auto& val : value) {
			sl.push(val);
		}
	};
	void TearDown() {

	};
};

TEST_F(stackTest, PopTest) {
	int lastPoppedValue = 6;
	while (lastPoppedValue != 1) {
		ASSERT_EQ(sl.pop(), lastPoppedValue--);
	}
}

TEST_F(stackTest, sizeValidate) {
	int val = sl.size();
	for (val; !val; val--) {
		//ASSERT_EQ(sl.pop(), val);
		ASSERT_NE(sl.pop(), -1);
	}
}


struct BankAccountTest : testing::Test {
	BankAccount* account;
	BankAccountTest() {
		account = new BankAccount();
	}
	~BankAccountTest() {
		delete account;
	}
};

TEST_F(BankAccountTest, BankAccountStartsEmpty)
{
	EXPECT_EQ(0, account->balance);
}

TEST_F(BankAccountTest, CanDepositMoney) {
	account->deposit(100);
	EXPECT_EQ(100, account->balance);
}

struct account_state {
	int initial_balance;
	int withdraw_amount;
	int final_balance;
	bool success;


	friend std::ostream& operator<<(std::ostream& os, const account_state& obj)
	{
		return os
			<< "initial_balance: " << obj.initial_balance
			<< " withdraw_amount: " << obj.withdraw_amount
			<< " final_balance: " << obj.final_balance
			<< " success: " << obj.success;
	}
};

struct WithdrawAccountTest : BankAccountTest, testing::WithParamInterface<account_state> {
	WithdrawAccountTest() {
		account->balance = GetParam().initial_balance;
	}
};
TEST_P(WithdrawAccountTest, FinalBalance) {
	auto as = GetParam();
	auto success = account->withdraw(as.withdraw_amount);
	EXPECT_EQ(as.final_balance, account->balance);
	EXPECT_EQ(as.success, success);
}
INSTANTIATE_TEST_CASE_P(Default, WithdrawAccountTest, testing::Values(
	account_state{ 100,50,50,true },
	account_state{ 100,200,100,false }
));