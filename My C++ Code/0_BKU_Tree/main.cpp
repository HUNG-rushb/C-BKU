#include <iostream>
#include <queue>
#include <vector>
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

//----------------------------------------------------------------------
//                   ___  __ ____  __  ______
//                  / _ )/ //_/ / / / /_  __/______ ___
//                 / _  / ,< / /_/ /   / / / __/ -_) -_)
//                /____/_/|_|\____/   /_/ /_/  \__/\__/
//----------------------------------------------------------------------
template <class K, class V>
class BKUTree
{
public:
    class AVLTree;
    class SplayTree;

    class Entry
    {
    public:
        K key;
        V value;

        Entry(K key, V value) : key(key), value(value) {}
    };

    //--------------------------------------------
    AVLTree *avl;
    SplayTree *splay;

    // Key queue
    queue<K> keys;
    int maxNumOfKeys;

    //----------------------------------------------------------------------
    //                   ___  __ ____  __  ______
    //                  / _ )/ //_/ / / / /_  __/______ ___
    //                 / _  / ,< / /_/ /   / / / __/ -_) -_)
    //                /____/_/|_|\____/   /_/ /_/  \__/\__/
    //----------------------------------------------------------------------
    BKUTree(int maxNumOfKeys = 5)
    {
        this->maxNumOfKeys = maxNumOfKeys;
        this->avl = new AVLTree;
        this->splay = new SplayTree;
    }

    ~BKUTree()
    {
        this->clear();
    }

    // -----------------------------------------------------------------
    // SUPPORT FUNCTION

    // Print both tree
    void print_both_tree()
    {
        this->avl->print_tree();
        this->splay->print_tree();
        cout << "....................................................................................\n\n";
    }

    // Print queue
    void print_queue()
    {
        queue<K> print_queue = this->keys;

        cout << "\nThe queue is: ";
        while (print_queue.empty() == false)
        {
            cout << print_queue.front() << " ";
            print_queue.pop();
        }
    }

    // Kiss the queue
    void take_care_queue(K new_key)
    {
        int queue_size = this->keys.size();
        if (queue_size == maxNumOfKeys)
        {
            this->keys.pop();
            this->keys.push(new_key);
        }
        else
        {
            this->keys.push(new_key);
        }
    }

    // Is the new key in the queue?
    bool in_key_queue(queue<K> my_queue, K new_key)
    {
        K test;
        while (!my_queue.empty())
        {
            test = my_queue.front();
            my_queue.pop();

            if (test == new_key)
                return true;
        }

        return false;
    }

    // Remove key from queue
    void remove_key(K new_key)
    {
        queue<K> new_queue = this->keys;
        queue<K> result_queue;

        while (new_queue.empty() == false)
        {
            K temp = new_queue.front();
            new_queue.pop();

            if (temp != new_key)
                result_queue.push(temp);
        }

        this->keys = result_queue;
    }

    // ------------------------------------------------------------------
    // ------------------------------------------------------------------
    // ------------------------------------------------------------------
    void add(K key, V value)
    {
        this->avl->add(key, value);
        this->splay->add(key, value);

        this->take_care_queue(key);

        // Connect corr
        this->avl->search_helper(this->avl->root, key)->corr = this->splay->search_no_splay(key);
        this->splay->search_no_splay(key)->corr = this->avl->search_helper(this->avl->root, key);
    }

    // ------------------------------------------------------------------
    void remove(K key)
    {
        this->avl->remove(key);
        this->splay->remove(key);



        bool key_in_queue = in_key_queue(this->keys, key);

        if (key_in_queue == true)
        {
            this->remove_key(key);
            this->keys.push(this->splay->root->entry->key);
        }
        else
            this->take_care_queue(key);
    }

    // ------------------------------------------------------------------
    V search(K key, vector<K> &traversedList)
    {
        V result;

        // Neu nhu key da o tai goc cay splay
        if (this->splay->root->entry->key == key)
            return this->splay->root->entry->value;

        bool in_queue = this->in_key_queue(this->keys, key);

        // key khong nam trong queue
        if (in_queue == false)
        {
            typename BKUTree<K, V>::AVLTree::Node *papaya = this->splay->root->corr;
            typename BKUTree<K, V>::AVLTree::Node *node_result;

            node_result = this->avl->search_and_vector(papaya, papaya, key, traversedList);

            if (node_result == NULL)
            {
                node_result = this->avl->search_and_vector(this->avl->root, papaya, key, traversedList);

                if (node_result == NULL)
                    throw "Not found";
            }

            typename BKUTree<K, V>::SplayTree::Node *durian = node_result->corr;
            this->splay->splay_once(durian);

            result = node_result->entry->value;
        }
        // Key nam trong queue
        else
        {
            typename BKUTree<K, V>::SplayTree::Node *durian = this->splay->search_and_vector(key, traversedList);

            this->splay->splay_once(durian);
            result = durian->entry->value;
        }

        this->take_care_queue(key);
        return result;
    }

    // ------------------------------------------------------------------
    void traverseNLROnAVL(void (*func)(K key, V value))
    {
        this->avl->traverseNLR(*func);
    }

    void traverseNLROnSplay(void (*func)(K key, V value))
    {
        this->splay->traverseNLR(*func);
    }

    // ------------------------------------------------------------------
    void clear()
    {
        this->avl->clear();
        this->splay->clear();

        while (this->keys.empty() == false)
        {
            this->keys.pop();
        }
    }
    //----------------------------------------------------------------------

    //----------------------------------------------------------------------
    //               ____     __            ______
    //              / __/__  / /__ ___ __  /_  __/______ ___
    //             _\ \/ _ \/ / _ `/ // /   / / / __/ -_) -_)
    //            /___/ .__/_/\_,_/\_, /   /_/ /_/  \__/\__/
    //               /_/          /___/
    //----------------------------------------------------------------------
    class SplayTree
    {
    public:
        class Node
        {
        public:
            Entry *entry;
            Node *parent;
            Node *left;
            Node *right;
            typename AVLTree::Node *corr;

            Node()
            {
                this->entry = NULL;
                this->parent = NULL;
                this->left = NULL;
                this->right = NULL;
                this->corr = NULL;
            }

            Node(Entry *entry)
            {
                this->entry = entry;
                this->parent = NULL;
                this->left = NULL;
                this->right = NULL;
                this->corr = NULL;
            }
        };

        // -----------------------------------------------------------------
        // -----------------------------------------------------------------
        Node *root;

        SplayTree() : root(NULL){};
        ~SplayTree() { this->clear(); };

        // -----------------------------------------------------------------
        // SUPPORT FUNCTION

        // Print the fucking tree
        void print_tree()
        {
            cout << "\n------------------------------------\n";
            cout << "Splay tree:\n\n";

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

        //---------------------------------------------------------------
        Node *subtree_max(Node *subRoot)
        {
            Node *curr = subRoot;
            while (curr->right != NULL)
                curr = curr->right;
            return curr;
        }

        Node *subtree_min(Node *subRoot)
        {
            Node *curr = subRoot;
            while (curr->left != NULL)
                curr = curr->left;
            return curr;
        }

        // Right or Left Rotation
        void zig_or_zag(Node *x)
        {
            Node *p = x->parent;

            // Zig
            if (p->left == x)
            {
                Node *T2 = x->right;

                x->parent = NULL;
                x->right = p;

                p->parent = x;
                p->left = T2;

                if (T2 != NULL)
                    T2->parent = p;
            }
            // Zag
            else
            {
                Node *T1 = x->left;

                x->parent = NULL;
                x->left = p;

                p->parent = x;
                p->right = T1;

                if (T1 != NULL)
                    T1->parent = p;
            }
        }

        // Double right or Double left rotate
        void zig_zig_or_zag_zag(Node *x)
        {
            Node *p = x->parent;
            Node *g = p->parent;

            // Zig Zig
            if (p->left == x)
            {
                Node *T2 = x->right;
                Node *T3 = p->right;

                x->parent = g->parent;
                x->right = p;

                p->parent = x;
                p->left = T2;
                p->right = g;

                g->parent = p;
                g->left = T3;

                // Change parent
                if (x->parent != NULL)
                {
                    if (x->parent->left == g)
                        x->parent->left = x;
                    else
                        x->parent->right = x;
                }

                if (T2 != NULL)
                    T2->parent = p;

                if (T3 != NULL)
                    T3->parent = g;
            }
            // Zag Zag
            else
            {
                Node *T2 = p->left;
                Node *T3 = x->left;

                x->parent = g->parent;
                x->left = p;

                p->parent = x;
                p->left = g;
                p->right = T3;

                g->parent = p;
                g->right = T2;

                // Change parent
                if (x->parent != NULL)
                {
                    if (x->parent->left == g)
                        x->parent->left = x;
                    else
                        x->parent->right = x;
                }

                if (T2 != NULL)
                    T2->parent = g;

                if (T3 != NULL)
                    T3->parent = p;
            }
        }

        // Right Left or Left Right rotate
        void zig_zag_or_zag_zig(Node *x)
        {
            Node *p = x->parent;
            Node *g = p->parent;

            // Zag Zig
            if (p->right == x)
            {
                Node *T2 = x->left;
                Node *T3 = x->right;

                x->parent = g->parent;
                x->left = p;
                x->right = g;

                p->parent = x;
                p->right = T2;

                g->parent = x;
                g->left = T3;

                // Change parent
                if (x->parent != NULL)
                {
                    if (x->parent->left == g)
                        x->parent->left = x;
                    else
                        x->parent->right = x;
                }

                if (T2 != NULL)
                    T2->parent = p;

                if (T3 != NULL)
                    T3->parent = g;
            }
            // Zig Zag
            else
            {
                Node *T2 = x->left;
                Node *T3 = x->right;

                x->parent = g->parent;
                x->left = g;
                x->right = p;

                p->parent = x;
                p->left = T3;

                g->parent = x;
                g->right = T2;

                // Change parent
                if (x->parent != NULL)
                {
                    if (x->parent->left == g)
                        x->parent->left = x;
                    else
                        x->parent->right = x;
                }

                if (T2 != NULL)
                    T2->parent = g;

                if (T3 != NULL)
                    T3->parent = p;
            }
        }

        // Splay
        void splay(Node *x)
        {
            while (x->parent != NULL)
            {
                Node *p = x->parent;
                Node *g = p->parent;

                if (g == NULL)
                    zig_or_zag(x);
                else if ((g->left == p && p->left == x) || (g->right == p && p->right == x))
                    zig_zig_or_zag_zag(x);
                else
                    zig_zag_or_zag_zig(x);
            }

            this->root = x;
        }

        // Fix the corr
        void format_the_Corr(Node* main)
        {
            if (main == NULL)
                return;

            main->corr->corr = main;

            format_the_Corr(main->left);
            format_the_Corr(main->right);

            return;
        }

        // ------------------------------------------------------------------------
        // INSERT
        void add(K key, V value)
        {
            if (this->root == NULL)
            {
                Entry *new_entry = new Entry(key, value);
                add(new_entry);
            }
            else if (this->root != NULL)
            {
                Node *found = this->search_no_splay(key);

                if (found != NULL)
                    throw("Duplicate key");
                else
                {
                    Entry *new_entry = new Entry(key, value);
                    add(new_entry);
                }
            }
        }

        void add(Entry *new_entry)
        {
            if (this->root == NULL)
            {
                this->root = new Node(new_entry);
                return;
            }

            Node *current = this->root;
            while (current != NULL)
            {
                if (new_entry->key < current->entry->key)
                {
                    if (current->left == NULL)
                    {
                        Node *newNode = new Node(new_entry);

                        current->left = newNode;
                        newNode->parent = current;

                        // Splay it
                        splay(newNode);
                        return;
                    }
                    else
                        current = current->left;
                }
                else if (new_entry->key > current->entry->key)
                {
                    if (current->right == NULL)
                    {
                        Node *newNode = new Node(new_entry);

                        current->right = newNode;
                        newNode->parent = current;

                        // Splay it
                        splay(newNode);
                        return;
                    }
                    else
                        current = current->right;
                }
                else
                {
                    splay(current);
                    return;
                }
            }
        }

        // DELETE
        void remove(K key)
        {
            Node *test = search_no_splay(key);

            if (test == NULL)
            {
                throw("Not found");
            }

            Node *del = search_helper(key);

            // doesnt exist
            if (del == NULL)
            {
                throw("Not found");
            }

            Node *L = del->left;
            Node *R = del->right;

            // only one node and == key
            if (L == NULL && R == NULL)
            {
                this->root = NULL;
            }
            else if (L == NULL)
            {
                Node *M = subtree_min(R);
                splay(M);
                this->root->left = NULL;
            }
            else if (R == NULL)
            {
                Node *M = subtree_max(L);
                splay(M);
                this->root->right = NULL;
            }
            else
            {
                Node *M = subtree_max(L);
                splay(M);
                M->right = R;
                R->parent = M;
                delete del;

                this->format_the_Corr(this->root);
            }

            delete del;

            this->format_the_Corr(this->root);
        }

        // SEARCH
        V search(K key)
        {
            Node *test = search_no_splay(key);

            if (test == NULL)
            {
                throw("Not found");
            }

            Node *result = search_helper(key);

            if (result != NULL)
                return result->entry->value;
            else
                throw("Not found");
        }

        // If key doesnt exist splay the largest key to root
        // and return NULL
        Node *search_helper(K key)
        {
            Node *result = NULL;
            Node *curr = this->root;
            Node *prev = NULL;

            while (curr != NULL)
            {
                prev = curr;
                if (key < curr->entry->key)
                    curr = curr->left;
                else if (key > curr->entry->key)
                    curr = curr->right;
                else
                {
                    result = curr;
                    break;
                }
            }

            if (result != NULL)
                splay(result);
            else if (prev != NULL)
                splay(prev);

            return result;
        }

        // Search no splay
        Node *search_no_splay(K key)
        {
            Node *result = NULL;
            Node *curr = this->root;

            while (curr != NULL)
            {
                if (key < curr->entry->key)
                    curr = curr->left;
                else if (key > curr->entry->key)
                    curr = curr->right;
                else
                {
                    result = curr;
                    break;
                }
            }

            return result;
        }

        // CLEAR
        void clear()
        {
            while (this->root != NULL)
            {
                this->remove(this->root->entry->key);
            }
        }

        //--------------------------------------------------------------------------
        void pre_order(Node *main, void (*func)(K key, V value))
        {
            if (main == NULL)
                return;
            func(main->entry->key, main->entry->value);
            pre_order(main->left, *func);
            pre_order(main->right, *func);
        }

        void traverseNLR(void (*func)(K key, V value))
        {
            pre_order(this->root, *func);
        }

        // SPECIAL
        void splay_once(Node *main)
        {
            Node *p = main->parent;
            Node *g = p->parent;

            if (g == NULL)
            {
                zig_or_zag(main);
                this->root = main;
            }
            else if ((g->left == p && p->left == main) || (g->right == p && p->right == main))
            {
                zig_zig_or_zag_zag(main);

                if (main->parent == NULL)
                    this->root = main;
            }
            else
            {
                zig_zag_or_zag_zig(main);

                if (main->parent == NULL)
                    this->root = main;
            }
        }

        // BKU search
        Node *search_and_vector(K key, vector<K> &traversedList)
        {
            Node *main = this->root;

            while (main != NULL)
            {
                if (main->entry->key > key)
                {
                    traversedList.push_back(main->entry->key);
                    main = main->left;
                }
                else if (main->entry->key < key)
                {
                    traversedList.push_back(main->entry->key);
                    main = main->right;
                }
                else if (main->entry->key == key)
                {
                    break;
                }
            }

            return main;
        }
    };

    //----------------------------------------------------------------------
    //               ___ _   ____     ______
    //              / _ | | / / /    /_  __/______ ___
    //             / _  | |/ / /__    / / / __/ -_) -_)
    //            /_/ |_|___/____/   /_/ /_/  \__/\__/
    //----------------------------------------------------------------------
    class AVLTree
    {
    public:
        class Node
        {
        public:
            Entry *entry;
            Node *left;
            Node *right;
            int height;
            typename SplayTree::Node *corr;

            Node()
            {
                this->entry = NULL;
                this->left = NULL;
                this->right = NULL;
                this->height = 0;
                this->corr = NULL;
            }

            Node(Entry *entry)
            {
                this->entry = entry;
                this->left = NULL;
                this->right = NULL;
                this->height = 0;
                this->corr = NULL;
            }
        };

        //------------------------------------------------------------------
        //------------------------------------------------------------------
        Node *root;

        AVLTree() : root(NULL){};
        ~AVLTree() { this->clear(); };

        // -----------------------------------------------------------------
        // -----------------------------------------------------------------
        // SUPPORT FUNCTION

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
        Node *minValueNode(Node *main)
        {
            Node *current = main;

            /* loop down to find the leftmost leaf */
            while (current->left != NULL)
                current = current->left;

            return current;
        }

        // Fix the corr
        void format_the_Corr(Node* main)
        {
            if (main == NULL)
                return;

            main->corr->corr = main;

            format_the_Corr(main->left);
            format_the_Corr(main->right);

            return;
        }

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

                if (coconut != NULL)
                    throw("Duplicate key");
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
                    Node *temp = main->left ? main->left : main->right;

                    // No child case
                    if (temp == NULL)
                    {
                        temp = main;
                        main = NULL;
                    }
                    else               // One child case
                        *main = *temp; // Copy the contents of
                                       // the non-empty child
                    delete temp; //*****************************************************************
                    this->format_the_Corr(this->root);
                }
                else
                {
                    // node with two children: Get the inorder
                    // successor (smallest in the right subtree)
                    //Node *temp = minValueNode(main->right);
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
                throw("Not found");

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
                throw("Not found");
        }

        Node *search_helper(Node *main, K key)
        {
            Node *result = this->root;

            if (this->root == NULL)
                throw("Not found");

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

        // -------------------------------------------------------------------
        void pre_order(Node *main, void (*func)(K key, V value))
        {
            if (main == NULL)
                return;

            func(main->entry->key, main->entry->value);
            pre_order(main->left, *func);
            pre_order(main->right, *func);
        }

        void traverseNLR(void (*func)(K key, V value))
        {
            pre_order(this->root, *func);
        }

        //
        Node *search_and_vector(Node *main, Node *coconut, K key, vector<K> &traversedList)
        {
            while (main != NULL)
            {
                if (main->entry->key > key)
                {
                    traversedList.push_back(main->entry->key);
                    main = main->left;
                }
                else if (main->entry->key < key)
                {
                    traversedList.push_back(main->entry->key);
                    main = main->right;
                }
                else if (main->entry->key == key)
                {
                    break;
                }
                else if (main == coconut)
                {
                    throw "Not found";
                }
            }

            if (main != NULL)
            {
                return main;
            }
            else if (main == NULL)
            {
                return NULL;
            }

            return main;
        }
    };
};

void printKey(int key, int value)
{
    cout << key << endl;
}

 int main()
 {
//    BKUTree<int, int> *my_BKU_tree = new BKUTree<int, int>;
//     vector<int> my_key_vector;
//
//     int my_array[] = {1, 3, 14, 6, 4, 8, 7, 2, 9};
//     int array_size = sizeof(my_array) / sizeof(my_array[0]);
//
//     for (int i = 0; i < array_size; i++)
//     {
//         my_BKU_tree->add(my_array[i], my_array[i] * 2);
//     }
//           my_BKU_tree->add(12, 13);
//    my_BKU_tree->add(23, 23);
//    my_BKU_tree->add(10, 34);
//
//     my_BKU_tree->print_queue();
//     my_BKU_tree->print_both_tree();
//
//     //    my_BKU_tree->remove(7);
//     //
//     //    my_BKU_tree->print_queue();
//     //    my_BKU_tree->print_both_tree();
//     //
//       my_BKU_tree->remove(9);
//       my_BKU_tree->remove(6);
//
//
////     cout << my_BKU_tree->search(7, my_key_vector);
////
////     cout << "\nMy traversed list: ";
////     for (int i = 0; i < my_key_vector.size(); i++)
////     {
////         cout << my_key_vector[i] << " ";
////     }
////     cout << endl;
//
//     my_BKU_tree->print_queue();
//     my_BKU_tree->print_both_tree();

    BKUTree<int, int>* tree = new BKUTree<int, int>();
        int keys[] = { 1, 3, 5, 7, 9, 2, 4 ,67,98,100,45,35,89,76 };
        for (int i = 0; i < 14; i++) tree->add(keys[i], keys[i]);

        cout << "---76-67-45-35-9-4-2-1-3-5-7-89-98-100" << endl;
        tree->traverseNLROnSplay(printKey);

        cout << "--7-3-1-2-5-4-67-35-9-45-98-89-76-100-----------" << endl;
        tree->traverseNLROnAVL(printKey);
        cout << "REMOVE 05 :" << endl;
        tree->remove(5);

        cout << "--4-2-1-3-67-35-9-7-45-76-89-98-100" << endl;
        tree->traverseNLROnSplay(printKey);
        cout << "--7-3-1-2-4-67-35-9-45-98-89-76-100----" << endl;
        tree->traverseNLROnAVL(printKey);
        cout << "REMOVE 89:" << endl;

        tree->remove(89);
        cout << "-76-4-2-1-3-67-35-9-7-45-7-89-98-100" << endl;
        tree->traverseNLROnSplay(printKey);
        cout << "--7-3-1-2-4-67-35-9-45-98-76-100----" << endl;
        tree->traverseNLROnAVL(printKey);
        cout << "REMOVE 76:" << endl;

        tree->remove(76);
        cout << "-67-4-2-1-3-35-9-7-45-98-100" << endl;
        tree->traverseNLROnSplay(printKey);

        cout << "--7-3-1-2-4-67-35-9-45-98-100---" << endl;
        tree->traverseNLROnAVL(printKey);

        tree->print_both_tree();

        cout << "TEST CORR :" << endl;
        cout << "------4672----" << endl;

        cout << tree->splay->root->left->corr->entry->key << endl;

        cout << tree->splay->root->corr->entry->key<< endl;
        cout << tree->splay->root->left->left->corr->entry->key<< endl;

        cout << "--------------------" << endl;

     return 0;
 }
