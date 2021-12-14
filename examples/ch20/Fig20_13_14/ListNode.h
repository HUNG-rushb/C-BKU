// Fig. 20.3: ListNode.h
// Template ListNode class definition.
#ifndef LISTNODE_H
#define LISTNODE_H

// forward declaration of class List required to announce that class
// List exists so it can be used in the friend declaration at line 13
template <typename NODETYPE>
class List;

template <typename NODETYPE>
class ListNode
{
   friend class List<NODETYPE>; // make List a friend

public:
   ListNode(const NODETYPE &); // constructor
   NODETYPE getData() const;   // return data in node
private:
   NODETYPE data;               // data
   ListNode<NODETYPE> *nextPtr; // next node in list
};                              // end class ListNode

// constructor
template <typename NODETYPE>
ListNode<NODETYPE>::ListNode(const NODETYPE &info)
    : data(info), nextPtr(0)
{
   // empty body
} // end ListNode constructor

// return copy of data in node
template <typename NODETYPE>
NODETYPE ListNode<NODETYPE>::getData() const
{
   return data;
} // end function getData

#endif
