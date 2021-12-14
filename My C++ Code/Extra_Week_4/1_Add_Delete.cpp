#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
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

    // Helping function

    // Insert
    void add(Node *a, T value)
    {
        // Empty tree
        if (a == NULL)
        {
            Node *b = new Node(value);
            this->root = b;
        }
        // right of root
        else if (a->pRight == NULL && value > a->value)
        {
            Node *b = new Node(value);
            a->pRight = b;
        }
        // left of root
        else if (a->pLeft == NULL && value <= a->value)
        {
            Node *b = new Node(value);
            a->pLeft = b;
        }
        // go to the left
        else if (value < a->value)
            this->add(a->pLeft, value);
        // go to the right
        else
            this->add(a->pRight, value);
    }

    void add(T value)
    {
        //TODO
        this->add(this->root, value);
    }

    //  Delete
    Node *deleteNode1(Node *root, T key)
    {
        if (root == NULL)
            return root;
        if (root->value > key)
        {
            root->pLeft = deleteNode1(root->pLeft, key);
            return root;
        }
        else if (root->value < key)
        {
            root->pRight = deleteNode1(root->pRight, key);
            return root;
        }
        if (root->pLeft == NULL)
        {
            Node *temp = root->pRight;
            delete root;
            return temp;
        }
        else if (root->pRight == NULL)
        {
            Node *temp = root->pLeft;
            delete root;
            return temp;
        }
        else
        {
            Node *succParent = root;
            Node *succ = root->pRight;
            while (succ->pLeft != NULL)
            {
                succParent = succ;
                succ = succ->pLeft;
            }
            if (succParent != root)
                succParent->pLeft = succ->pRight;
            else
                succParent->pRight = succ->pRight;
            root->value = succ->value;
            delete succ;
            return root;
        }
    }
    void deleteNode(T value)
    {
        //TODO
        //cout << "a\n";
        deleteNode1(this->root, value);
    }

    //------------------------------------------------------------------------------------------------
    string inOrderRec(Node *root)
    {
        stringstream ss;
        if (root != nullptr)
        {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }

    string inOrder()
    {
        return inOrderRec(this->root);
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
};

int main()
{
    BinarySearchTree<int> bst;
    bst.add(9);
    bst.add(2);
    bst.add(10);
    bst.add(8);
    cout << bst.inOrder() << endl;
    bst.add(11);
    bst.deleteNode(9);
    cout << bst.inOrder();
}
