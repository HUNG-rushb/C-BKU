/*
            * HCMUT - DATA STRUCTURES & ALGORITHM
            * ASSIGNMENT 2 - PHASE 1
            * miniTest version 1.0
            * Note: this is not a official output, so test case may be wrong
            * @22:00 - 13 - 12 - 2020

*/
#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <assert.h>
#include "main.cpp"
using namespace std;

ofstream out("output.txt", ios::out);
// Print function
void print(int key, int value)
{
    cout << key << " ";
    out << key << " ";
}

// Test validation of AVL tree
void testAVLInsertion(BKUTree<int, int>::AVLTree *avl)
{

    int keys[] = {1, 3, 14, 6, 4, 8, 7, 2, 9};
    int size = sizeof(keys) / sizeof(int);
    try
    {
        cout << "Insert 1,3,14,6,4,8,7,2,9: " << endl;
        for (auto i : keys)
            avl->add(i, 2 * i);

        //avl->printTreeStructure();
        avl->traverseNLR(print);
        out << "\n";
        cout << "\n\n";
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
    cout << "Insert 12,23,10: " << endl;
    avl->add(12, 13);
    avl->add(23, 23);
    avl->add(10, 34);
    avl->traverseNLR(print);
    out << "\n";
    cout << "\n\n";
}

void testAVLDeletion(BKUTree<int, int>::AVLTree *avl)
{
    try
    {
        cout << "Delete 9,6:" << endl;
        avl->remove(9);
        //avl->printTreeStructure();
        avl->remove(6);
        //avl->printTreeStructure();
        avl->traverseNLR(print);
        cout << '\n';
        //avl->traverseNLR(print);
    }

    catch (const char *e)
    {
        cerr << e << '\n';
    }
}

void testAVLsearch(BKUTree<int, int>::AVLTree *avl)
{
    try
    {
        cout << "Search value of key 7: " << avl->search(7) << endl;
        out << avl->search(7) << " ";
        cout << "Search value of key 12: " << avl->search(12) << endl;
        out << avl->search(12) << " ";
        cout << "Search value of key 8: " << avl->search(8) << endl;
        out << avl->search(8) << " ";
        cout << "Search value of key 100: " << avl->search(100) << endl;
        out << avl->search(100) << " ";
    }
    catch (const char *e)
    {
        cout << "Search value of key 100: " << e << endl;
        out << e << " ";
    }
}

void testSplayInsertion(BKUTree<int, int>::SplayTree *splay)
{
    int keys[] = {1, 3, 14, 6, 4, 8, 7, 2, 9};
    int size = sizeof(keys) / sizeof(int);
    try
    {
        cout << "Insert 1,3,14,6,4,8,7,2,9: " << endl;
        for (auto i : keys)
            splay->add(i, 2 * i);

        //avl->printTreeStructure();
        splay->traverseNLR(print);
        out << "\n";
        cout << "\n\n";
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
    cout << "Insert 12,23,10: " << endl;
    splay->add(12, 13);
    splay->add(23, 23);
    splay->add(10, 34);
    splay->traverseNLR(print);
    out << "\n";
    cout << "\n\n";
}

void testSplaySearch(BKUTree<int, int>::SplayTree *splay)
{
    try
    {
        cout << "Search value of key 6: ";
        cout << splay->search(6) << endl;
        out << "Search value of key 6: ";
        out << splay->search(6) << endl;

        cout << "Search value of key 8: ";
        cout << splay->search(8) << endl;
        out << "Search value of key 8: ";
        out << splay->search(8) << endl;

        cout << "Search value of key 14: ";
        cout << splay->search(14) << endl;
        out << "Search value of key 14: ";
        out << splay->search(14) << endl;

        splay->search(25);
    }
    catch (const char *e)
    {
        cout << "Search value of key 25: " << e << endl;
        out << "Search value of key 25: " << e << endl;
    }
}

void testSplayDeletion(BKUTree<int, int>::SplayTree *splay)
{
    cout << "\nRemove key 4: " << endl;
    splay->remove(4);
    splay->traverseNLR(print);
}

void testBKUInsertion(BKUTree<int, int> *tree)
{
    int keys[] = {1, 3, 14, 6, 4, 8, 7, 2, 9, 12, 23, 10};
    int size = sizeof(keys) / sizeof(keys[0]);
    for (int i = 0; i < size; i++)
        tree->add(keys[i], keys[i]);
    cout << "Insert 1, 3, 14, 6, 4, 8, 7, 2, 9, 12, 23, 10: " << endl;
    cout << "AVL traverse: ";
    tree->traverseNLROnAVL(print);
    cout << endl
         << "Splay traverse: ";
    tree->traverseNLROnSplay(print);
}

void testBKUSearch(BKUTree<int, int> *tree)
{
    cout << "Search 4: " << endl;
    vector<int> track;
    int value = tree->search(4, track);
    cout << "Value of key 4: " << value << endl;
    out << value << endl;
    cout << "AVL traverse: ";
    tree->traverseNLROnAVL(print);
    cout << endl
         << "Splay traverse: ";
    tree->traverseNLROnSplay(print);

    cout << "\nTraversed List: ";
    for (auto i : track)
    {
        cout << i << ",";
        out << i << ",";
    }
}

void testBKUDeletion(BKUTree<int, int> *tree)
{
    cout << "Remove 8: " << endl;
    tree->remove(8);
    cout << "AVL traverse: ";
    tree->traverseNLROnAVL(print);
    cout << endl
         << "Splay traverse: ";
    tree->traverseNLROnSplay(print);

    cout << "\nRemove 14: " << endl;
    tree->remove(14);
    cout << "AVL traverse: ";
    tree->traverseNLROnAVL(print);
    cout << endl
         << "Splay traverse: ";
    tree->traverseNLROnSplay(print);
}

void PreTraverse(typename BKUTree<int, int>::AVLTree::Node *a)
{
    if (a == NULL)
        return;
    if (a != a->corr->corr)
        throw "May be a corr pointer is incorrect! Check your tree again!\n";
    else if (a->corr->corr == a)
        cout << "[" << a->entry->key << "<--->" << a->corr->entry->key << "]"
             << " ";
    PreTraverse(a->left);
    PreTraverse(a->right);
}

void testCorrPointer(BKUTree<int, int> *tree)
{
    typename BKUTree<int, int>::AVLTree::Node *avlNode = tree->avl->root;
    cout << "\nTesting your corr: " << endl;
    PreTraverse(avlNode);
}

#define TEST01 "6 3 1 2 4 8 7 14 9 6 3 1 2 4 12 8 7 9 10 14 23 4 2 1 3 12 8 7 10 14 23 "
#define TEST02 "14 13 16 Not found "
#define TEST03 "9 7 2 1 4 3 6 8 14 10 9 7 2 1 4 3 6 8 14 12 23 "
#define TEST04 "Search value of key 6: 12Search value of key 8: 16Search value of key 14: 28Search value of key 25: Not found"
#define TEST05 "3 2 1 23 10 6 8 7 9 14 12 "
#define TEST06 "6 3 1 2 4 12 8 7 9 10 14 23 10 9 7 2 1 4 3 6 8 14 12 23 "
#define TEST07 "6 3 1 2 4 12 9 7 10 14 23 7 2 1 4 3 6 10 9 14 12 23 6 3 1 2 4 12 9 7 10 23 12 10 7 2 1 4 3 6 9 23 "
#define TEST08 "46 3 1 2 4 12 9 7 10 23 12 10 4 2 1 3 7 6 9 23 12,9,7,6,3,"
#define TEST09 "May be a corr pointer is incorrect! Check your tree again!\n"
int main()
{
    BKUTree<int, int>::AVLTree *avl = new BKUTree<int, int>::AVLTree();
    string result = "";
    string str;
    fstream in;

    // TEST CASE 01
    cout << "==========AVL Tree=========\n";
    cout << "TEST 01: " << endl;
    testAVLInsertion(avl);
    testAVLDeletion(avl);
    out.close();

    in.open("output.txt", ios::in);
    while (!in.eof())
    {
        getline(in, str);
        result += str;
    }

    in.close();
    assert(result == TEST01);

    //TEST 02
    cout << endl
         << "TEST 02: " << endl;
    out.open("output.txt", ios::out);
    out.clear();
    testAVLsearch(avl);
    out.close();
    result.clear();
    if (!in.is_open())
    {
        in.open("output.txt");
        while (!in.eof())
        {
            getline(in, str);
            result += str;
        }
        in.close();
    }
    assert(result == TEST02);

    // TEST 03
    BKUTree<int, int>::SplayTree *splay = new BKUTree<int, int>::SplayTree();
    cout << "========Splay Tree========\n";
    cout << "TEST 03:" << endl;
    out.open("output.txt", ios::out);
    out.clear();
    testSplayInsertion(splay);

    out.close();
    result.clear();
    if (!in.is_open())
    {
        in.open("output.txt");
        while (!in.eof())
        {
            getline(in, str);
            result += str;
        }
        in.close();
    }

    assert(result == TEST03);

    // TEST 04
    cout << "TEST 04: " << endl;
    out.open("output.txt", ios::out);
    out.clear();
    testSplaySearch(splay);
    out.close();

    result.clear();
    if (!in.is_open())
    {
        in.open("output.txt");
        while (!in.eof())
        {
            getline(in, str);
            result += str;
        }
        in.close();
    }

    assert(result == TEST04);

    // TEST 05
    cout << endl
         << "TEST 05: " << endl;
    out.open("output.txt", ios::out);
    out.clear();
    testSplayDeletion(splay);
    out.close();

    result.clear();
    if (!in.is_open())
    {
        in.open("output.txt");
        while (!in.eof())
        {
            getline(in, str);
            result += str;
        }
        in.close();
    }
    assert(result == TEST05);

    delete splay;
    delete avl;
    // TEST 06 (BKU tree)
    cout << endl
         << "TEST 06: " << endl;
    cout << "========BKU Tree========\n";
    BKUTree<int, int> *tree = new BKUTree<int, int>(4);
    out.open("output.txt", ios::out);
    out.clear();
    testBKUInsertion(tree);
    out.close();

    result.clear();
    if (!in.is_open())
    {
        in.open("output.txt");
        while (!in.eof())
        {
            getline(in, str);
            result += str;
        }
        in.close();
    }
    assert(result == TEST06);

    // TEST 07 (Deletion)
    cout << endl
         << "\nTEST 07: " << endl;
    out.open("output.txt", ios::out);
    out.clear();
    testBKUDeletion(tree);
    out.close();

    result.clear();
    if (!in.is_open())
    {
        in.open("output.txt");
        while (!in.eof())
        {
            getline(in, str);
            result += str;
        }
        in.close();
    }
    assert(result == TEST07);
    // TEST 08 (Search)

    cout << endl
         << "\nTEST 08: " << endl;
    out.open("output.txt", ios::out);
    out.clear();
    testBKUSearch(tree);
    out.close();

    result.clear();
    if (!in.is_open())
    {
        in.open("output.txt");
        while (!in.eof())
        {
            getline(in, str);
            result += str;
        }
        in.close();
    }

    assert(result == TEST08);
    // TEST 09 (test corr pointer)
    delete tree;
    cout << "\nTEST 09: " << endl;
    BKUTree<int, int> *_tree = new BKUTree<int, int>(4);

    out.open("output.txt", ios::out | ios::trunc);
    testBKUInsertion(_tree);
    out.close();
    out.open("output.txt", ios::out | ios::trunc);
    try
    {
        testCorrPointer(_tree);
    }
    catch (const char *e)
    {
        out << e;
    }
    out.close();

    result.clear();
    if (!in.is_open())
    {
        in.open("output.txt");
        while (!in.eof())
        {
            getline(in, str);
            result += str;
        }
        in.close();
    }

    cout << endl
         << result;
    assert(result != TEST09);
    cout << endl
         << "All test case passed!" << endl;

    return 0;
}