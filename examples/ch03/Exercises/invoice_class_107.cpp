#include <iostream>
using namespace std;

class Invoice
{
public:
    Invoice(string, string, int, int);
    void setPartNumber(string);
    void setPartDescription(string);
    void setQuantity(int);
    void setPrive(int);

    string getPartNumber();
    string getPartDesciption();
    int getQuantity();
    int getPrice();

    void getInvoiceAmount(int, int);

private:
    string partNumber, partDescription;
    int quantity, price;
};

Invoice::Invoice(string partNumber, string partDescription, int quantity, int price)
{
}

int main()
{
    Invoice wheely(1913652, );
    return 0;
}