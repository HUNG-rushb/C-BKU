#include <iostream>

using namespace std;

class Employee
{
public:
    Employee(string, string, int);
    void setFirstName(string);
    void setLastName(string);
    void setSalary(int);
    string getFirstname();
    string getLastName();
    int getSalary();
    int raiseSalary();
    void demo();
private:
    string firstName, lastName;
    int monthlySalary;

};

Employee::Employee(string yourFirstName, string yourLastName, int yourSalary)
{
    setFirstName(yourFirstName);
    setLastName(yourLastName);

    if (yourSalary < 0)
    {
        cout << "Your salary cant be negative, plz change!";
        setSalary(0);
    }
    else
    {
        setSalary(yourSalary);
    }
}

void Employee::setFirstName(string yourFirstName)
{
    firstName = yourFirstName;
}

void Employee::setLastName(string yourLastName)
{
    lastName = yourLastName;
}

void Employee::setSalary(int yourSalary)
{
    monthlySalary = yourSalary;
}

string Employee::getFirstname()
{
    return firstName;
}

string Employee::getLastName()
{
    return lastName;
}

int Employee::getSalary()
{
    return monthlySalary;
}

void Employee::demo()
{
    cout << "\n--------------------------------------------------------";
    cout << "\nYour name is: " << getFirstname() << " " << getLastName() << ".";
    cout << "\nYour monthly salary is: " << getSalary() << "$.";
}

int Employee::raiseSalary()
{
    return monthlySalary = monthlySalary * 1.1;
}

int main()
{
    string firstName, lastName;
    int salary;

    cout << "Please input your information!";
    cout << "\nFirst name: ";
    getline(cin, firstName);
    cout << "Last name: ";
    getline(cin, lastName);
    cout << "Your monthly salary: ";
    cin >> salary;

    Employee Hung(firstName, lastName, salary);
    Hung.demo();
    Hung.raiseSalary();
    Hung.demo();
    return 0;
}
