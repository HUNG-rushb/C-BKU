#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

// Given an array of distinct integers, find if there are two pairs (a, b) and (c, d)
// such that a+b = c+d, and a, b, c and d are distinct elements.

// If there are multiple answers, you can find any of them.
bool findPairs(int arr[], int n, pair<int, int> &pair1, pair<int, int> &pair2)
{
    vector<int> my_Vector;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            my_Vector.push_back(arr[i] + arr[j]);
            my_Vector.push_back(arr[i]);
            my_Vector.push_back(arr[j]);
        }
    }

    for (unsigned int i = 0; i < my_Vector.size() - 1; i = i + 3)
    {
        for (unsigned int j = i + 3; j < my_Vector.size(); j = j + 3)
        {
            if (my_Vector[i] == my_Vector[j])
            {
                pair1.first = my_Vector[i + 1];
                pair1.second = my_Vector[i + 2];

                pair2.first = my_Vector[j + 1];
                pair2.second = my_Vector[j + 2];

                return 1;
            }
        }
    }

    return 0;
}

int main()
{
    // int arr[] = {3, 4, 7, 1, 2, 9, 8};
    // int n = sizeof arr / sizeof arr[0];
    // pair<int, int> pair1, pair2;
    // if (findPairs(arr, n, pair1, pair2))
    // {
    //     if (checkAnswer(arr, n, pair1, pair2))
    //     {
    //         printf("Your answer is correct.\n");
    //     }
    //     else
    //         printf("Your answer is incorrect.\n");
    // }
    // else
    //     printf("No pair found.\n");

    return 0;
}