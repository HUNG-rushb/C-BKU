#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>

using namespace std;

template <class T>
class SLinkedList
{
public:
    class Iterator; //forward declaration
    class Node;     //forward declaration

protected:
    Node *head;
    Node *tail;
    int count = 0;

public:
    SLinkedList() : head(NULL), tail(NULL), count(0){};
    ~SLinkedList();
    void add(const T &e);
    void add(int index, const T &e);
    T removeAt(int index);
    bool removeItem(const T &removeItem);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
    string toString();

    // ham tu them---------------------------
    void printList();
    //---------------------------------------

    SLinkedList(const SLinkedList &list)
    {
        this->count = 0;
        this->head = NULL;
        this->tail = NULL;
    }

    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
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

        Node(Node *next)
        {
            this->next = next;
        }

        Node(T data, Node *next = NULL)
        {
            this->data = data;
            this->next = next;
        }
    };

    class Iterator
    {
    private:
        SLinkedList<T> *pList;
        Node *current;
        int index;

    public:
        Iterator(SLinkedList<T> *pList = NULL, bool begin = true);

        Iterator &operator=(const Iterator &iterator);
        void remove();
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        Iterator &operator++();
        Iterator operator++(int);
    };
};

/*********************************************************************************************
*                                                                                            *
*                                       SLinkedList                                          *
*                                                                                            *
**********************************************************************************************/

// Print the list
template <class T>
void SLinkedList<T>::printList()
{
    if (this->head == NULL && this->tail == NULL)
    {
        cout << "Danh sach dang trong.\n";
        return;
    }

    Node *currentPtr = new Node();
    currentPtr = this->head;

    cout << "Danh sach la: \n";

    while (currentPtr != NULL)
    {
        cout << currentPtr->data << " ";
        currentPtr = currentPtr->next;
    }
    cout << "\nSo phan tu trong list la: " << this->size();
    cout << "\n----------------------------------------------\n";
}

// Destructor
template <class T>
SLinkedList<T>::~SLinkedList()
{
}

/* Insert an element into the end of the list. */
template <class T>
void SLinkedList<T>::add(const T &e)
{
    // Empty list
    if (this->head == NULL && this->tail == NULL)
    {
        Node *newNode = new Node();
        newNode->data = e;
        newNode->next = NULL;

        this->head = newNode;
        this->tail = newNode;
    }
    else // insert at back
    {
        Node *newNode = new Node();
        newNode->data = e;
        newNode->next = NULL;

        this->tail->next = newNode;
        this->tail = newNode;
    }

    this->count += 1;
}

/* Insert an element into the list at given index. */
template <class T>
void SLinkedList<T>::add(int index, const T &e)
{
    Node *currentPtr = new Node;
    currentPtr = this->head;

    // danh sach trong
    if (this->head == NULL && this->tail == NULL)
    {
        Node *newNode = new Node;
        newNode->data = e;
        newNode->next = NULL;
        this->head = newNode;
        this->tail = newNode;
    }
    else if (index == 0) // them o dau
    {
        Node *newNode = new Node;
        newNode->data = e;

        newNode->next = this->head;
        this->head = newNode;
    }
    else
    {
        Node *newNode = new Node;
        newNode->data = e;
        newNode->next = NULL;

        int x = 0;

        // chay toi index - 1
        // index bat dau tu 0
        for (int i = 0; i < index; i++)
        {
            x += 1;
            currentPtr = currentPtr->next;
        }

        newNode->next = currentPtr->next;
        currentPtr->next = newNode;
    }

    this->count += 1;
}

/* Return the length (size) of list */
template <class T>
int SLinkedList<T>::size()
{
    return this->count;
}

/* Give the data of the element at given index in the list. */
template <class T>
T SLinkedList<T>::get(int index)
{
    // invalid index
    if (index < 0 || index > this->size())
        throw std::out_of_range("The index is out of range !.");

    Node *currentPtr = new Node;
    currentPtr = this->head;

    // loop to index
    for (int i = 1; i <= index; i++)
    {
        currentPtr = currentPtr->next;
    }

    return currentPtr->data;
}

/* Assign new value for element at given index in the list */
template <class T>
void SLinkedList<T>::set(int index, const T &e)
{
    if (index < 0 || index > this->size())
        throw std::out_of_range("The index is out of range !.");

    Node *currentPtr = new Node;
    currentPtr = this->head;

    for (int i = 0; i < index; i++)
    {
        currentPtr = currentPtr->next;
    }

    currentPtr->data = e;
}

/* Check if the list is empty or not. */
template <class T>
bool SLinkedList<T>::empty()
{
    if (this->size() == 0 && this->head == NULL && this->tail == NULL)
        return true;

    return false;
}

/* Return the first index wheter item appears in list, otherwise return -1 */
template <class T>
int SLinkedList<T>::indexOf(const T &item)
{
    int result = -1;
    bool found = false;

    Node *currentPtr = new Node;
    currentPtr = this->head;

    for (int i = 0; i <= this->size(); i++)
    {
        result += 1;

        if (currentPtr->data != item)
        {
            currentPtr = currentPtr->next;
            found = false;
        }
        else
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

/* Check if item appears in the list */
template <class T>
bool SLinkedList<T>::contains(const T &item)
{
    if (this->size() == 0)
    {
        return false;
    }
    else
    {
        Node *currentPtr = new Node;
        currentPtr = this->head;

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

/* Remove element at index and return removed value */
template <class T>
T SLinkedList<T>::removeAt(int index)
{
    T result;

    Node *currentPtr = new Node;
    currentPtr = this->head;

    Node *temp = new Node;

    // Chi co 1 phan tu
    if (this->size() == 1)
    {
        this->head = this->tail = NULL;
        this->count = 0;

        result = currentPtr->data;
        delete currentPtr;

        return result;
    }
    // Vi tri dau
    else if (index == 0 && this->size() > 1)
    {
        this->head = this->head->next;
        this->count -= 1;

        result = currentPtr->data;
        delete currentPtr;

        return result;
    }
    // Nhung vi tri khac
    else
    {
        int x = 0;

        // Phan tu dung truoc 1 don vi
        while (x != index - 1)
        {
            currentPtr = currentPtr->next;
            x++;
        }

        temp = currentPtr->next;
        currentPtr->next = currentPtr->next->next;
        this->count -= 1;

        result = temp->data;
        delete temp;

        return result;
    }
}

/* Remove the first apperance of item in list and return true, otherwise return false */ //*****************************************************************************8
template <class T>
bool SLinkedList<T>::removeItem(const T &item)
{
    // Danh sach empty
    if (this->count == 0)
        return false;

    // vi tri dau
    if (this->head->data == item)
    {
        // nhieu hon 1 phan tu
        if (this->head->next != NULL)
        {
            this->head = this->head->next;
            this->count -= 1;

            return true;
        }
        else // chi co 1 phan tu
        {
            this->head = this->tail = NULL;
            return true;
        }
    }
    else if (this->head->data != item && this->head->next == NULL) // 1 phan tu va ko la item
    {
        return false;
    }

    // tao con tro current
    Node *currentPtr = new Node;
    currentPtr = this->head;

    Node *preNode = new Node;

    // tim kiem gia tri item trong danh sach
    while (currentPtr->data != item && currentPtr->next != NULL)
    {
        preNode = currentPtr;
        currentPtr = currentPtr->next;
    }

    if (currentPtr->data == item)
    {
        preNode->next = currentPtr->next;

        if (currentPtr == NULL)
            this->tail = preNode;

        delete currentPtr;
        this->count -= 1;

        return true;
    }
    else
        return false;
}

/* Remove all elements in list */
template <class T>
void SLinkedList<T>::clear()
{
    while (this->head != NULL)
        this->removeAt(0);

    this->count = 0;
}

/*********************************************************************************************
*                                                                                            *
*                                       ITERATOR                                             *
*                                                                                            *
**********************************************************************************************/

// Constructor
template <class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T> *pList, bool begin)
{
    /*
        Constructor of iterator
        * Set pList to pList
        *
        * begin = true:
        * * Set current (index = 0) to pList's head if pList is not NULL
        * * Otherwise set to NULL (index = -1)
        *
        * begin = false:
        * * Always set current to NULL
        * * Set index to pList's size if pList is not NULL, otherwise 0
    */
    this->pList = pList;

    // BEGIN (true)
    if (begin == true)
    {
        // Danh sach khong NULL
        // neu pList dang NULL thi ta se ko goi ham size() hay count dc
        // nen code nhu ben duoi
        if (!this->pList == 0)
        {
            this->current = this->pList->head;
            this->index = 0;
        }
        else // Danh sach NULL
        {
            this->current = NULL;
            this->index = -1;
        }
    }
    else // END (false)
    {
        if (!this->pList == 0)
        {
            this->current = NULL;
            this->index = this->pList->size();
        }
        else
        {
            this->current = NULL;
            this->index = 0;
        }
    }
}

// Remove
template <class T>
void SLinkedList<T>::Iterator::remove()
{
    /*
        Remove a node which is pointed by current
        * After remove current points to the previous node of this position (or node with index - 1)
        * If remove at front, current points to previous "node" of head (current = NULL, index = -1)
        * Exception: throw std::out_of_range("Segmentation fault!") if remove when current is NULL
    */

    // current == NULL
    if (this->current == NULL)
        throw std::out_of_range("Segmentation fault!");
    // remove at front
    else if (this->current == this->pList->head)
    {
        this->pList->removeAt(0);
        this->current = NULL;
    }
    // remove
    else
    {
        // tim vi tri cua current
        int countIndex = 0;
        Node *temp = this->pList->head;

        while (temp != this->current)
        {
            countIndex += 1;
            temp = temp->next;
        }
        // countIndex va temp deu dang o tai current

        int x = 0;
        Node *temp_2 = this->pList->head;
        // Phan tu dung truoc 1 don vi
        while (x != countIndex - 1)
        {
            temp_2 = temp_2->next;
            x++;
        }

        temp_2->next = temp->next;
        this->current = temp_2;
        delete temp;
        this->pList->count -= 1;
    }
}

// Set
template <class T>
void SLinkedList<T>::Iterator::set(const T &e)
{
    /*
        Set the new value for current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
    this->current->data = e;
}

// Operator *
template <class T>
T &SLinkedList<T>::Iterator::operator*()
{
    /*
        Get data stored in current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
    return this->current->data;
}

// Operator =
template <class T>
typename SLinkedList<T>::Iterator
    &
    SLinkedList<T>::Iterator::operator=(const Iterator &iterator)
{
    /*
        Assignment operator
        * Set this current, index, pList to iterator corresponding elements.
    */
    this->current = iterator.current;
    this->index = iterator.index;
    this->pList = iterator.pList;
    return *this;
}

// Operator !=
template <class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator &iterator)
{
    //Returns true if two iterators points the same node and index
    if (this->current != iterator.current)
        return true;
    else
        return false;
}

// Prefix ++a overload
template <class T>
typename SLinkedList<T>::Iterator
    &
    SLinkedList<T>::Iterator::operator++()
{
    /*
        Prefix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */

    this->current = this->current->next;
    return *this;
}

// Postfix a++ overload
template <class T>
typename SLinkedList<T>::Iterator
SLinkedList<T>::Iterator::operator++(int)
{
    /*
        Postfix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
    SLinkedList<T>::Iterator result = *this;
    ++(*this);
    return result;
}

//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------
