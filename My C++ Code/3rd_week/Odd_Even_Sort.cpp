#include <iostream>
using namespace std;

template <class T>
class Sorting
{
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void oddEvenSort(T *start, T *end);
};

template <class T>
void Sorting<T>::oddEvenSort(T *start, T *end)
{
    int size = end - start;

    bool isSorted = false;

    while (!isSorted)
    {
        isSorted = true;

        // Perform Bubble sort on even indexed element
        for (int i = 0; i <= size - 2; i = i + 2)
        {
            if (start[i] > start[i + 1])
            {
                int hold = start[i];
                start[i] = start[i + 1];
                start[i + 1] = hold;

                isSorted = false;
            }
        }

        // Perform Bubble sort on odd indexed element
        for (int i = 1; i <= size - 2; i = i + 2)
        {
            if (start[i] > start[i + 1])
            {
                int hold = start[i];
                start[i] = start[i + 1];
                start[i + 1] = hold;

                isSorted = false;
            }
        }

        printArray(start, end);
    }

    return;
}

int main()
{
    //    int arr[] = {9, 2, 8, 1, 0, -2};
    //    Sorting<int>::selectionSort(&arr[0], &arr[6]);

    int arr[] = {3, 2, 3, 8, 5, 6, 4, 1};
    Sorting<int>::oddEvenSort(&arr[0], &arr[8]);

    return 0;
}
