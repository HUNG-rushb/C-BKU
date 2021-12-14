#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

template <class T>
class Heap
{
protected:
    T *elements;
    int capacity;
    int count;

public:
    Heap()
    {
        this->capacity = 10;
        this->count = 0;
        this->elements = new T[capacity];
    }
    ~Heap()
    {
        delete[] elements;
    }
    //---------------------
    void push(T item);
    // --------------------
    int getItem(T item);
    void remove(T item);
    void clear();
    //---------------------
    bool isEmpty();
    bool contains(T item);
    T peek();
    bool pop();
    int size();

    void printHeap()
    {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]";
    }

private:
    void ensureCapacity(int minCapacity);
    void reheapUp(int position);
    void reheapDown(int position);
};

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Global function reheap
void reheap_Down(int maxHeap[], int numberOfElements, int index)
{
    int left_child = index * 2 + 1;
    int right_child = index * 2 + 2;
    int large;

    if (left_child < numberOfElements)
    {
        if (right_child < numberOfElements && maxHeap[right_child] > maxHeap[left_child])
            large = right_child;
        else
            large = left_child;

        if (maxHeap[large] > maxHeap[index])
        {
            swap(maxHeap[large], maxHeap[index]);
            reheap_Down(maxHeap, numberOfElements, large);
        }
    }
}

void reheap_Up(int maxHeap[], int numberOfElements, int index)
{
    int parent = (index - 1) / 2;

    if (index > 0 && index < numberOfElements)
    {
        if (maxHeap[index] > maxHeap[parent])
        {
            swap(maxHeap[index], maxHeap[parent]);
            reheap_Up(maxHeap, numberOfElements, parent);
        }
    }
}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
template <class T>
void Heap<T>::push(T item)
{
    if (this->count >= capacity)
        ensureCapacity(this->count);

    elements[this->count] = item;
    reheapUp(this->count);
    this->count++;
}

template <class T>
void Heap<T>::ensureCapacity(int minCapacity)
{
    T *ptr = elements;
    elements = new T[capacity + minCapacity];

    for (int i = 0; i < this->count; i++)
    {
        elements[i] = ptr[i];
    }
}

template <class T>
void Heap<T>::reheapDown(int position)
{
    int left_child = position * 2 + 1;
    int right_child = position * 2 + 2;
    int large;

    if (left_child < this->count)
    {
        if (right_child < this->count && elements[right_child] > elements[left_child])
            large = right_child;
        else
            large = left_child;

        if (elements[large] > elements[position])
        {
            swap(elements[large], elements[position]);
            reheapDown(large);
        }
    }
}

template <class T>
void Heap<T>::reheapUp(int position)
{
    int parent = (position - 1) / 2;

    if (position > 0 && position <= this->count)
    {
        if (elements[position] > elements[parent])
        {
            swap(elements[position], elements[parent]);
            reheapUp(parent);
        }
    }
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
template <class T>
int Heap<T>::getItem(T item)
{
    // TODO: return the index of item in heap
    for (int i = 0; i < this->count; i++)
    {
        if (this->elements[i] == item)
        {
            return i;
        }
    }
    return -1;
}

template <class T>
void Heap<T>::remove(T item)
{
    // TODO: remove the element with value equal to item
    int i = this->getItem(item);

    if (i != -1)
    {
        this->elements[i] = this->elements[this->count - 1];
        this->count--;
        this->reheapDown(i);
    }

    return;
}

template <class T>
void Heap<T>::clear()
{
    // TODO: delete all elements in heap
    delete[] this->elements;
    this->count = 0;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
template <class T>
int Heap<T>::size()
{
    return this->count;
}

template <class T>
bool Heap<T>::isEmpty()
{
    if (this->size() == 0)
        return true;

    return false;
}

template <class T>
T Heap<T>::peek()
{
    if (this->size() > 0)
        return elements[0];

    return -1;
}

template <class T>
bool Heap<T>::contains(T item)
{
    for (int i = 0; i < this->size(); i++)
    {
        if (elements[i] == item)
            return true;
    }

    return false;
}

template <class T>
bool Heap<T>::pop()
{
    if (this->size() > 0)
    {
        elements[0] = elements[this->count - 1];
        this->count--;
        reheapDown(0);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
int main()
{
    Heap<int> maxHeap;
    int arr[] = {13, 19, 20, 7, 15, 12, 16, 10, 8, 9, 3, 6, 18, 2, 14, 1, 17, 4, 11, 5};
    for (int i = 0; i < 20; ++i)
        maxHeap.push(arr[i]);
    //maxHeap.clear();
    maxHeap.printHeap();

    return 0;
}
