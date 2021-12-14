#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template <class K, class V>
class BinaryTree
{
public:
    class Node;

private:
    Node *root;

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }
    class Node
    {
    private:
        K key;
        V value;
        Node *pLeft, *pRight;
        friend class BinaryTree<K, V>;

    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node *walker = this->root;
        int l = (int)posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }

    // Answer -----------------------------------------------------------------------------------

    int getDiameter()
    {
        return diameter(this->root);
    }

    int diameter(Node *tree)
    {

        // base case where tree is empty
        if (tree == NULL)
            return 0;

        // get the height of left and right sub-trees
        int left_height = height(tree->pLeft);
        int right_height = height(tree->pRight);

        // get the diameter of left and right sub-trees
        int left_diameter = diameter(tree->pLeft);
        int right_diameter = diameter(tree->pRight);

        // Return max of following three
        // 1) Diameter of left subtree
        // 2) Diameter of right subtree
        // 3) Height of left subtree + height of right subtree +
        // 1

        return max(left_height + right_height + 1, max(left_diameter, right_diameter));
    }

    int height(Node *node)
    {
        // base case tree is empty
        if (node == NULL)
            return 0;

        // If tree is not empty then height = 1 + max of left
        // height and right heights
        return 1 + max(height(node->pLeft), height(node->pRight));
    }
};

int main()
{
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 1, 4);
    binaryTree.addNode("L", 2, 6);
    binaryTree.addNode("R", 3, 9);
    binaryTree.addNode("LL", 4, 10);
    cout << binaryTree.getDiameter();
    return 0;
}