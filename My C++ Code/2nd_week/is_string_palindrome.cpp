#include <iostream>
#include <string.h>
using namespace std;

bool isPalRec(string str, int s, int e)
{
    // ignore space
    if (str[s] == ' ')
        return isPalRec(str, s + 1, e);

    if (str[e] == ' ')
        return isPalRec(str, s, e - 1);

    // one character
    if (s == e)
        return true;

    // If first and last characters do not match
    if (str[s] != str[e])
        return false;

    // If there are more than two characters,
    // check if  middle substring is also  palindrome or not.

    if (s < e + 1) // hai chu khong trung nhau
        return isPalRec(str, s + 1, e - 1);

    return true;
}

bool isPalindrome(string str)
{
    int n = str.size();

    // An empty string is considered as palindrome
    if (n == 0)
        return true;

    return isPalRec(str, 0, n - 1);
}

int main()
{
    cout << isPalindrome("mom");
    cout << endl;
    cout << isPalindrome("do geese see god");
    return 0;
}
