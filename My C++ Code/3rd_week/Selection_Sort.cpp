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

    static void selectionSort(T *start, T *end);
};

template <class T>
void Sorting<T>::selectionSort(T *start, T *end)
{
    int size = end - start;

    int smallest;

    for (int currentElement = 0; currentElement < size - 1; currentElement++)
    {
        smallest = currentElement;

        for (int Index = currentElement + 1; Index < size; Index++)
        {
            if (start[Index] < start[smallest])
                smallest = Index;
        }

        int hold = start[currentElement];
        start[currentElement] = start[smallest];
        start[smallest] = hold;

        printArray(start, end);
    }
}

int main()
{
    int arr[] = {9, 2, 8, 1, 0, -2};
    Sorting<int>::selectionSort(&arr[0], &arr[6]);

    return 0;
}
