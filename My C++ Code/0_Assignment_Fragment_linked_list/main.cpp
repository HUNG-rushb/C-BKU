#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
using namespace std;

#ifndef ILIST_H
#define ILIST_H

template <class T>
class IList
{
public:
    virtual void add(const T &element) = 0;
    virtual void add(int index, const T &element) = 0;
    virtual T removeAt(int index) = 0;
    virtual bool removeItem(const T &item) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual T get(int index) = 0;
    virtual void set(int index, const T &element) = 0;
    virtual int indexOf(const T &item) = 0;
    virtual bool contains(const T &item) = 0;
    virtual string toString() = 0;
};

#endif

// STUDENT ANSWER
#ifndef FRAGMENT_LINKED_LIST
#define FRAGMENT_LINKED_LIST
template <class T>
class FragmentLinkedList : IList<T>
{
public:
    class Node;
    class Iterator;

protected:
    Node **fragmentPointers;

    Node *first = NULL;
    Node *last = NULL;

    Node *head = new Node;
    Node *tail = new Node;

    /*
       *************         *************              ****************            ****************
       *   head    *   --->  *   first   *   ........   *     last     *     --->   *     tail     *
       *************         *************              ****************            ****************
    */
    int fragmentMaxSize;
    int count;

public:
    FragmentLinkedList(int fragmentMaxSize = 5)
    {
        this->count = 0;
        this->fragmentMaxSize = fragmentMaxSize;

        this->head->next = this->first;
        this->tail->prev = this->last;

        // Fragment Pointers chua cac ptr tro den cac node nam o dau fragment
        this->fragmentPointers = new Node *[2];
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
    }

    virtual ~FragmentLinkedList(){};
    virtual void add(const T &element);
    virtual void add(int index, const T &element);
    virtual T removeAt(int index);
    virtual bool removeItem(const T &item);
    virtual bool empty();
    virtual int size();
    virtual void clear();
    virtual T get(int index);
    virtual void set(int index, const T &element);
    virtual int indexOf(const T &item);
    virtual bool contains(const T &item);
    virtual string toString();

    Iterator begin(int index = 0);
    Iterator end(int index = -1);

    // Ham tu them vao-------------------------------------------------
    void printList();
    void reArrangeFragmentPtr();
    string toString_FragmentPtr();
    int numberOfFrag();


    // Class
public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *prev;
        friend class FragmentLinkedList<T>;

    public:
        Node()
        {
            data = 0;
            next = 0;
            prev = 0;
        }
        Node(Node *next, Node *prev)
        {
            this->data = 0;
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node *next, Node *prev)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    class Iterator
    {
    private:
        FragmentLinkedList<T> *pList;
        Node *pNode;
        int index;

    public:
        Iterator(FragmentLinkedList<T> *pList = 0, bool begin = true);
        Iterator(int fragmentIndex, FragmentLinkedList<T> *pList = 0, bool begin = true);

        Iterator &operator=(const Iterator &iterator);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        void remove();
        void set(const T &element);

        Iterator &operator++();
        Iterator operator++(int);
    };
};

/*********************************************************************************************
*                                                                                            *
*                                Fragment Linked-list                                        *
*                                                                                            *
**********************************************************************************************/
// Qui uoc index bat dau tu 0 (ZERO)

//-------------------------------------------------------------------------------------------------
// Ham tu them vao

// Ham PRINT
template <class T>
void FragmentLinkedList<T>::printList()
{
    if (this->empty())
    {
        cout << "Danh sach dang trong.\n";
        cout << "----------EMPTY-----------\n";
        cout << "So phan tu trong list la: " << this->size();
        cout << "\n-------------------------------------------------\n";
    }
    else
    {
        FragmentLinkedList<T>::Node *currentPtr = new FragmentLinkedList<T>::Node();
        currentPtr = this->first;

        cout << "Danh sach la: \n";

        while (currentPtr != 0)
        {
            cout << currentPtr->data << " ";
            currentPtr = currentPtr->next;
        }
        cout << "\nSo phan tu trong list la: " << this->size();
        cout << "\nSo phan tu trong 1 fragment la: " << this->fragmentMaxSize;
        cout << "\n-------------------------------------------------\n";
    }
}

// Tra ve danh sach Fragment Pointer duoi dang 1 chuoi
template <class T>
string FragmentLinkedList<T>::toString_FragmentPtr()
{
    // So Fragment
    int numberOfFrag = this->numberOfFrag();

    stringstream ss;
    ss << "Danh sach cac Fragment Ptr la:\n[";

    if (this->size() == 0)
    {
        ss << "]";
        return ss.str();
    }


    for (int i = 0; i < numberOfFrag; i++)
    {
        if (i == numberOfFrag - 1)
            ss << to_string(fragmentPointers[i]->data);
        else
            ss << to_string(fragmentPointers[i]->data) << ", ";
    }

    if (this->size() != 0)
        ss << "]";

    return ss.str();
}

// Sap xep Fragment Pointers
template <class T>
void FragmentLinkedList<T>::reArrangeFragmentPtr()
{
    // tao con tro de chay
    FragmentLinkedList<T>::Node *currentPtr = new FragmentLinkedList<T>::Node();
    currentPtr = this->first;

    // So Fragment
    int numberOfFrag = this->numberOfFrag();

    // Xoa array cu
    delete[] this->fragmentPointers;

    // Tao array moi
    this->fragmentPointers = new Node *[numberOfFrag];

    // Chay vong lap tao array
    // Phan tu Tail phai tro ve node cuoi cung
    if (this->count <= this->fragmentMaxSize)
    {
        this->fragmentPointers[0] = this->first;
        this->fragmentPointers[numberOfFrag - 1] = this->last;
    }
    else
    {
        this->fragmentPointers[0] = this->first;
        this->fragmentPointers[numberOfFrag - 1] = this->last;

        for (int i = 1; i < numberOfFrag - 1; i++)
        {
            // Dich chuyen currentPtr di 1 maxSize de tao ra 1 fragment moi
            int j = 1;
            while (j <= this->fragmentMaxSize)
            {
                j++;
                currentPtr = currentPtr->next;
            }

            fragmentPointers[i] = currentPtr;
        }
    }
}

// Tinh chinh xac so Fragment
template <class T>
int FragmentLinkedList<T>::numberOfFrag()
{
    int total = 0;

    // Chia het
    if (this->count % this->fragmentMaxSize == 0)
    {
        total = this->count / this->fragmentMaxSize + 1;
    }
    else // Du
    {
        total = this->count / this->fragmentMaxSize + 2;
    }

    return total;
}

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

// Them 1 phan tu moi vao cuoi danh sach
template <class T>
void FragmentLinkedList<T>::add(const T &element) // element = data
{
    FragmentLinkedList<T>::Node *newNode = new FragmentLinkedList<T>::Node();
    newNode->data = element;
    newNode->next = NULL;
    newNode->prev = NULL;

    // Danh sach trong tu dau
    if (this->empty())
    {
        this->head->next = this->tail->prev = NULL;

        this->first = newNode;
        this->last = newNode;
        this->count += 1;

        this->head->next = this->first;
        this->tail->prev = this->last;
        //cout << "Danh sach trong, da them phan tu " << element << " lam dau tien.\n";
    }
    else // Them vao cuoi
    {
        this->head->next = this->tail->prev = NULL;

        this->last->next = newNode;
        newNode->prev = this->last;
        this->last = newNode;
        this->count += 1;

        this->head->next = this->first;
        this->tail->prev = this->last;
        //cout << "Da them phan tu " << element << " vao cuoi danh sach.\n";
    }

    this->reArrangeFragmentPtr();
}

// Them 1 phan tu moi vao vi tri index
template <class T>
void FragmentLinkedList<T>::add(int index, const T &element)
{
    FragmentLinkedList<T>::Node *newNode = new FragmentLinkedList<T>::Node();
    newNode->data = element;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (this->empty()) // danh sach empty
    {
        this->head->next = this->tail->prev = NULL;

        this->first = newNode;
        this->last = newNode;
        this->count += 1;

        this->head->next = this->first;
        this->tail->prev = this->last;

        //cout << "Danh sach trong, da them phan tu " << element << " lam dau tien.\n";
    }
    else if (index == this->size() && index != 0) // them o cuoi
    {
        //this->add(e);
        this->head->next = this->tail->prev = NULL;

        this->last->next = newNode;
        newNode->prev = this->last;
        this->last = newNode;
        this->count += 1;

        this->head->next = this->first;
        this->tail->prev = this->last;

        //cout << "Da them phan tu " << element << " vao cuoi danh sach.\n";
    }
    else if (index == 0) // them o dau
    {
        this->head->next = this->tail->prev = NULL;

        this->first->prev = newNode;
        newNode->next = this->first;
        this->first = newNode;
        this->count += 1;

        this->head->next = this->first;
        this->tail->prev = this->last;

        //cout << "Da them phan tu " << element << " vao dau danh sach.\n";
    }
    else
    {
        FragmentLinkedList<T>::Node *currentPtr = new FragmentLinkedList<T>::Node();
        currentPtr = this->first;

        // Di chuyen toi vi tri index
        for (int i = 0; i < index; i++)
        {
            currentPtr = currentPtr->next;
        }

        FragmentLinkedList<T>::Node *currentPtr_Previous = new FragmentLinkedList<T>::Node();
        currentPtr_Previous = currentPtr->prev;

        // co lap de them New Node
        currentPtr_Previous->next = NULL;
        currentPtr->prev = NULL;

        // prev cua New Node
        currentPtr_Previous->next = newNode;
        newNode->prev = currentPtr_Previous;

        // next cua New Node
        currentPtr->prev = newNode;
        newNode->next = currentPtr;

        this->count += 1;
        //cout << "Da them phan tu " << element << " vao vi tri " << index << ".\n";
    }
    this->reArrangeFragmentPtr();
}

// Xoa phan tu tai vi tri index
template <class T>
T FragmentLinkedList<T>::removeAt(int index)
{
    if (index < 0 || index > this->size())
        throw std::out_of_range("The index is out of range!");

    FragmentLinkedList<T>::Node *currentPtr = new FragmentLinkedList<T>::Node();
    currentPtr = this->first;

    // Vi tri dau
    if (index == 0)
    {
        T result;
        this->head->next = this->tail->prev = NULL;

        this->first = this->first->next;

        result = currentPtr->data;
        delete currentPtr;

        this->count -= 1;

        this->head->next = this->first;
        this->tail->prev = this->last;

        //cout << "\nDa xoa phan tu " << currentPtr->data << " tai vi tri dau tien.\n";
        this->reArrangeFragmentPtr();
        return result;
    }
    // Vi tri cuoi
    else if (index == this->size() - 1)
    {
        T result;

        this->head->next = this->tail->prev = NULL;

        currentPtr = this->last;
        this->last->prev->next = NULL;
        this->last = this->last->prev;

        result = currentPtr->data;
        delete currentPtr;

        this->count -= 1;
        this->head->next = this->first;
        this->tail->prev = this->last;

        //cout << "\nDa xoa phan tu " << currentPtr->data << " tai vi tri cuoi cung.\n";
        this->reArrangeFragmentPtr();
        return result;
    }
    // Vi tri khac
    else if (index < this->size() - 1 && index > 0)
    {
        T result;

        int fragIndex = index / this->fragmentMaxSize;

        int elementIndex = index % this->fragmentMaxSize;

        Node *p = this->fragmentPointers[fragIndex];

        while (elementIndex--)
        {
            p = p->next;
        }

        result = p->data;
        p->next->prev = p->prev;
        p->prev->next = p->next;

        delete p;
        this->count -= 1;

        this->reArrangeFragmentPtr();
        return result;
    }

    return 0;
}

// Xoa phan tu co gia tri item
template <class T>
bool FragmentLinkedList<T>::removeItem(const T &item)
{
    // Danh sach empty
    if (this->empty())
        return false;

    // vi tri dau
    if (this->first->data == item)
    {
        // nhieu hon 1 phan tu
        if (this->first->next != NULL)
        {
            this->head->next = this->tail->prev = NULL;

            FragmentLinkedList<T>::Node *currentPtr = new FragmentLinkedList<T>::Node();
            currentPtr = this->first;

            this->first->next->prev = NULL;
            this->first = this->first->next;
            delete currentPtr;

            this->head->next = this->first;
            this->tail->prev = this->last;

            this->count -= 1;
            this->reArrangeFragmentPtr();
            //cout << "\nDa xoa phan tu co gia tri " << item << ".\n";
            return true;
        }
        else // chi co 1 phan tu
        {
            this->head->next = this->tail->prev = NULL;

            delete this->first;
            this->first = this->last = NULL;
            this->head->next = this->first;
            this->tail->prev = this->last;
            this->count -= 1;
            return true;
        }
    }
    else if (this->first->data != item && this->first->next == NULL) // 1 phan tu va ko la item
    {
        return false;
    }

    // Vi tri nam trong danh sach
    // tao con tro current
    FragmentLinkedList<T>::Node *currentPtr = new FragmentLinkedList<T>::Node();
    currentPtr = this->first;
    FragmentLinkedList<T>::Node *preNode = new FragmentLinkedList<T>::Node();

    // tim kiem gia tri item trong danh sach
    while (currentPtr->data != item && currentPtr->next != NULL)
    {
        preNode = currentPtr;
        currentPtr = currentPtr->next;
    }

    if (currentPtr->data == item)
    {
        this->head->next = this->tail->prev = NULL;

        preNode->next = preNode->next->next;

        if (preNode->next != NULL)
        {
            preNode->next->prev = preNode;
        }
        else
            this->last = preNode;

        delete currentPtr;

        this->head->next = this->first;
        this->tail->prev = this->last;

        this->count -= 1;
        //cout << "\nDa xoa phan tu co gia tri " << item << ".\n";
        this->reArrangeFragmentPtr();

        return true;
    }
    else
        return false;
}

// Kiem tra xem danh sach co rong hay ko?
template <class T>
bool FragmentLinkedList<T>::empty()
{
    if (/*this->first == NULL && this->last == NULL && */ this->count == 0)
    {
        return true;
    }

    return false;
}

// Kich thuoc danh sach
template <class T>
int FragmentLinkedList<T>::size()
{
    return this->count;
}

// Xoa toan bo cac phan tu
template <class T>
void FragmentLinkedList<T>::clear()
{
    while (!this->empty())
        this->removeAt(0); // goi ham removeAt xoa phan tu dau tien

    this->first = this->last = NULL;
    this->count = 0;
    this->reArrangeFragmentPtr();
}

// Tra ve phan tu tai vi tri index
template <class T>
T FragmentLinkedList<T>::get(int index)
{
    if (index < 0 || index > this->size() - 1)
        throw std::out_of_range("The index is out of range!");

    // tao con tro de chay
    FragmentLinkedList<T>::Node *currentPtr = new FragmentLinkedList<T>::Node();
    currentPtr = this->first;

    for (int i = 0; i != index; i++)
    {
        currentPtr = currentPtr->next;
    }

    return currentPtr->data;
}

// Thay the data bang gia tri element tai vi tri index
template <class T>
void FragmentLinkedList<T>::set(int index, const T &element)
{
    if (index > this->size() || index < 0)
    {
        throw std::out_of_range("The index is out of range!");
    }

    // Tao con tro de chay
    FragmentLinkedList<T>::Node *currentPtr = new FragmentLinkedList<T>::Node();
    currentPtr = this->first;

    // currentPtr da o vi tri 1
    for (int i = 1; i <= index; i++)
    {
        currentPtr = currentPtr->next;
    }

    currentPtr->data = element;

    //cout << "\nDa thay doi thanh cong.\n";
}

// Tra ve vi tri cua phan tu mang gia tri item
template <class T>
int FragmentLinkedList<T>::indexOf(const T &item)
{
    // index bat dau tu 0
    int result = -1;
    bool found = false;

    // tao con tro chay
    FragmentLinkedList<T>::Node *currentPtr = new FragmentLinkedList<T>::Node();
    currentPtr = this->first;

    while (currentPtr != NULL)
    {
        result += 1;
        if (currentPtr->data != item)
        {
            currentPtr = currentPtr->next;
            found = false;
        }
        else // GOTCHA
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        return result;
    }
    else
        return -1;
}

// Kiem tra phan tu co gia tri item xuat hien trong danh sach ko
template <class T>
bool FragmentLinkedList<T>::contains(const T &item)
{
    if (this->first == NULL && this->last == NULL)
    {
        return false;
    }
    else
    {
        // tao con tro de chay
        FragmentLinkedList<T>::Node *currentPtr = new FragmentLinkedList<T>::Node();
        currentPtr = this->first;

        while (currentPtr != NULL && currentPtr->data != item)
        {
            currentPtr = currentPtr->next;
        }

        if (currentPtr != NULL)
            return true;

        if (currentPtr == NULL)
            return false;
    }

    return false;
}

// Tra ve danh sach node duoi dang 1 chuoi
template <class T>
string FragmentLinkedList<T>::toString()
{
    stringstream ss;
    ss << "[";

    if (this->count == 0)
        ss << "]";

    Node *ptr = this->fragmentPointers[0];
    while (ptr != NULL)
    {
        // Phan tu cuoi cung
        if (ptr->next == NULL)
        {
            ss << ptr->data;
        }
        else
            ss << ptr->data << ", ";

        ptr = ptr->next;
    }

    if (this->count != 0)
        ss << "]";

    return ss.str();
}


/*********************************************************************************************
*                                                                                            *
*                                       ITERATOR                                             *
*                                                                                            *
*********************************************************************************************/

// Constructor #1
template <class T>
FragmentLinkedList<T>::Iterator::Iterator(FragmentLinkedList<T> *pList, bool begin)
{
    this->pList = pList;

    // Node dau tien
    if (begin)
    {
        if (pList == NULL)
        {
            this->pNode = NULL;
            this->index = -1;
        }
        else
        {
            this->pNode = pList->first;
            this->index = 0;
        }
    }
    else if (!begin)
    {
        if (pList != NULL)
        {
            this->pNode = pList->last;
            this->index = this->pList->size();
        }
        else
        {
            this->pNode = NULL;
            this->index = 0;
        }
    }
}

// Constructor #2
template <class T>
FragmentLinkedList<T>::Iterator::Iterator(int fragmentIndex, FragmentLinkedList<T> *pList, bool begin)
{
    this->pList = pList;

    FragmentLinkedList<T>::Node *currentPtr = new FragmentLinkedList<T>::Node();
    currentPtr = this->pList->first;

    if (pList == NULL)
    {
        this->pNode = NULL;
        this->index = -1;
    }
    else if (begin)
    {
        int Frag = this->pList->numberOfFrag();
        if (fragmentIndex >= Frag - 1)
            throw std::out_of_range("Segmentation fault!");

        // Vi tri dau (Default)
        if (fragmentIndex == 0)
        {
            this->pNode = this->pList->first;
            this->index = 0;
        }
        // Vi tri trong List
        else if (fragmentIndex > 0)
        {
            int a = fragmentIndex * this->pList->fragmentMaxSize;
            int i = 0;

            while (i < a)
            {
                currentPtr = currentPtr->next;
                i++;
            }

            this->pNode = currentPtr;
            this->index = fragmentIndex * this->pList->fragmentMaxSize;
        }
    }
    else // begin == false (end)
    {
        // Index cua fragment cuoi cung
        int lastFrag = this->pList->size() / this->pList->fragmentMaxSize;

        // Frag cuoi cung
        if (fragmentIndex == -1 || fragmentIndex >= lastFrag)
        {
            this->pNode = this->pList->last->next;
            this->index = this->pList->size();
        }
        // Frag dau tien
        else if (fragmentIndex == 0)
        {
            int first = this->pList->fragmentMaxSize - 1;
            int i = 0;

            while (i < first)
            {
                currentPtr = currentPtr->next;
                i++;
            }

            this->index = (fragmentIndex + 1) * this->pList->fragmentMaxSize;
            this->pNode = currentPtr->next;
        }
        // Frag o giua
        else if (fragmentIndex > 0 && fragmentIndex < lastFrag)
        {
            int middle = (fragmentIndex + 1) * this->pList->fragmentMaxSize - 1;
            int i = 0;

            while (i < middle)
            {
                currentPtr = currentPtr->next;
                i++;
            }

            this->index = (fragmentIndex + 1) * this->pList->fragmentMaxSize;
            this->pNode = currentPtr->next;
        }
    }
}

// Begin   (Default 0)
template <class T>
typename FragmentLinkedList<T>::Iterator
FragmentLinkedList<T>::begin(int index)
{
    FragmentLinkedList<T>::Iterator myIterator = FragmentLinkedList<T>::Iterator(index, this, true);
    return myIterator;
}

// End     (Default -1)
template <class T>
typename FragmentLinkedList<T>::Iterator
FragmentLinkedList<T>::end(int index)
{
    FragmentLinkedList<T>::Iterator myIterator = FragmentLinkedList<T>::Iterator(index, this, false);
    return myIterator;
}

// Remove
template <class T>
void FragmentLinkedList<T>::Iterator::remove()
{
    if (this->pNode == NULL)
        throw std::out_of_range("Segmentation fault!");

    // Vi tri dau tien
    if (/*this->pNode == this->pList->first ||*/ this->index == 0)
    {
        this->pList->removeAt(0);
        this->pNode = this->pList->head;
        this->index = -1;
    }
    // Vi tri trong list
    else if (this->pNode->prev != NULL)
    {
        //Node *currentPtr = this->pNode;
        this->pNode = this->pNode->prev;

        this->pList->removeAt(this->index);
        this->index -= 1;
    }
}

// Set
template <class T>
void FragmentLinkedList<T>::Iterator::set(const T &element)
{
    this->pNode->data = element;
}

// Overload operator =
template <class T>
typename FragmentLinkedList<T>::Iterator
    &
    FragmentLinkedList<T>::Iterator::operator=(const Iterator &iterator)
{
    this->pNode = iterator.pNode;
    this->pList = iterator.pList;
    this->index = iterator.index;
    return *this;
}

// Overload operator !=
template <class T>
bool FragmentLinkedList<T>::Iterator::operator!=(const Iterator &iterator)
{
    if (this->pNode != iterator.pNode || this->index != iterator.index)
        return true;
    else
        return false;
}

// Overload operator *
template <class T>
T &FragmentLinkedList<T>::Iterator::operator*()
{
    if (this->pNode == NULL)
        throw std::out_of_range("Segmentation fault!");

    return this->pNode->data;
}

// Overload operator prefix ++a
template <class T>
typename FragmentLinkedList<T>::Iterator
    &
    FragmentLinkedList<T>::Iterator::operator++()
{
    if (this->pNode == NULL && index > this->pList->size())
        throw std::out_of_range("Segmentation fault!");

    this->pNode = this->pNode->next;
    this->index += 1;
    return *this;
}

// Overload operator postfix a++
template <class T>
typename FragmentLinkedList<T>::Iterator
FragmentLinkedList<T>::Iterator::operator++(int)
{
    if (this->pNode == NULL && index > this->pList->size())
        throw std::out_of_range("Segmentation fault!");

    FragmentLinkedList<T>::Iterator result = *this;
    ++(*this);
    return result;
}

#endif
// END: STUDENT ANSWER
//----------------------------------------------------------------------------------------------------------------


int main()
{
    //Test 1
    FragmentLinkedList<int> fList(4);
    for (int idx = 0 ; idx <= 23; idx += 1)
        fList.add(idx);

    fList.printList();
    cout << fList.toString_FragmentPtr() << endl;

    fList.removeAt(23);

    fList.printList();
    cout << fList.toString_FragmentPtr() << endl;

    FragmentLinkedList<int>::Iterator it = fList.begin();
    while(!fList.empty())
    {
        it.remove();
        it++;
    }

    fList.printList();
    cout << fList.toString_FragmentPtr() << endl;

    return 0;
}
