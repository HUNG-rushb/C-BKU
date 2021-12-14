#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

bool isValidParentheses(string s)
{
    stack<char> myStack;
    int string_size = s.size();

    for (int i = 0; i < string_size; i++)
    {
        // Push
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
            myStack.push(s[i]);

        // Pop
        if (s[i] == ')')
        {
            if (myStack.empty() || myStack.top() != '(')
                return false;

            myStack.pop();
        }

        if (s[i] == ']')
        {
            if (myStack.empty() || myStack.top() != '[')
                return false;

            myStack.pop();
        }

        if (s[i] == '}')
        {
            if (myStack.empty() || myStack.top() != '{')
                return false;

            myStack.pop();
        }
    }

    return myStack.empty();
}

int main()
{
    cout << isValidParentheses("[");
    return 0;
}