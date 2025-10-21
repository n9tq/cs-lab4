#ifndef _bst_h
#define _bst_h

// Symbolic Constants




// Data types

// NOTE! - You will want to fill out this data structure.  Do you want a separate
// NODE data structure as well?

// BST Data structure
typedef struct _BST
{
    int rootFull;           // Value to check if the tree has already been established when inserting a node
    void * item;            // Pointer to the item being inserted
    int key;                // Holds the key value of the item being inserted and is what determines it's place in the tree
    struct _BST * left;     // Pointer to left child of parent
    struct _BST * right;    // Pointer to right child of parent
    struct _BST * parent;
} BST;

typedef void (*NODEVISITFUNC)(void * parm);




// Prototypes
BST * NewBST();
void TreeInsert(BST * pBST, void * satellite, long long key);
void InOrder(BST * pBST, NODEVISITFUNC func);
void PreOrder(BST * pBST, NODEVISITFUNC func);
void PostOrder(BST * pBST, NODEVISITFUNC func);
void * Search(BST * pBST, long long key);

// A search function that returns the node of an object rather than its item to so it can be deleted
BST * NodeSearch(BST * pBST, long long key);

void TreeDelete(BST * pBST, long long key);

// Prototypes of functions to free space allocated to the full BST object
void DestroyLeftSide(BST * pBST);
void DestroyRightSide(BST * pBST);
void DestroyTree(BST * pBST);


#endif
