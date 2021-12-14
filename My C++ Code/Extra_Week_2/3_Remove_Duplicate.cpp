#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

string removeDuplicates(string S)
{
    stack<char> myStack;
    string result = "";

    int string_size = S.size();
    for (int i = string_size - 1; i >= 0; i--)
    {
        // Stack is empty from the begining
        if (myStack.empty())
        {
            myStack.push(S[i]);
            continue;
        }
        else if (S[i] != myStack.top())
        {
            myStack.push(S[i]);
        }
        else if (S[i] == myStack.top())
        {
            myStack.pop();
        }
    }

    while (!myStack.empty())
    {
        result += myStack.top();
        myStack.pop();
    }

    return result;
}

int main()
{
    cout << removeDuplicates("abbaca");
    return 0;
}