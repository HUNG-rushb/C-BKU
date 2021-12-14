#include <iostream>
#include <stdlib.h>
#include <queue>
#include <math.h>
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

// -------------------------------------------------------------------------------------
template <class K, class V>
class SplayTree
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

        Node *parent;
        Node *left;
        Node *right;
        //typename AVLTree::Node *corr;

        Node()
        {
            this->entry = NULL;
            this->parent = NULL;
            this->left = NULL;
            this->right = NULL;
            //this->corr = NULL;
        }

        Node(Entry *entry)
        {
            this->entry = entry;
            this->parent = NULL;
            this->left = NULL;
            this->right = NULL;
            //this->corr = NULL;
        }
    };

public:
    Node *root;

    SplayTree() : root(NULL){};
    ~SplayTree()
    {
        this->clear();
    };

    // -----------------------------------------------------------------
    // HELPFUL FUNCTION


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
    Node *subtree_max(Node *main)
    {
        Node *current = main;
        while (current->right != NULL)
            current = current->right;

        return current;
    }

    Node *subtree_min(Node *main)
    {
        Node *current = main;
        while (current->left != NULL)
            current = current->left;

        return current;
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

//            if (x->parent == NULL)
//                this->root = x;
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

//            if (x->parent == NULL)
//                this->root = x;
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
            Node *T3= p->right;

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

//            if (x->parent == NULL)
//                this->root = x;
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

//            if (x->parent == NULL)
//                this->root = x;
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

//            if (x->parent == NULL)
//                this->root = x;
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

//            if (x->parent == NULL)
//                this->root = x;
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

    // -------------------------------------------------------------------

    // INSERT -----------------------------------------------------------------
    void add(K key, V value)
    {
        if (this->root == NULL)
        {
            Entry *new_entry = new Entry(key, value);
            add(new_entry);
        }
        else if (this->root != NULL)
        {
            Node* found = this->search_no_splay(key);

            if  (found != NULL)
                throw ("Duplicate key");
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

    // DELETE -----------------------------------------------------------------
    void remove(K key)
    {
        Node *del = search_helper(key);

        // doesnt exist
        if (del == NULL)
        {
            throw out_of_range("Not found");
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
        }

        delete del;
    }

    // SEARCH ------------------------------------------------------------------
    V search(K key)
    {
        Node *result = search_helper(key);

        if (result != NULL)
            return result->entry->value;
        else
            throw out_of_range("Not found");
    }

    // if key doesnt exist
    // splay the largest key to root
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

    Node* search_no_splay(K key)
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

    // CLEAR --------------------------------------------------------------------
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

    SplayTree<int,int> *my_splay_tree = new SplayTree<int,int>;

    int my_array[] = {1,3,5,7,9,3,2,4};
    int array_size = sizeof(my_array) / sizeof(my_array[0]);

    for(int i = 0; i < array_size; i++)
    {
        my_splay_tree->add(my_array[i], my_array[i] * 10);
    }

//
//
//
//    my_splay_tree->clear();

    //my_splay_tree->printTreeStructure();
    my_splay_tree->print_tree();
    return 0;
}
