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
    // https://www.prodevelopertutorial.com/perform-bubble-sort-on-singly-linked-list-solution-in-c/

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

    for (int i = 0; i < int(sizeof(arr)) / 4; i++)
        list.add(arr[i]);

    list.bubbleSort();
    //list.printList();

    return 0;
}