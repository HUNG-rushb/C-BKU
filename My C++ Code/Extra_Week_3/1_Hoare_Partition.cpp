#ifndef SORTING_H
#define SORTING_H
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

// https://www.techiedelight.com/quick-sort-using-hoares-partitioning-scheme/

template <class T>
class Sorting
{
private:
    static T *Partition(T *start, T *end)
    {
        // TODO: return the pointer which points to the pivot after rearrange the array.
        T pivot = *start;

        int low = 0;
        int high = end - start - 1;

        int left = 0; //low - 1;
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
    };

public:
    static void QuickSort(T *start, T *end)
    {
        // In this question,
        // you must print out the index of pivot in subarray after everytime calling method Partition.

        // Base condition
        if (end - start <= 0)
            return;

        // rearrange the elements across pivot
        T *pivot = Partition(start, end);
        cout << pivot - start << " ";

        // recur on sub-array containing elements that are less than pivot
        QuickSort(start, pivot);

        // recur on sub-array containing elements that are more than pivot
        QuickSort(pivot + 1, end);
    };
};
#endif /* SORTING_H */

int main()
{
    Sorting<int> s;
    int a[] = {3, 5, 7, 10, 12, 14, 15, 13, 1, 2, 9, 6, 4, 8, 11, 16, 17, 18, 20, 19};
    cout << "Index of pivots: ";

    s.QuickSort(&a[0], &a[20]);

    cout << "\nArray after sorting: ";
    for (int i : a)
        cout << i << " ";

    return 0;
}
