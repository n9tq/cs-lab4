#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include "bst.h"
#include <stdio.h>

// Local functions

// These are stubs.  That is, you need to implement these functions.

// This function allocates memory for a new BST object and intializes all of the values of
// the object to be either 0 or NULL
BST * NewBST()
{
    BST *bst = malloc(sizeof(BST));
    bst->rootFull = 0;
    bst->item = NULL;
    bst->key = 0;
    bst->left = NULL;
    bst->right = NULL;
    return bst;
}

// This function is used to insert any node into the tree. If the root has not been filled in,
// it fills that in first. All subsequen nodes are inserted into their correct place in the BST.
void TreeInsert(BST * pBST, void * satellite, long long key)
{
    // Fill in the root node if there isn't one
    if(pBST->rootFull == 0){
        pBST->item = satellite;
        pBST->key = key;
        pBST->rootFull = 1;
    }
    else{
        int inserted = 0;
        // Do the following checks until the node has been inserted
        while(inserted == 0){
            // If the value to be inserted needs to go right, and node to the right is empty, insert
            if(key > pBST->key && pBST->right == NULL){
                pBST->right = malloc(sizeof(BST));
                pBST->right->item = satellite;
                pBST->right->key = key;
                pBST->right->parent = pBST;
                pBST->right->right = NULL;
                pBST->right->left = NULL;
                inserted = 1;   // Marks that we've inserted and can exit the loop
            }
            // If the value to be inserted needs to go left, and node to the left is empty, insert
            else if(key < pBST->key && pBST->left == NULL){
                pBST->left = malloc(sizeof(BST));
                pBST->left->item = satellite;
                pBST->left->key = key;
                pBST->left->parent = pBST;
                pBST->left->right = NULL;
                pBST->left->left = NULL;
                inserted = 1;   // Marks that we've inserted and can exit the loop
            }
            // If the node has not been inserted, then move the parent node we're comparing the value to
            // either to the right or left
            else{
                if(key > pBST->key){
                    pBST = pBST->right;
                }else{
                    pBST = pBST->left;
                }
            }
        }
    }
}

// This function prints the in order traversal of the tree. It utilizes the left-child, parent, right child
// printing method via recurrsion to do this.
void InOrder(BST * p, NODEVISITFUNC func)
{
    if(p != NULL){
        InOrder(p->left, func);     // Traverse to the bottom of the left side of the tree
        func(p->item);              // Print the value of the node the function is at
        InOrder(p->right, func);    // Traverse to the bottom of the right side of the tree
    }
}

// This function prints the pre order traversal of the tree. It utilizes the parent, left-child, right-child
// printing method via recurrsion to do this.
void PreOrder(BST * pBST, NODEVISITFUNC func)
{
    if(pBST != NULL){
        func(pBST->item);               // Print the value of the node the function is at
        PreOrder(pBST->left, func);     // Traverse to the bottom of the left side of the tree
        PreOrder(pBST->right, func);    // Traverse to the bottom of the right side of the tree
    }
}

// This function prints the post order traversal of the tree. It utilizes the left-child, right-child, parent
// printing method via recurrsion to do this.
void PostOrder(BST * pBST, NODEVISITFUNC func)
{
    if(pBST != NULL){
        PostOrder(pBST->left, func);    // Traverse to the bottom of the left side of the tree
        PostOrder(pBST->right, func);   // Traverse to the bottom of the right side of the tree
        func(pBST->item);               // Print the value of the node the function is at
    }
}

// This function searches the BST for a given item using its key. If the key is found, that item is returned.
// If the key is not found, then the fuction returns NULL.
// This function is used for finding objects because it returns the pointer to the object and not the object's node.
void * Search(BST * pBST, long long key)
{
    void * itemToReturn;
    // If the key of item being searched for is larger than root, search right sub tree
    if(key > pBST->key){
        itemToReturn = Search(pBST->right, key);
    }
    // If the key of item being searched for is less than root, search left sub tree
    else if(key < pBST->key){
        itemToReturn = Search(pBST->left, key);
    }
    // If the key of item being searched for is equal to node we're at, return that item
    else if(key == pBST->key){
        itemToReturn = pBST->item;
        return itemToReturn;
    }
    // If this block is reached, then the key was not found, so we return NULL
    else{
        itemToReturn = NULL;
        return itemToReturn;
    }
    return itemToReturn;
}

// This function searches for a keys location in the BST and returns its node if the key is found. If the key
// is not found, the function returns NULL.
// This function is used for deletion because it returns pointer to the node rather than the object stored there.
BST * NodeSearch(BST * pBST, long long key){
    BST * itemToReturn;
    if(key > pBST->key){
        itemToReturn = NodeSearch(pBST->right, key);
    }else if(key < pBST->key){
        itemToReturn = NodeSearch(pBST->left, key);
    }else if(key == pBST->key){
        itemToReturn = pBST;
        return itemToReturn;
    }else{
        itemToReturn = NULL;
        return itemToReturn;
    }
    return itemToReturn;
}

// This function removes nodes from the tree whether it has no children, one child, or two children.
void TreeDelete(BST * pBST, long long key)
{
    // Find the node to be deleted
    BST * itemToDelete = NodeSearch(pBST, key);

    // If the node to be deleted has no children, then set it's parent pointer to it to NULL and free the memory
    if(itemToDelete->left == NULL && itemToDelete->right == NULL){
        if(key > itemToDelete->parent->key){
            itemToDelete->parent->right = NULL;
        }else{
            itemToDelete->parent->left = NULL;
        }
        free(itemToDelete);
    }
    // If the object has only 1 child node then do the appropriate fix and delete the node to be deleted
    else if(itemToDelete->left != NULL && itemToDelete->right == NULL){
        if(itemToDelete->parent->left == itemToDelete){
            /*
            This repeated block of code basically performs the necessary swap function within the tree. It makes the
            to-be-deleted node's parent point to the to-be-deleted node's child, and then deletes the to-be-deleted node.
            The if/else statement surrounding it decides if the to-be-deleted node's parent's left or right node should point
            to the to-be-deleted node's child.
            */
            itemToDelete->parent->left = itemToDelete->left;
            itemToDelete->left->parent = itemToDelete->parent;
            free(itemToDelete);
        }else{
            itemToDelete->parent->right = itemToDelete->left;
            itemToDelete->left->parent = itemToDelete->parent;
            free(itemToDelete);
        }
    }else if(itemToDelete->left == NULL && itemToDelete->right != NULL){
        if(itemToDelete->parent->left == itemToDelete){
            itemToDelete->parent->left = itemToDelete->right;
            itemToDelete->right->parent = itemToDelete->parent;
            free(itemToDelete);
        }else{
            itemToDelete->parent->right = itemToDelete->right;
            itemToDelete->right->parent = itemToDelete->parent;
            free(itemToDelete);
        }
    // If the object has 2 children nodes then do appropriate fix and delte the node to be deleted
    }else{
        // Find the object to be deleted's successor by checking the right subtree
        if(itemToDelete->right->left != NULL){
            if(itemToDelete->parent->left == itemToDelete){
                itemToDelete->parent->left = itemToDelete->right->left;
                itemToDelete->right->left->parent = itemToDelete->parent;
                free(itemToDelete);
            }else{
                itemToDelete->parent->right = itemToDelete->right->left;
                itemToDelete->right->left->parent = itemToDelete->parent;
                free(itemToDelete);
            }
        }else{
            if(itemToDelete->parent->left == itemToDelete){
                itemToDelete->parent->left = itemToDelete->right;
                itemToDelete->right->parent = itemToDelete->parent;
                free(itemToDelete);
            }else{
                itemToDelete->parent->right = itemToDelete->right;
                itemToDelete->right->parent = itemToDelete->parent;
                free(itemToDelete);
            }
        }
    }
}

// Function to destroy left sub trees and free their memory
void DestroyLeftSide(BST * pBST){
    if(pBST->left != NULL){
        if(pBST->left->right != NULL){
            DestroyRightSide(pBST->left->right);
        }
        DestroyLeftSide(pBST->left);
    }
    free(pBST);
}

// Function to destroy right sub trees and free their memory
void DestroyRightSide(BST * pBST){
    if(pBST->right != NULL){
        if(pBST->right->left != NULL){
            DestroyLeftSide(pBST->right->left);
        }
        DestroyRightSide(pBST->right);
    }
    free(pBST);
}

// Function to destroy BST by using the DestroyLeftSide() and DestroyRightSide functions
void DestroyTree(BST * pBST){
    // Free left side of tree
    DestroyLeftSide(pBST->left);
    // Free Right side of the tree
    DestroyRightSide(pBST->right);

    free(pBST);
}