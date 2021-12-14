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
        long size = end - start + 1;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void merge(T *left, T *middle, T *right)
    {
        T i, j, k;
        T n1 = middle - left + 1;
        T n2 = right - middle;
        /* Tạo các mảng tạm */
        T *L = new T[n1], *R = new T[n2];
        /* Copy dữ liệu sang các mảng tạm */
        for (i = 0; i < n1; i++)
            L[i] = left[i];
        for (j = 0; j < n2; j++)
            R[j] = middle[1 + j];

        /* Gộp hai mảng tạm vừa rồi vào mảng arr*/
        i = 0; // Khởi tạo chỉ số bắt đầu của mảng con đầu tiên
        j = 0; // Khởi tạo chỉ số bắt đầu của mảng con thứ hai
        k = 0; // IKhởi tạo chỉ số bắt đầu của mảng lưu kết quả
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
            {
                left[k] = L[i];
                i++;
            }
            else
            {
                left[k] = R[j];
                j++;
            }
            k++;
        }

        /* Copy các phần tử còn lại của mảng L vào arr nếu có */
        while (i < n1)
        {
            left[k] = L[i];
            i++;
            k++;
        }

        /* Copy các phần tử còn lại của mảng R vào arr nếu có */
        while (j < n2)
        {
            left[k] = R[j];
            j++;
            k++;
        }
        Sorting::printArray(left, right);
    }

    static void mergeSort(T *start, T *end)
    {
        if (start < end)
        {
            int m = (end - start) / 2;
            mergeSort(start, &start[m]);
            mergeSort(&start[m + 1], end);

            merge(start, &start[m], end);
        }
    }
};
#endif /* SORTING_H */

int main()
{
    int arr[] = {0, 2, 4, 3, 1, 4};
    Sorting<int>::mergeSort(&arr[0], &arr[5]);
    return 0;
}