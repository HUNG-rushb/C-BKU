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

    T getMin()
    {
        //TODO: return the minimum values of nodes in the tree.
        Node *current_node = this->root;

        while (current_node->pLeft != NULL)
        {
            current_node = current_node->pLeft;
        }

        return current_node->value;
    }

    T getMax()
    {
        //TODO: return the maximum values of nodes in the tree.
        Node *current_node = this->root;

        while (current_node->pRight != NULL)
        {
            current_node = current_node->pRight;
        }

        return current_node->value;
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
    cout << bst.getMin() << endl;
    cout << bst.getMax() << endl;

    return 0;
}