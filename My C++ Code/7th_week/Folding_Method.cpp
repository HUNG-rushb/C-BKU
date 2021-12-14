#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>
using namespace std;

int take_number(string &number, int ad_size)
{
    if (number == "")
        return 0;

    int number_size = number.size();

    if (number_size < ad_size)
    {
        int a = stoi(number);
        number.clear();
        return a;
    }

    string result = "";

    int i = 0;

    for (; i < ad_size; i++)
    {
        result += number[i];
    }

    number.erase(0, i);
    return stoi(result);
}

int countDigit(long long n)
{
    int count = 0;

    while (n != 0)
    {
        n = n / 10;
        ++count;
    }

    return count;

    //    if (n == 0)
    //        return 0;
    //    return 1 + countDigit(n / 10)
}

void reverseStr(string &str)
{
    int n = str.length();

    // Swap character starting from two corners
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}

int foldShift(long long key, int addressSize)
{
    string my_key = to_string(key);
    int total = 0;

    int key_digit = countDigit(key);
    int total_pieces = (key_digit / addressSize) + 1;

    for (int i = 0; i <= total_pieces; i++)
    {
        total += take_number(my_key, addressSize);
    }

    my_key = to_string(total);

    int result_size = my_key.size();
    if (result_size > addressSize)
    {
        int a = result_size - addressSize;

        if (a == 1)
        {
            int c = pow(10, addressSize);

            total = total - (total / c) * c;
        }
        else if (a > 1)
        {
            my_key.erase(0, a - 1);
            total = stoi(my_key);
        }

        return total;
    }
    else
        return total;
}

int rotation(long long key, int addressSize)
{
    int result = foldShift(key, addressSize);

    string final_result = to_string(result);
    reverseStr(final_result);

    return stoi(final_result);
}

int main()
{
    cout << foldShift(1234567891234, 3);
    return 0;
}