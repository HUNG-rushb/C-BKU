#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

int baseballScore(string ops)
{
    stack<int> myStack;

    int string_size = ops.size();
    int result = 0;

    for (int i = 0; i < string_size; i++)
    {
        // NUMBER
        switch (ops[i])
        {
        case '0':
            myStack.push(0);
            break;

        case '1':
            myStack.push(1);
            break;

        case '2':
            myStack.push(2);
            break;

        case '3':
            myStack.push(3);
            break;

        case '4':
            myStack.push(4);
            break;

        case '5':
            myStack.push(5);
            break;

        case '6':
            myStack.push(6);
            break;

        case '7':
            myStack.push(7);
            break;

        case '8':
            myStack.push(8);
            break;

        case '9':
            myStack.push(9);
            break;

        default:
            break;
        }

        // CHARACTER
        if (ops[i] == 'C')
        {
            if (myStack.empty())
                continue;

            myStack.pop();
        }

        if (ops[i] == 'D')
        {
            if (myStack.empty())
                continue;

            int a = myStack.top();
            a *= 2;
            myStack.push(a);
            //myStack.push(2 * myStack.top());
        }

        if (ops[i] == '+')
        {
            if (myStack.size() < 2)
                continue;

            int top_1st = myStack.top();
            myStack.pop();
            int top_2nd = myStack.top();

            int new_top = top_1st + top_2nd;

            myStack.push(top_1st);
            myStack.push(new_top);
        }
    }

    // Calculate SUM
    int my_stack_size = myStack.size();
    for (int i = 0; i < my_stack_size; i++)
    {
        result += myStack.top();
        myStack.pop();
    }

    return result;
}

int main()
{
    cout << baseballScore("524CD9++");
    return 0;
}