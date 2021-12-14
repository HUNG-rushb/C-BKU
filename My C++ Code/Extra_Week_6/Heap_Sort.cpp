#define SEPARATOR "#<ab@17943918#@>#"
#ifndef SORTING_H
#define SORTING_H
#include <iostream>
using namespace std;

template <class T>
class Sorting
{
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        long size = end - start;

        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];

        cout << endl;
    }

    // https://www.geeksforgeeks.org/heap-sort/
    static void heapify(int arr[], int size, int i)
    {
        int largest = i;       // Initialize largest as root
        int left = 2 * i + 1;  // left = 2*i + 1
        int right = 2 * i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (left < size && arr[left] > arr[largest])
            largest = left;

        // If right child is larger than largest so far
        if (right < size && arr[right] > arr[largest])
            largest = right;

        // If largest is not root
        if (largest != i)
        {
            swap(arr[i], arr[largest]);

            // Recursively heapify the affected sub-tree
            heapify(arr, size, largest);
        }
    }

    static void heapSort(T *start, T *end)
    {
        //TODO
        long size = end - start;

        // Build heap (rearrange array)
        for (int i = size / 2 - 1; i >= 0; i--)
            heapify(start, size, i);

        // One by one extract an element from heap
        for (int i = size - 1; i > 0; i--)
        {
            // Move current root to end
            swap(start[0], start[i]);

            // call max heapify on the reduced heap
            heapify(start, i, 0);
        }

        Sorting<T>::printArray(start, end);
    }
};
#endif /* SORTING_H */

int main()
{
    int arr[4] = {4, 2, 9, 1};
    Sorting<int>::heapSort(&arr[0], &arr[4]);

    return 0;
}
