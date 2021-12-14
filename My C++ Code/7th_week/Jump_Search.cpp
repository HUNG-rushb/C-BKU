#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

int jumpSearch(int arr[], int x, int n)
{
    // Finding block size to be jumped
    //cout << n << " ";
    int step = sqrt(n);
    //cout << step << endl;

    // Finding the block where element is
    // present (if it is present)
    int prev = 0;
    cout << prev << " ";

    // compare between current block and n
    while (arr[min(step, n) - 1] < x)
    {
        prev = step;
        cout << prev << " ";
        step += sqrt(n);

        if (step > n)
        {
            cout << n - 1 << " ";

            if (arr[n - 1] < x)
                return -1;

            break;
        }
        else if (arr[min(step, n) - 1] >= x)
        {
            cout << step << " ";
        }
        else if (arr[step] > x)
        {
            cout << step << " ";
            break;
        }

        else if (arr[min(step, n)] == x)
        {
            cout << step << " ";
            return step;
        }

        if (prev >= n)
            return -1;
    }

    // Doing a linear search for x in block
    // beginning with prev.

    while (arr[prev] < x)
    {
        prev++;

        cout << prev << " ";

        // If we reached next block or end of
        // array, element is not present.
        if (prev == min(step, n) - 1)
            return -1;
    }

    // If element is found
    if (arr[prev] == x)
        return prev;

    return -1;
}

int main()
{
    int arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 611, 612, 613, 1000, 1002, 2000, 2003, 2004, 2005, 2006};
    int x = 36;
    int n = sizeof(arr) / sizeof(arr[0]);
    int index = jumpSearch(arr, x, n);

    if (index != -1)
    {
        cout << "\nNumber " << x << " is at index " << index;
    }
    else
    {
        cout << endl;
        cout << x << " is not in array!";
    }

    return 0;
}