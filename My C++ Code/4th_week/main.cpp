#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include<queue>
using namespace std;

template <class K, class V>
class BinaryTree
{
public:
    class Node;

private:
    Node *root;

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() {}

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


    // Functions----------------------------------------------------

    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node *walker = this->root;
        int l = posFromRoot.length();
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


    //--------------------------------------------------------------------------------------
    // STUDENT ANSWER BEGIN

    int height(Node *ptr)
    {
        // TODO: return height of the binary tree.
        if (ptr == NULL)
            return -1;
        else
            return max(height(ptr->pLeft), height(ptr->pRight)) + 1;
    }

    int getHeight()
    {
        return height(root);
    }

    void preOrder_Helper(Node *ptr)
    {
        // TODO: return the sequence of values of nodes in pre-order.
        if (ptr != 0)
        {
            cout << ptr->value << " ";
            preOrder_Helper(ptr->pLeft);
            preOrder_Helper(ptr->pRight);
        }
    }

    string preOrder()
    {
        preOrder_Helper(root);
        return "";
    }

    void inOrder_Helper(Node *ptr)
    {
        // TODO: return the sequence of values of nodes in in-order.
        if (ptr != 0)
        {
            inOrder_Helper(ptr->pLeft);
            cout << ptr->value << " ";
            inOrder_Helper(ptr->pRight);
        }
    }

    string inOrder()
    {
        inOrder_Helper(root);
        return "";
    }

    void postOrder_Helper(Node *ptr)
    {
        // TODO: return the sequence of values of nodes in post-order.
        if (ptr != 0)
        {
            postOrder_Helper(ptr->pLeft);
            postOrder_Helper(ptr->pRight);
            cout << ptr->value << " ";
        }
    }

    string postOrder()
    {
        postOrder_Helper(root);
        return "";
    }

    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------

    int countTwoChildrenNode_Helper(Node *ptr)
    {
        if (ptr->pLeft != NULL && ptr->pRight != NULL)
        {
            return 1 + countTwoChildrenNode_Helper(ptr->pRight) + countTwoChildrenNode_Helper(ptr->pLeft);
        }
        else
            return 0;

    }

    int countTwoChildrenNode()
    {
        return countTwoChildrenNode_Helper(root);
    }

    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------

    void sumOfLeafs_Hepler(Node *ptr, int &sum)
    {
        if (ptr == NULL)
            return;

        if  (ptr->pLeft == NULL && ptr->pRight == NULL)
            sum += ptr->value;

        sumOfLeafs_Hepler(ptr->pLeft, sum);
        sumOfLeafs_Hepler(ptr->pRight, sum);
    }

    int sumOfLeafs()
    {
        int result = 0;
        sumOfLeafs_Hepler(root, result);
        return result;
    }

    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------

    void BFS_Helper(Node *ptr)
    {
        if (ptr == NULL)
            return;

        queue<Node *> myQueue;

        myQueue.push(ptr);

        while (!myQueue.empty())
        {
            Node *current_node = myQueue.front();
            cout << current_node->value << " ";
            myQueue.pop();

            // Enqueue left child
            if (current_node->pLeft != NULL)
                myQueue.push(current_node->pLeft);

            // Enqueue right child
            if (current_node->pRight != NULL)
                myQueue.push(current_node->pRight);
        }
    }


    void BFS()
    {
        BFS_Helper(root);
    }

    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------

    bool isBST_Helper(Node *ptr, int min, int max)
    {
        // an empty tree is BST
        if (ptr == NULL)
            return true;

        if (ptr->value < min || ptr->value > max)
            return false;

        return isBST_Helper(ptr->pLeft, min, ptr->value - 1) && isBST_Helper(ptr->pRight, ptr->value + 1, max);
    }

    bool isBST()
    {
        // TODO: return true if a tree is a BST; otherwise, return false.
        return isBST_Helper(this->root, INT8_MIN, INT8_MAX);
    }

    // STUDENT ANSWER END
};

int main()
{
//    //-------------------------------------------------------------
//    BinaryTree<int, int> binaryTree;
//    binaryTree.addNode("", 2, 4);  // Add to root
//    binaryTree.addNode("L", 3, 6); // Add to root's left node
//    binaryTree.addNode("R", 5, 9); // Add to root's right node
//
//    cout << binaryTree.getHeight() << endl;
//    cout << binaryTree.preOrder() << endl;
//    cout << binaryTree.inOrder() << endl;
//    cout << binaryTree.postOrder() << endl;

//    //--------------------------------------------------------------
//    BinaryTree<int, int> binaryTree;
//    binaryTree.addNode("",2, 4);
//    binaryTree.addNode("L",3, 6);
//    binaryTree.addNode("R",5, 9);
//    binaryTree.addNode("LL",4, 10);
//    binaryTree.addNode("LR",6, 2);
//    cout << binaryTree.countTwoChildrenNode();

//    //--------------------------------------------------------------
//    BinaryTree<int, int> binaryTree;
//    binaryTree.addNode("", 2, 4);
//    cout << binaryTree.sumOfLeafs();

//    //--------------------------------------------------------------
//    BinaryTree<int, int> binaryTree;
//    binaryTree.addNode("", 2, 4);
//    binaryTree.addNode("L", 3, 6);
//    binaryTree.addNode("R", 5, 9);
//    cout << binaryTree.sumOfLeafs();

//    //--------------------------------------------------------------
//    BinaryTree<int, int> binaryTree;
//    binaryTree.addNode("",2, 4); // Add to root
//    binaryTree.addNode("L",3, 6); // Add to root's left node
//    binaryTree.addNode("R",5, 9); // Add to root's right node
//    binaryTree.BFS();


    //--------------------------------------------------------------
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4); // Add to root
    binaryTree.addNode("L", 3, 2); // Add to root's left node
    binaryTree.addNode("R", 5, 9); // Add to root's right node

    cout << binaryTree.isBST();

    return 0;
}
