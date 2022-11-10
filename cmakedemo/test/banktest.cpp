#include <gtest/gtest.h>

#include <iostream>
using namespace std;

/**
 * @brief 判断n是否为质数
 * @param n 输入值
 * @return true n为质数
 * @return false n不为质数
 */
bool IsPrime(int n) {
  if (n <= 1) return false;
  if (n % 2 == 0) return n == 2;
  for (int i = 3;; i += 2) {
    if (i > n / i) break;
    if (n % i == 0) return false;
  }
  return true;
}

class IsPrimeParamTest : public::testing::TestWithParam<int>{};

TEST_P(IsPrimeParamTest, HandleTrueReturn) {
    int n =  GetParam();
    EXPECT_TRUE(IsPrime(n));
}
INSTANTIATE_TEST_SUITE_P(TrueReturn, IsPrimeParamTest, testing::Values(3, 5, 11, 23, 17));

// 银行账户类
struct BankAccount {
  int balance = 0;  // 余额
  BankAccount() {}
  explicit BankAccount(const int balance) : balance(balance) {}

  /**
   * @brief 存款函数
   * @param amount 存入金额
   * @return
   */
  void deposit(int amount) { balance += amount; }

  /**
   * @brief 取款函数
   * @param amount 取出金额
   * @return
   * - true  交易成功
   * - false 交易失败
   */
  bool withdraw(int amount) {
    if (balance >= amount) {
      balance -= amount;
      return true;
    }
    return false;
  }
};

// 交易类
struct account_state {
  int initial_balance;  // 交易前余额
  int withdraw_amount;  // 消费金额
  int final_balance;    // 交易后余额
  bool success;         // 交易成功

  friend std::ostream& operator<<(std::ostream& os, const account_state& obj)
  {
    return os << "initial_balance: " << obj.initial_balance
              << "withdraw_amount: " << obj.withdraw_amount
              << "final_balance: " << obj.final_balance
              << "success: " << obj.success;
  }
};

// 银行账户测试类
struct BankAccountTest : testing::Test {
  BankAccount* account = nullptr;  // 银行账户
  BankAccountTest() { account = new BankAccount(); }
  virtual ~BankAccountTest() {
    delete account;
    account = nullptr;
  }
};

// 消费测试类
struct WithdrawAccountTest : BankAccountTest,
                             testing::WithParamInterface<account_state> {
  WithdrawAccountTest() { account->balance = GetParam().initial_balance; }
};

TEST_F(BankAccountTest, BankAccountStartsEmpty) {
  EXPECT_EQ(0, account->balance);
}

TEST_F(BankAccountTest, CanDepositMoney) {
  account->deposit(100);
  EXPECT_EQ(100, account->balance);
}

TEST_P(WithdrawAccountTest, FinalBalance) {
  auto as = GetParam();
  auto success = account->withdraw(as.withdraw_amount);
  EXPECT_EQ(as.final_balance, account->balance);
  EXPECT_EQ(as.success, success);
}

INSTANTIATE_TEST_SUITE_P(Default, WithdrawAccountTest,
                        testing::Values(account_state{100, 50, 50, true},
                                        account_state{100, 200, 100,
                                        false}));

int main(int argc, char** argv) {
  testing::GTEST_FLAG(output) = "xml:";
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}