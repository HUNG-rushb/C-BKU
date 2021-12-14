#include <iostream>
#include <stdlib.h>
using namespace std;

struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

void showTrunks(Trunk *p)
{
    if (p == nullptr)
        return;

    showTrunks(p->prev);

    cout << p->str;
}

template <class K, class V>
class AVLTree
{
public:
    // --------------------------------------------------------
    class Entry
    {
    public:
        K key;
        V value;

        Entry(K key, V value) : key(key), value(value) {}
    };

    class Node
    {
        public:
        Entry *entry;
        Node *left;
        Node *right;
        int height;
        //typename AVLTree::Node *corr;

        Node()//Entry *entry = NULL, Node *left = NULL, Node *right = NULL)
        {
            this->entry = NULL;
            this->left = NULL;
            this->right = NULL;
            this->height = 0;
            //this->corr = NULL;
        }

        Node(Entry *entry)
        {
            this->entry = entry;
            this->left = NULL;
            this->right = NULL;
            this->height = 0;
            //this->corr = NULL;
        }
    };

 public:
        Node *root;

        AVLTree() : root(NULL){};
        ~AVLTree() { this->clear(); };

        // -----------------------------------------------------------------
        // -----------------------------------------------------------------
        // HELPFUL FUNCTION

        // Print the fucking tree
        void print_tree()
        {
            cout << "\n------------------------------------\n";
            cout << "AVL tree:\n\n";

            if (this->root == NULL)
                cout << "Nothing in the tree.\n";
            else
                printTree(this->root, nullptr, false);
        }

        void printTree(Node *root, Trunk *prev, bool isLeft)
        {
            if (root == nullptr)
                return;

            string prev_str = "    ";
            Trunk *trunk = new Trunk(prev, prev_str);

            printTree(root->right, trunk, true);

            if (!prev)
                trunk->str = "-> ";
            else if (isLeft)
            {
                trunk->str = ".---";
                prev_str = "   |";
            }
            else
            {
                trunk->str = "`---";
                prev->str = prev_str;
            }

            showTrunks(trunk);
            cout << root->entry->key << endl;

            if (prev)
                prev->str = prev_str;
            trunk->str = "   |";

            printTree(root->left, trunk, false);
        }

        //----------------------------------------------------------
        // Lay do cao cua Node
        int getHeight_Node(Node *node)
        {
            if (node == NULL)
                return 0;

            int lh = this->getHeight_Node(node->left);
            int rh = this->getHeight_Node(node->right);

            return (lh > rh ? lh : rh) + 1;
        }

        // Do cao cua cay
        int getHeight()
        {
            return this->getHeight_Node(this->root);
        }

        // Right rotation
        Node *rightRotate(Node *main)
        {
            Node *Left_child = main->left;
            Node *Right_child_of_leftchild = Left_child->right;

            Left_child->right = main;
            main->left = Right_child_of_leftchild;

            return Left_child;
        }

        // Left rotation
        Node *leftRotate(Node *main)
        {
            Node *Right_child = main->right;
            Node *Left_child_of_rightchild = Right_child->left;

            Right_child->left = main;
            main->right = Left_child_of_rightchild;

            return Right_child;
        }

        // Get Balance factor of node N
        int getBalance(Node *main)
        {
            if (main == NULL)
                return 0;

            return getHeight_Node(main->left) - getHeight_Node(main->right);
        }

        // Find the max value of the tree
        Node *maxValueNode(Node *main)
        {
            Node *current = main;

            /* loop down to find the right-most leaf */
            while (current->right != NULL)
                current = current->right;

            return current;
        }

        // Find the min value of the tree
        Node *minValueNode(Node* main)
        {
            Node* current = main;

            /* loop down to find the leftmost leaf */
            while (current->left != NULL)
                current = current->left;

            return current;
        }


        // -------------------------------------------------------------------
        // -------------------------------------------------------------------
        // -------------------------------------------------------------------


        void add(K key, V value)
        {
            if (this->root == NULL)
            {
                Entry *new_entry = new Entry(key, value);
                add(new_entry);
            }
            else if (this->root != NULL)
            {
                Node *coconut = this->search_helper(this->root, key);

                if  (coconut != NULL)
                    throw out_of_range("Duplicate key");
                else
                {
                    Entry *new_entry = new Entry(key, value);
                    add(new_entry);
                }
            }
        }

        void add(Entry *new_entry)
        {
            this->root = this->Insert_helper(this->root, new_entry);
        }

        Node *Insert_helper(Node *main, Entry *new_entry)
        {
            // If current node is NULL
            if (main == NULL)
            {
                main = new Node(new_entry);
                return main;
            }

            // If currentNode.key <= key, then travel to the right
            if (main->entry->key <= new_entry->key)
            {
                main->right = Insert_helper(main->right, new_entry);
            }
            // if currentNode.key > key, then travel to the left
            else if (main->entry->key > new_entry->key)
            {
                main->left = Insert_helper(main->left, new_entry);
            }

            // BALANCE THE TREE
            // Balance = Left - right
            int balance = getHeight_Node(main->left) - getHeight_Node(main->right);

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
                if (new_entry->key < main->right->entry->key)
                {
                    main->right = rightRotate(main->right);
                    return leftRotate(main);
                }

                // https://vi.wikipedia.org/wiki/C%C3%A2y_AVL#/media/T%E1%BA%ADp_tin:AVL_Insert3.jpg
                /* Example: right-right
                        (2)
                         \
                           4
                            \
                             5
                */
                else if (new_entry->key >= main->right->entry->key)
                {
                    return leftRotate(main);
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
                if (new_entry->key > main->left->entry->key)
                {
                    main->left = leftRotate(main->left);
                    return rightRotate(main);
                }

                // https://vi.wikipedia.org/wiki/C%C3%A2y_AVL#/media/T%E1%BA%ADp_tin:AVL_Insert1.jpg
                /* Example: left-right
                           5
                          /
                        (3)
                        /
                       2
                */
                else if (new_entry->key < main->left->entry->key)
                {
                    return rightRotate(main);
                }
            }

            return main;
        }

        // -------------------------------------------------------------------
        Node *remove_helper(Node *main, K key)
        {
            // STEP 1: PERFORM STANDARD BST DELETE
            if (main == NULL)
                return main;

            // If the key to be deleted is smaller
            // than the main's key, then it lies
            // in left subtree
            if (key < main->entry->key)
                main->left = remove_helper(main->left, key);

            // If the key to be deleted is greater
            // than the main's key, then it lies
            // in right subtree
            else if (key > main->entry->key)
                main->right = remove_helper(main->right, key);

            // if key is same as main's key, then
            // This is the node to be deleted
            else
            {
                // node with only one child or no child
                if ((main->left == NULL) ||
                    (main->right == NULL))
                {
                    Node *temp = main->left ?
                        main->left :
                        main->right;

                    // No child case
                    if (temp == NULL)
                    {
                        temp = main;
                        main = NULL;
                    }
                    else // One child case
                        *main = *temp; // Copy the contents of
                                       // the non-empty child
                    free(temp);
                }
                else
                {
                    // node with two children: Get the inorder
                    // successor (smallest in the right subtree)
                    //Node* temp = minValueNode(main->right);
                    Node* temp = maxValueNode(main->left);

                    // Copy the inorder successor's
                    // data to this node
                    main->entry->key = temp->entry->key;

                    // Delete the inorder successor
                    main->left = remove_helper(main->left, temp->entry->key);
                }
            }

            // If the tree had only one node
            // then return
            if (main == NULL)
                return main;

            // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
            main->height = 1 + max(getHeight_Node(main->left), getHeight_Node(main->right));

            // STEP 3: GET THE BALANCE FACTOR OF
            // THIS NODE (to check whether this
            // node became unbalanced)
            int balance = getBalance(main);

            // If this node becomes unbalanced,
            // then there are 4 cases

            // Left Left Case
            if (balance > 1 &&
                getBalance(main->left) >= 0)
                return rightRotate(main);

            // Left Right Case
            if (balance > 1 &&
                getBalance(main->left) < 0)
            {
                main->left = leftRotate(main->left);
                return rightRotate(main);
            }

            // Right Right Case
            if (balance < -1 &&
                getBalance(main->right) <= 0)
                return leftRotate(main);

            // Right Left Case
            if (balance < -1 &&
                getBalance(main->right) > 0)
            {
                main->right = rightRotate(main->right);
                return leftRotate(main);
            }

            return main;
        }

        void remove(K key)
        {
            this->root = remove_helper(this->root, key);
        }

        //--------------------------------------------------------------------
        V search(K key)
        {
            Node *result = this->root;

            if (this->root == NULL)
                throw out_of_range("Not found");

            while (result != NULL)
            {
                if (result->entry->key > key)
                    result = result->left;
                else if (result->entry->key < key)
                    result = result->right;
                else if (result->entry->key == key)
                    return result->entry->value;
            }

            if (result == NULL)
                throw out_of_range("Not found");
        }

        Node *search_helper(Node *main, K key)
        {
            Node *result = this->root;

            if (this->root == NULL)
                throw out_of_range("Not found");

            while (result != NULL)
            {
                if (result->entry->key > key)
                    result = result->left;
                else if (result->entry->key < key)
                    result = result->right;
                else if (result->entry->key == key)
                    return result;
            }

            return result;

        }
        // ------------------------------------------------------------------
        void clear()
        {
            while (this->root != NULL)
            {
                this->remove(this->root->entry->key);
            }
        }
};

int main()
{
    AVLTree<int,int> *my_AVL_tree = new AVLTree<int,int>;

    int my_array[] = {1,3,5,7,9,2,4};
    int array_size = sizeof(my_array) / sizeof(my_array[0]);

    for(int i = 0; i < array_size; i++)
    {
        my_AVL_tree->add(my_array[i], my_array[i] * 10);
    }
    my_AVL_tree->remove(5);
//    my_AVL_tree->add(5, 10);
//    my_AVL_tree->add(6, 10);
//    my_AVL_tree->print_tree();
//
//    my_AVL_tree->clear();

    //cout << my_AVL_tree->search(100);

    my_AVL_tree->print_tree();
    return 0;
}




