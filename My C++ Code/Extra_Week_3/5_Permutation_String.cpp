#ifndef SORTINGAPPLICATION_H
#define SORTINGAPPLICATION_H
#include <iostream>
#include <string>
using namespace std;
#endif /* SORTINGAPPLICATION_H */

#define total_char 256
bool isPermutation(string a, string b)
{
    // Create 2 count arrays and initialize
    // all values as 0
    int count1[total_char] = {0};
    int count2[total_char] = {0};
    int i;

    // For each character in input strings,
    // increment count in the corresponding
    // count array
    for (i = 0; a[i] && b[i]; i++)
    {
        int c = a[i];
        int d = b[i];
        count1[c] += 1;
        count2[d] += 1;
    }

    // If both strings are of different length.
    // Removing this condition will make the
    // program fail for strings like "aaca"
    // and "aca"
    if (a[i] || b[i])
        return false;

    // Compare count arrays
    for (i = 0; i < total_char; i++)
        if (count1[i] != count2[i])
            return false;

    return true;
}

int main()
{
    string a = "abbac";
    string b = "baba";

    cout << isPermutation(a, b);
}