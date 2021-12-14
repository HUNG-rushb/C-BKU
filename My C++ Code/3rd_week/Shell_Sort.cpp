#include <iostream>
using namespace std;

#ifndef SORTING_H
#define SORTING_H

#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class Sorting
{
private:
    static void printArray(T *start, T *end)
    {
        int size = end - start;
        for (int i = 0; i < size; i++)
            cout << start[i] << " ";
        cout << endl;
    }

    static void sortSegment(T *start, T *end, int segment_idx, int cur_segment_total)
    {
        int size = end - start;
        for (int i = segment_idx; i < size; i += cur_segment_total)
        {
            T a = start[i];
            int j = i - cur_segment_total;
            while (j > -1 && start[j] > a)
            {
                start[j + cur_segment_total] = start[j];
                j -= cur_segment_total;
            }
            start[j + cur_segment_total] = a;
        }
    }

public:
    static void ShellSort(T *start, T *end, int *num_segment_list, int num_phases)
    {
        // Note: You must print out the array after sorting segments to check whether your algorithm is true.
        for (int i = num_phases - 1; i >= 0; --i)
        {
            int step = num_segment_list[i];
            for (int j = 0; j < step; ++j)
                sortSegment(start, end, j, step);
            cout << step << " segments: ";
            printArray(start, end);
        }
    }
};

#endif /* SORTING_H */

int main()
{

    int num_segment_list[] = {1, 3, 5};
    int num_phases = 3;
    int array[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    Sorting<int>::ShellSort(&array[0], &array[10], &num_segment_list[0], num_phases);
    return 0;
}