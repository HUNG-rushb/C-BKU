#include <iostream>
using namespace std;

class Account
{
public:
    Account(int);
    void setBalance(int);
    int getBalance();
    void credit(int);
    void debit(int);

private:
    int balance;
};

Account::Account(int your_balance)
{
    if (your_balance < 0)
    {
        setBalance(0);
        cout << "Your balance must be greater than 0. Please try again!";
    }
    else
    {
        setBalance(your_balance);
        cout << "Your current balance is: " << getBalance();
        cout << "\n-------------------------------\n";
    }
}

void Account::setBalance(int your_balance)
{
    balance = your_balance;
}

int Account::getBalance()
{
    return balance;
}

void Account::credit(int bonus)
{
    balance += bonus;
    cout << "You have successfully add " << bonus << " to your balance.";
    cout << "\nYour new balance is " << balance << ".";
    cout << "\n-------------------------------\n";
}

void Account::debit(int draw)
{
    if (draw > balance)
    {
        cout << "Debit amount exceeded account balance.";
        cout << "\n------------------------------------\n";
    }
    else
    {
        balance -= draw;
        cout << "You have draw successfully " << draw << " from your account.";
        cout << "\nYour new balance is " << balance << ".";
        cout << "\n--------------------------\n";
    }
}

int main()
{
    int your_balance;
    cout << "Please enter your balance: ";
    cin >> your_balance;

    Account hung(your_balance);
    hung.credit(10);
    hung.debit(70);

    return 0;
}
