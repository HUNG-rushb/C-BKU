//#include <iostream>
//using namespace std;
//
//template <class T>
//class Sorting
//{
//public:
//    /* Function to print an array */
//    static void printArray(T *start, T *end)
//    {
//        int size = end - start;
//        for (int i = 0; i < size - 1; i++)
//            cout << start[i] << ", ";
//        cout << start[size - 1];
//        cout << endl;
//    }
//
//    static void selectionSort(T *start, T *end);
//    static void oddEvenSort(T *start, T *end);
//};
//
//template <class T>
//void Sorting<T>::selectionSort(T *start, T *end)
//{
//    int size = end - start;
//
//    int smallest;
//
//    for (int currentElement = 0; currentElement < size - 1; currentElement++)
//    {
//        smallest = currentElement;
//
//        for (int Index = currentElement + 1; Index < size; Index++)
//        {
//            if (start[Index] < start[smallest])
//                smallest = Index;
//        }
//
//        int hold = start[currentElement];
//        start[currentElement] = start[smallest];
//        start[smallest] = hold;
//
//        printArray(start, end);
//    }
//}
//
//template <class T>
//void Sorting<T>::oddEvenSort(T *start, T *end)
//{
//    int size = end - start;
//
//    bool isSorted = false;
//
//    while (!isSorted)
//    {
//        isSorted = true;
//
//        // Perform Bubble sort on even indexed element
//        for (int i = 0; i <= size - 2; i = i + 2)
//        {
//            if (start[i] > start[i + 1])
//            {
//                int hold = start[i];
//                start[i] = start[i + 1];
//                start[i + 1] = hold;
//
//                isSorted = false;
//            }
//        }
//
//        // Perform Bubble sort on odd indexed element
//        for (int i = 1; i <= size - 2; i = i + 2)
//        {
//            if (start[i] > start[i + 1])
//            {
//                int hold = start[i];
//                start[i] = start[i + 1];
//                start[i + 1] = hold;
//
//                isSorted = false;
//            }
//        }
//
//        printArray(start, end);
//    }
//
//    return;
//}
//
//int main()
//{
//    //    int arr[] = {9, 2, 8, 1, 0, -2};
//    //    Sorting<int>::selectionSort(&arr[0], &arr[6]);
//
//    int arr[] = {3, 2, 3, 8, 5, 6, 4, 1};
//    Sorting<int>::oddEvenSort(&arr[0], &arr[8]);
//
//    return 0;
//}

#include <iostream>
#include <sstream>
using namespace std;

template <class T>
class SLinkedList
{
public:
    class Node; // Forward declaration
protected:
    Node *head;
    Node *tail;
    int count;

public:
    SLinkedList()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->count = 0;
    }

    ~SLinkedList(){};

    void add(T e)
    {
        Node *pNew = new Node(e);

        if (this->count == 0)
        {
            this->head = this->tail = pNew;
        }
        else
        {
            this->tail->next = pNew;
            this->tail = pNew;
        }

        this->count++;
    }

    int size()
    {
        return this->count;
    }

    void printList()
    {
        stringstream ss;
        ss << "[";
        Node *ptr = head;
        while (ptr != tail)
        {
            ss << ptr->data << ",";
            ptr = ptr->next;
        }

        if (count > 0)
            ss << ptr->data << "]";
        else
            ss << "]";
        cout << ss.str() << endl;
    }

public:
    class Node
    {
    private:
        T data;
        Node *next;
        friend class SLinkedList<T>;

    public:
        Node()
        {
            next = 0;
        }

        Node(T data)
        {
            this->data = data;
            this->next = nullptr;
        }
    };

    void bubbleSort();
};

template <class T>
void SLinkedList<T>::bubbleSort()
{
    Node *left_Ptr;         // will point to this->head
    Node *right_Ptr = NULL; // will point to the biggest

    bool swapped;
    do
    {
        swapped = false;
        left_Ptr = this->head;

        // Duyet qua ca list
        // vong lap dau tien right_Ptr = NULL
        while (left_Ptr->next != right_Ptr)
        {
            // Neu nhu left > right
            if (left_Ptr->data > left_Ptr->next->data)
            {
                // Swap data
                T temp = left_Ptr->data;
                left_Ptr->data = left_Ptr->next->data;
                left_Ptr->next->data = temp;

                // Da xay ra thay doi
                swapped = true;
            }

            // Tien toi node tiep theo
            left_Ptr = left_Ptr->next;
        }

        // In list neu co thay doi
        if (swapped)
            this->printList();

        // left gio day dang nam giu gia tri lon nhat sau vong lap
        // gan cho right
        right_Ptr = left_Ptr;
    } while (swapped); // end neu nhu khong xay ra su thay doi nao
}

//template <class T>
//void SLinkedList<T>::bubbleSort()
//{
//    for (int i = 0; i < count - 1; ++i)
//    {
//        for (int j = 0; j < count - 1; ++j)
//        {
//            Node *p1 = this->head, *p2 = this->head;
//            int m = j, n = j + 1;
//            while (m--) p1 = p1->next;
//            while (n--) p2 = p2->next;
//
//            if (p1->data > p2->data)
//            {
//                T tmp = p1->data;
//                p1->data = p2->data;
//                p2->data = tmp;
//            }
//        }
//        printList();
//    }
//}

int main()
{
    int arr[] = {9, 2, 8, 4, 1};
    SLinkedList<int> list;
    for(int i = 0; i <int(sizeof(arr))/4;i++)
        list.add(arr[i]);

    list.bubbleSort();
}
