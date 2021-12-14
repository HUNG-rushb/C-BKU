#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class K, class D, int M> // K: key, D: data, M: degree of BTree
class BTree
{
    /// Convention: Left sub-tree < Root's key <= Right sub-tree

public:
    class Entry;
    class Node;

private:
    Node *root;

public:
    BTree() : root(0){};
    ~BTree() {}

    ///////////////////////////////////////////////////
    ///             CLASS `Entry`                   ///
    ///////////////////////////////////////////////////
public:
    class Entry
    {
    private:
        K key;
        D data;
        Node *rightPtr;

        friend class BTree<K, D, M>;

    public:
        Entry(K key = K{}, D value = D{}) : key(key), data(value), rightPtr(0) {}
        ~Entry() {}

        string toString()
        {
            stringstream ss;
            ss << "<"
               << this->key << ","
               << this->data
               << ">";
            return ss.str();
        }
    };

    ///////////////////////////////////////////////////
    ///             CLASS `Node`                    ///
    ///////////////////////////////////////////////////
public:
    class Node
    {
    private:
        Node *firstPtr;
        int numEntries;
        Entry entries[M - 1];

        friend class BTree<K, D, M>;

    public:
        Node() : firstPtr(0), numEntries(0){};
        ~Node() {}

        // Node is full or not?
        bool isFull()
        {
            return (numEntries >= M - 1);
        }

        string toString()
        {
            stringstream ss;

            ss << "[(" << this->numEntries << ")";

            for (int idx = 0; idx < this->numEntries; idx++)
            {
                ss << this->entries[idx].toString();
            }

            ss << "]";
            return ss.str();
        }
    };

    /////////////////////////////////////////////////////////////
    ///         CLASS `BTree`: method run sample test         ///
    /////////////////////////////////////////////////////////////

    // Print Node List
    void testPrintNode(K *keys, D *data, int size)
    {
        Node node;

        for (int idx = 0; idx < size; idx++)
        {
            node.entries[idx].key = keys[idx];
            node.entries[idx].data = data[idx];
        }

        node.numEntries = size;

        cout << node.toString() << endl;
    }

    // Print Pre-order
    string toStringPreOrder_helper(Node *current_node)
    {
        stringstream ss;

        if (current_node != NULL)
        {
            ss << current_node->toString() << " ";

            ss << toStringPreOrder_helper(current_node->firstPtr);

            for (int i = 0; i < current_node->numEntries; i++)
            {
                ss << toStringPreOrder_helper(current_node->entries[i].rightPtr);
            }
        }
        return ss.str();
    }

    string toStringPreOrder()
    {
        return toStringPreOrder_helper(this->root);
    }

    // -----------------------------------------------------------------------------
    // Search
    bool search_helper(Node *current_node, const K &key, Node *&outNodePtr, int &outEntryIdx)
    {
        bool found = false;

        if (key < current_node->entries[0].key)
        {
            if (current_node->firstPtr != NULL)
                return search_helper(current_node->firstPtr, key, outNodePtr, outEntryIdx);
            else
                return false;
        }
        else
        {
            outEntryIdx = current_node->numEntries - 1;

            while (key < current_node->entries[outEntryIdx].key)
            {

                outEntryIdx -= 1;
            }

            if (key == current_node->entries[outEntryIdx].key)
            {
                outNodePtr = current_node;
                found = true;
            }
            else if (key > current_node->entries[outEntryIdx].key && current_node->entries[outEntryIdx].rightPtr != NULL)
            {
                return search_helper(current_node->entries[outEntryIdx].rightPtr, key, outNodePtr, outEntryIdx);
            }
        }
        return found;
    }

    bool search(const K &key, Node *&outNodePtr, int &outEntryIdx)
    {
        return search_helper(this->root, key, outNodePtr, outEntryIdx);
    }

    // ------------------------------------------------------------------------------
    // Insert
    void insertEntry(Node *pNode, int entryIdx, const Entry &newEntry)
    {
        for (int i = pNode->numEntries; i > entryIdx; --i)
        {
            pNode->entries[i] = pNode->entries[i - 1];
        }

        pNode->entries[entryIdx] = newEntry;
    }

    void splitNode(Node *pNode, int entryIdx, Entry &upEntry)
    {
        int minEntries = (M - 1) / 2;
        Node *rightPtr = new Node();

        int fromNdx = 0;

        if (entryIdx <= minEntries)
        {
            fromNdx = minEntries + 1;
        }
        else
        {
            fromNdx = minEntries + 2;
        }

        int toNdx = 1;

        rightPtr->numEntries = pNode->numEntries - fromNdx + 1;

        while (fromNdx <= pNode->numEntries)
        {
            rightPtr->entries[toNdx - 1] = pNode->entries[fromNdx - 1];
            fromNdx += 1;
            toNdx += 1;
        }

        pNode->numEntries -= rightPtr->numEntries;

        if (entryIdx <= minEntries)
        {
            insertEntry(pNode, entryIdx, upEntry);
        }
        else
        {
            insertEntry(rightPtr, entryIdx - minEntries - 1, upEntry);
            pNode->numEntries -= 1;
            rightPtr->numEntries += 1;
        }

        int medianNdx = minEntries + 1;

        upEntry.data = pNode->entries[medianNdx - 1].data;
        upEntry.rightPtr = rightPtr;
        rightPtr->firstPtr = pNode->entries[medianNdx - 1].rightPtr;

        return;
    }

    int searchNode(Node *nodePtr, K key)
    {
        int walker = 0;

        if (key >= nodePtr->entries[0].key)
        {
            walker = nodePtr->numEntries;

            while (key < nodePtr->entries[walker - 1].key)
            {
                --walker;
            }
        }

        return walker;
    }

    bool insertNode(Node *&root, const K &key, const D &data, Entry &upEntry)
    {
        bool taller = false;

        if (root == NULL)
        {
            upEntry.data = data;
            upEntry.key = key;
            upEntry.rightPtr = NULL;
            taller = true;
        }
        else
        {
            int entryNdx = searchNode(root, key);
            Node *subTree = NULL;

            if (entryNdx > 0)
            {
                subTree = root->entries[entryNdx - 1].rightPtr;
            }
            else
            {
                subTree = root->firstPtr;
            }

            taller = insertNode(subTree, key, data, upEntry);

            if (taller)
            {
                // node full
                if (root->isFull())
                {
                    splitNode(root, entryNdx, upEntry);
                    taller = true;
                }
                else
                {
                    insertEntry(root, entryNdx, upEntry);
                    taller = false;
                    root->numEntries += 1;
                }
            }
        }

        return taller;
    }

    void insert_helper(Node *&root, const K &key, const D &data)
    {
        Entry upEntry;
        bool taller = insertNode(root, key, data, upEntry);

        if (taller)
        {
            Node *newPtr = new Node;
            newPtr->entries[0] = upEntry;
            newPtr->firstPtr = root;
            newPtr->numEntries = 1;
            root = newPtr;
        }
    }

    void insert(const K &key, const D &data)
    {
        insert_helper(this->root, key, data);
    }
};

int main()
{
    //    int keys[] = {3, 5, 7};
    //    int data[] = {33, 55, 77};
    //    int size = sizeof(keys) / sizeof(int);
    //
    //    BTree<int, int, 5>().testPrintNode(keys, data, size);

    //    BTree<int, int, 5> bTree;
    //    int keys[] = {78};
    //    int size = sizeof(keys) / sizeof(int);
    //
    //    for (int idx = 0; idx < size; idx++) {
    //        bTree.insert(keys[idx], idx);
    //    }
    //
    //    cout << bTree.toStringPreOrder() << endl;

    //    BTree<int, int, 3> bTree;
    //    int keys[] = {9, 21, 14};
    //    int size = sizeof(keys) / sizeof(int);
    //
    //    for (int idx = 0; idx < size; idx++) {
    //        bTree.insert(keys[idx], idx);
    //    }
    //
    //    cout << bTree.toStringPreOrder() << endl;

    //int keys[] = {78, 21, 14};
    //int size = sizeof(keys) / sizeof(int);
    //
    //BTree<int, int, 5> bTree;
    //for (int idx = 0; idx < size; idx++) {
    //    bTree.insert(keys[idx], idx + 5);
    //}
    //
    //BTree<int, int, 5>::Node* outNode;
    //int outEntryIdx;
    //if (bTree.search(11, outNode, outEntryIdx)) {
    //    cout << "FOUND" << endl;
    //    cout << outNode->toString() << endl;
    //    cout << "Index: " << outEntryIdx;
    //}
    //else {
    //    cout << "NOT FOUND";
    //}

    int keys[] = {78, 21, 14};
    int size = sizeof(keys) / sizeof(int);

    BTree<int, int, 5> bTree;
    for (int idx = 0; idx < size; idx++)
    {
        bTree.insert(keys[idx], idx + 5);
    }

    BTree<int, int, 5>::Node *outNode;
    int outEntryIdx;
    if (bTree.search(21, outNode, outEntryIdx))
    {
        cout << "FOUND" << endl;
        cout << outNode->toString() << endl;
        cout << "Index: " << outEntryIdx;
    }
    else
    {
        cout << "NOT FOUND";
    }

    return 0;
}
