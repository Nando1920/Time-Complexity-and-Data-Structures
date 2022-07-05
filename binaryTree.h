#include<string>
#include <iostream>
#include <functional>
using namespace std;

class binaryTree
{
public:
    binaryTree()=default;
    binaryTree(const binaryTree&);
    binaryTree& operator=(const binaryTree&);
    binaryTree(binaryTree&&);
    binaryTree& operator=(binaryTree&&);
    ~binaryTree();
    using KeyType = int;
    using ItemType = string;

    ItemType* lookUp(KeyType);
    void insert(KeyType, ItemType);
    void remove(KeyType); 
    void displayEntries();
    void displayTree();
    void removeIf(std::function<bool(KeyType)>);


private:

    struct Node;
    static Node* leaf();
    static bool isLeaf(Node*);
    ItemType* lookupRec(KeyType, Node*);
    void insertRec(KeyType, ItemType, Node*&);
    void displayEntriesRec(Node*);
    void displayTreeRec(Node*,string);
    void removeRec(KeyType,Node*&);
    Node* detachMinimumNode(Node*&);
    void deepDelete(Node*);
    Node* root = leaf();
    Node* deepCopy(Node*);
};

