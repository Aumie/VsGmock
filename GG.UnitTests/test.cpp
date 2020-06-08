#include <ostream>

#include "pch.h"
#include <gmock/gmock.h>

#include "../GG/BankAccount.h"
#include "../GG/Mathh.h"
#include "../GG/MyClass.h"
#include "../GG/Stack.h"
#include "../GG/TryMock.h"


TEST(TestCaseName, TestName) {
	auto m = new Mathh();
	EXPECT_EQ(m->add(1, 1), 2);
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


//mock
class MockDB : public DataBaseConnect
{
public:
	MOCK_METHOD(int, fetchRecord, (), (override)); // new style
	//MOCK_METHOD0(fetchRecord, int());	// old style
	//MOCK_METHOD1(logout, bool(std::string usrname));
	MOCK_METHOD(bool,logout,(std::string usrname));
	MOCK_METHOD2(login, bool(std::string usrname, std::string pwd));
	MOCK_METHOD2(login2, bool(std::string usrname, std::string pwd));
	
};

TEST(MyDBTest, loginTest)
{
	//Arrage
	MockDB mdb;
	MyDatabase db(mdb);
	// _ = whatever
	/*EXPECT_CALL(mdb, login(/*"termi", "lol"#1#testing::_,testing::_)).Times(1)
		.WillOnce(testing::Return(true));*/
	ON_CALL(mdb, login(testing::_, testing::_)).WillByDefault(testing::Return(true));
	ON_CALL(mdb, login2(testing::_, testing::_)).WillByDefault(testing::Return(true));
	
	//Act
	int retval = db.init("termi", "lol");
	//Assert
	EXPECT_EQ(retval, 1);
}

TEST(Fetch,rcord)
{
	MockDB mdb;
	
	ON_CALL(mdb, fetchRecord()).WillByDefault(testing::Return(1));
	ON_CALL(mdb, login(testing::_, testing::_)).WillByDefault(testing::Return(true));
	
	int val = mdb.fetchRecord();

	EXPECT_EQ(val, 1);
}

class MockMathh:public Mathh
{
	Mathh& _m;
public:
	MockMathh(Mathh& mm):_m(mm){}
	MOCK_METHOD(bool, gtt, (int a, int b), (override));
	MOCK_METHOD(int, add, (int a, int b), (override));
	
}; 
TEST(Sequence,sq)
{
	Mathh m;
	MockMathh mm(m);
	
	ON_CALL(mm, gtt(testing::_,testing::_)).WillByDefault(testing::Return(true));

	EXPECT_CALL(mm, gtt(testing::_, testing::_));

	bool ret = mm.gtt(6, 8);
	EXPECT_EQ(ret,false);
	// must fail
}
TEST(Sequence,sq2)
{
	Mathh m;
	MockMathh mm(m);

	testing::Sequence s1;
	EXPECT_CALL(mm, add(testing::_,testing::_)).InSequence(s1);
	EXPECT_CALL(mm, gtt(testing::_, testing::_)).InSequence(s1);

	mm.gtt(5, 6);
	mm.add(5, 6);
	//must fail
}


