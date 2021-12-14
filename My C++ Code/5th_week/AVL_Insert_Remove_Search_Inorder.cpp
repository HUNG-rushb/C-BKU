#include <iostream>
#include <queue>
#include <math.h>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template <class T>
class AVLTree
{
public:
    class Node;

private:
    Node *root;

protected:
    // Lay do cao cua Node
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;

        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);

        return (lh > rh ? lh : rh) + 1;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {}

    // Do cao cua cay
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }

    void printTreeStructure()
    {
        int height = this->getHeight();

        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }

        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);

        while (!q.empty())
        {
            temp = q.front();
            q.pop();

            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }

            printNSpace(space);
            count++;

            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }

            if (level == height)
                return;
        }
    }

    // Answer---------------------------------------------------------------------------

    // HELPFUL FUNCTION ----------------------------------------------------------------
    //https://vi.wikipedia.org/wiki/Ph%C3%A9p_quay_c%C3%A2y_nh%E1%BB%8B_ph%C3%A2n#/media/T%E1%BA%ADp_tin:Phep_quay.png
    // Right rotation
    Node *rightRotate(Node *main)
    {
        Node *Left_child = main->pLeft;
        Node *Right_child_of_leftchild = Left_child->pRight;

        Left_child->pRight = main;
        main->pLeft = Right_child_of_leftchild;

        return Left_child;
    }

    //Left rotation
    Node *leftRotate(Node *main)
    {
        Node *Right_child = main->pRight;
        Node *Left_child_of_rightchild = Right_child->pLeft;

        Right_child->pLeft = main;
        main->pRight = Left_child_of_rightchild;

        return Right_child;
    }

    // Get Balance factor of node N
    int getBalance(Node *N)
    {
        if (N == NULL)
            return 0;

        return getHeightRec(N->pLeft) - getHeightRec(N->pRight);
    }

    // Find the max value of the tree
    Node *maxValueNode(Node *main)
    {
        Node *current = main;

        /* loop down to find the right-most leaf */
        while (current->pRight != NULL)
            current = current->pRight;

        return current;
    }
    //--------------------------------------------------------------------------

    // INSERT ------------------------------------------------------------------
    Node *Insert_helper(Node *t, T key)
    {
        // If current node is NULL
        if (t == NULL)
        {
            t = new Node(key);
            return t;
        }

        // If currentNode.key <= key, then travel to the right
        if (t->data <= key)
        {
            t->pRight = Insert_helper(t->pRight, key);
        }
        // if currentNode.key > key, then travel to the left
        else if (t->data > key)
        {
            t->pLeft = Insert_helper(t->pLeft, key);
        }

        // BALANCE THE TREE
        // Balance = Left - right
        int balance = getHeightRec(t->pLeft) - getHeightRec(t->pRight);

        // If height of right-subtree is larger
        if (balance < -1)
        {
            // https://vi.wikipedia.org/wiki/C%C3%A2y_AVL#/media/T%E1%BA%ADp_tin:AVL_Insert4.jpg
            /* Example: right-left
                    (2)
                      \
                       4
                      /
                    3
            */
            if (key < t->pRight->data)
            {
                t->pRight = rightRotate(t->pRight);
                return leftRotate(t);
            }

            // https://vi.wikipedia.org/wiki/C%C3%A2y_AVL#/media/T%E1%BA%ADp_tin:AVL_Insert3.jpg
            /* Example: right-right
                    (2)
                     \
                       4
                        \
                         5
            */
            else if (key >= t->pRight->data)
            {
                return leftRotate(t);
            }
        }

        // If height of left-subtree is larger
        if (balance > 1)
        {
            // https://vi.wikipedia.org/wiki/C%C3%A2y_AVL#/media/T%E1%BA%ADp_tin:AVL_Insert2.jpg
            /* Example: left-right
                       5
                      /
                    (3)
                      \
                       4
            */
            if (key > t->pLeft->data)
            {
                t->pLeft = leftRotate(t->pLeft);
                return rightRotate(t);
            }

            // https://vi.wikipedia.org/wiki/C%C3%A2y_AVL#/media/T%E1%BA%ADp_tin:AVL_Insert1.jpg
            /* Example: left-right
                       5
                      /
                    (3)
                    /
                   2
            */
            else if (key < (t->pLeft)->data)
            {
                return rightRotate(t);
            }
        }

        return t;
    }

    void insert(const T &value)
    {
        this->root = Insert_helper(root, value);
    }

    // REMOVE -------------------------------------------------------------------
    // Recursive function to delete a node with given key from subtree with
    // given root. It returns root of the modified subtree.
    Node *remove_helper(Node *root, int key)
    {

        // STEP 1: PERFORM STANDARD BST DELETE
        if (root == NULL)
            return root;

        // If the key to be deleted is smaller
        // than the root's key, then it lies
        // in left subtree
        if (key < root->data)
            root->pLeft = remove_helper(root->pLeft, key);

        // If the key to be deleted is greater
        // than the root's key, then it lies
        // in right subtree
        else if (key > root->data)
            root->pRight = remove_helper(root->pRight, key);

        // if key is same as root's key, then
        // This is the node to be deleted
        else
        {
            // node with only one child or no child
            if ((root->pLeft == NULL) || (root->pRight == NULL))
            {
                Node *temp = root->pLeft ? root->pLeft : root->pRight;

                // No child case
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else               // One child case
                    *root = *temp; // Copy the contents of
                                   // the non-empty child
                free(temp);
            }
            else
            {
                // node with two children: Get the inorder
                // successor (smallest in the right subtree)
                Node *temp = maxValueNode(root->pLeft);

                // Copy the inorder successor's
                // data to this node
                root->data = temp->data;

                // Delete the inorder successor
                root->pLeft = remove_helper(root->pLeft, temp->data);
            }
        }

        // If the tree had only one node
        // then return
        if (root == NULL)
            return root;

        // STEP 3: GET THE BALANCE FACTOR OF
        // THIS NODE (to check whether this
        // node became unbalanced)
        int balance = getBalance(root);

        // If this node becomes unbalanced,
        // then there are 4 cases

        // Left Left Case
        if (balance > 1 && getBalance(root->pLeft) >= 0)
            return rightRotate(root);

        // Left Right Case
        if (balance > 1 && getBalance(root->pLeft) < 0)
        {
            root->pLeft = leftRotate(root->pLeft);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 && getBalance(root->pRight) <= 0)
            return leftRotate(root);

        // Right Left Case
        if (balance < -1 && getBalance(root->pRight) > 0)
        {
            root->pRight = rightRotate(root->pRight);
            return leftRotate(root);
        }

        return root;
    }

    void remove(const T &value)
    {
        this->root = remove_helper(root, value);
    }

    // SEARCH -----------------------------------------------------------------
    // When tree contains value, search return true
    void search_helper(Node *main, T key, bool &found)
    {
        if (main == NULL)
        {
            found = false;
            return;
        }
        else if (key < main->data)
            search_helper(main->pLeft, key, found);
        else if (key > main->data)
            search_helper(main->pRight, key, found);
        else if (key == main->data)
        {
            found = true;
            return;
        }
    }

    bool search(const T &value)
    {
        bool found = false;
        search_helper(root, value, found);

        return found;
    }

    // PRINT IN-ORDER -------------------------------------------------------------
    void printInorder_helper(Node *main)
    {
        if (main == NULL)
            return;
        printInorder_helper(main->pLeft);
        cout << main->data << " ";
        printInorder_helper(main->pRight);
    }

    void printInorder()
    {
        printInorder_helper(root);
    }

    // Class Node
    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

int main()
{
    //    AVLTree<int> avl;
    //
    //    for (int i = 0; i < 9; i++)
    //    {
    //        avl.insert(i);
    //    }
    //
    //    avl.printTreeStructure();

    // AVLTree<int> avl;
    // int arr[] = {10, 52, 98, 32, 68, 92, 40, 13, 42, 63};
    // for (int i = 0; i < 10; i++)
    // {
    //     avl.insert(arr[i]);
    // }
    // avl.remove(10);
    // avl.printTreeStructure();

    AVLTree<int> avl;
    int arr[] = {10, 52, 98, 32, 68, 92, 40, 13, 42, 63, 99, 100};
    for (int i = 0; i < 12; i++)
    {
        avl.insert(arr[i]);
    }
    avl.remove(52);
    avl.printInorder();
    cout << endl;
    cout << avl.search(10);

    return 0;
}
