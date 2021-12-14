#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class T>
class BinarySearchTree
{
public:
    class Node;

private:
    Node *root;

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    class Node
    {
    private:
        T value;
        Node *pLeft, *pRight;
        friend class BinarySearchTree<T>;

    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    //--------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------
    // STUDENT ANSWER BEGIN

    void add(Node *a, T value)
    {
        // Empty tree
        if (a == NULL)
        {
            Node *b = new Node(value);
            this->root = b;
        }
        else if (a->pRight == NULL && value > a->value)
        {
            Node *b = new Node(value);
            a->pRight = b;
        }
        else if (a->pLeft == NULL && value <= a->value)
        {
            Node *b = new Node(value);
            a->pLeft = b;
        }
        else if (value < a->value)
            this->add(a->pLeft, value);
        else
            this->add(a->pRight, value);
    }

    void add(T value)
    {
        //TODO
        this->add(this->root, value);
    }

    //  Method find(i) to check whether value i is in the tree or not.
    bool find(T i)
    {
        // TODO: return true if value i is in the tree; otherwise, return false.
        return find_helper(this->root, i);
    }

    bool find_helper(Node *node, T value)
    {
        if (node == NULL)
            return false;

        if (node->value == value)
            return true;

        /* then recur on left sutree */
        bool found_left = find_helper(node->pLeft, value);
        // node found, no need to look further
        if (found_left)
            return true;

        /* node is not found in left, 
    	so recur on right subtree */
        bool found_right = find_helper(node->pRight, value);

        return found_right;
    }

    // Method sum(l,r) to calculate sum of all all elements v in the tree
    // that has value greater than or equal to l and less than or equal to r.
    T sum(T l, T r)
    {
        T result = 0;

        // Truyen tham chieu bien result
        range_Sum_counter(root, result, l, r);

        return result;
    }

    // Easier recursive
    void range_Sum_counter(Node *cur_Node, T &counter, T L, T R)
    {
        // Take the value
        if (cur_Node->value >= L && cur_Node->value <= R)
        {
            counter += cur_Node->value;
        }

        // Going Left
        if (cur_Node->pLeft != NULL)
        {
            range_Sum_counter(cur_Node->pLeft, counter, L, R);
        }

        // Going Right
        if (cur_Node->pRight != NULL)
        {
            range_Sum_counter(cur_Node->pRight, counter, L, R);
        }
    }

    // STUDENT ANSWER END
};

int main()
{

    BinarySearchTree<int> bst;
    for (int i = 0; i < 10; ++i)
    {
        bst.add(i);
    }
    cout << bst.find(7) << endl;
    cout << bst.sum(0, 4) << endl;
    return 0;
}
