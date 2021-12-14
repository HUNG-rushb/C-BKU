#include <iostream>
using namespace std;

//QuickSort is one of the fastest sorting algorithms for sorting large data.
//When implemented well, it can be about two or three times faster than its main competitors, such as MergeSort and HeapSort.
//When the number of elements is below some threshold (min_size),
//switch to insertion sort - non-recursive sorting algorithm that performs fewer swaps, comparisons or other operations on such small arrays.
//
//Implement static methods hybridQuickSort in class Sorting to sort an array in ascending order.
//If you do insertion sort, please print "Insertion sort: array" (using printArray) first.
//If you do quick sort, please print "Quick sort: array (using printArray)" first.
//Please read example carefully to know exactly what we print.
//
//To match the test cases, please note:
//
//    Using first element as pivot
//    Recursively call the hybridQuickSort function to the left of the pivot first, then recursively to the right of the pivot
//    Do insertion sort if sub array size smaller than min_size

template <class T>
class Sorting
{
private:
    static T *Partition(T *start, T *end);

public:
    static void printArray(T *start, T *end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    };

    static void insertionSort(T *start, T *end);

    static void hybridQuickSort(T *start, T *end, int min_size);
};

template <class T>
T *Sorting<T>::Partition(T *start, T *end)
{
    // TODO: return the pointer which points to the pivot after rearrange the array.
    T pivot = *start;

    int low = 0;
    int high = end - start - 1;

    int left = 0;
    int right = high + 1;

    while (true)
    {
        // left tang den khi gap so lon hon pivot
        do
        {
            left++;
        } while (start[left] < pivot);

        // right giam toi khi gap so be hon pivot
        do
        {
            right--;
        } while (start[right] > pivot);

        swap(start[left], start[right]);

        if (left >= right)
            break;
    }

    swap(start[left], start[right]);
    swap(start[low], start[right]);
    return &start[right];
}

template <class T>
void Sorting<T>::insertionSort(T *start, T *end)
{
}

template <class T>
void Sorting<T>::hybridQuickSort(T *start, T *end, int min_size)
{
    while (end - start > 0)
    {
        if (end - start < min_size)
        {
            cout << "Insertion sort: ";
            printArray(start, end);
            break;
        }
        else
        {
            cout << "Quick sort: ";
            printArray(start, end);

            T *pivot = Partition(start, end);

            hybridQuickSort(start, pivot, min_size);
            start = pivot + 1;

            hybridQuickSort(pivot + 1, end, min_size);
            end = pivot - 1;
        }
    }
}
int main()
{
    //    int array[] = {1, 2, 6, 4, 7, 8, 5, 3};
    //    int min_size = 4;
    //    Sorting<int>::hybridQuickSort(&array[0], &array[8], min_size);

    int array[] = {2, 6, 4, 12, 23, 1, 0, -12};
    int min_size = 4;
    Sorting<int>::hybridQuickSort(&array[0], &array[8], min_size);

    return 0;
}
