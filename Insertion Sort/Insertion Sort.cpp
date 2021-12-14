
#include <iostream>
#include <math.h>
using namespace std;

void ascendingSort(int a[], int n)
{
    // Insertion sort
    int temp;
    for (int next = 1; next < n; next++)
    {
        temp = a[next];

        int moveItem = next;

        while( (moveItem > 0) && (a[moveItem - 1] > temp))
        {
            a[moveItem] = a[moveItem - 1];
            moveItem--;
        }
        a[moveItem] = temp;
    }
}

void descendingSort(int a[], int n)
{
    // Insertion sort
    int i, j, key;

    for (j = 1; j < n; j++)
    {
        key = a[j];

        for(i = j - 1; (i >= 0) && (a[i] < key); i--)   // Smaller values move up
          {
            a[i+1] = a[i];
          }

        a[i+1] = key;
    }

}

void mySort(int a[], int n, void (*sort)(int[], int))
{
    if (sort == ascendingSort) {
        ascendingSort(a, n);
    }
    else if (sort == descendingSort) {
        descendingSort(a, n);
    }
}

int main()
{
    int n = 5;
    int a[5] = { 1, 2, 3, 4, 5 };

    // Sap xep theo phuong phap Insertion sort

    // tang dan
    //void (*sortAlgorithm)(int[], int) = ascendingSort;

    // giam dan
    void (*sortAlgorithm)(int[], int) = descendingSort;
    mySort(a, n, sortAlgorithm);
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", a[i]);
    }
    return 0;
}

