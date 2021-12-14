#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

long int midSquare(long int seed)
{
    long int result;

    long long key = seed;
    key = key * key;

    long int deleted_2_key = key / 100;

    long int deleted_4_key = deleted_2_key / 10000;
    deleted_4_key = deleted_4_key * 10000;

    result = deleted_2_key - deleted_4_key;
    return result;
}

long int digitExtraction(long int seed, int *extractDigits, int size)
{
    string string_result = "";
    string string_seed = "";
    string_seed = to_string(seed);

    long int result;

    int coconut = 0;

    for (int i = 0; i < size; i++)
    {
        coconut = extractDigits[i];
        string_result += string_seed[coconut];
    }

    result = stoi(string_result);
    return result;
}

long int moduloDivision(long int seed, long int mod)
{
    long int result = 0;
    result = seed % mod;

    return result;
}

int main()
{
    int a[] = {0, 1, 4, 5};
    cout << midSquare(midSquare(11111) - digitExtraction(111224423, a, 4) * moduloDivision(22222, 12));

    return 0;
}