#include <stdio.h>
#include <iostream>
using namespace std;

// https://phattrienphanmem123az.com/thuat-toan-lap-trinh/thuat-toan-interpolation-search.html
int interpolationSearch(int arr[], int left, int right, int target)
{
    if (left <= right && target >= arr[left] && target <= arr[right])
    {
        double value_1 = (double)(target - arr[left]) / (arr[right] - arr[left]);
        int value_2 = (right - left);
        int current_position = left + value_1 * value_2;

        cout << "We traverse on index: " << current_position << endl;

        if (arr[current_position] == target)
            return current_position;

        if (arr[current_position] < target)
        {
            left = current_position + 1;
            interpolationSearch(arr, left, right, target);
        }
        else
        {
            right = current_position - 1;
            interpolationSearch(arr, left, right, target);
        }
    }

    return -1;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 6;
    int result = interpolationSearch(arr, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array" : cout << "Element is present at index " << result;

    return 0;
}
