// You should not need to change main.c.  However, while
// developing your software, you may wish to uncomment various
// things that print out information for debugging purposes.  You
// can certainly add your own printing code as well to help you 
// debug things.
//
// Note also that the TAs may print out information when checking
// to see if your code actually works properly.

#include <stdio.h>
#include <string.h>
#include "bst.h"

// Symbolic Constants
#define NAMELEN 256

// Types
typedef struct
{
	char szFirstName[NAMELEN];
	char szLastName[NAMELEN];
	int iAccountNumber;
} Customer;

// Local Functions
void PrintCustomer(void * param)
{
	Customer * pCust = (Customer *)param;
	printf("%s %s (%d)", pCust->szFirstName, pCust->szLastName, pCust->iAccountNumber);
}

int main(void)
{
	// Start with some customers
	Customer customers[]=
	{
		{"Jim","Ries",123456},
		{"Laura","Ries",789012},
		{"Abbie","Ries",111111},
		{"Charlotte","Ries",333333},
		{"Cisco","Ries",555555},
		{"Murphy","Ries",666666},
		{"Larry","Ries",888888},
		{"Allison","Ries",777777},
		{"Marie","Ries",999999},
		{"Maggie","Durant",121212},
		{"Paul","Durant",212121},
		{"Alex","Durant",444444},
		{"Katherine","Durant",222222},
	};

	int countCustomers = sizeof(customers)/sizeof(Customer);

	// Create an empty BST that we can add customers to	
	printf("Creating an empty BST...\n");
	BST * pBST = NewBST();

	for (int i=0;i<countCustomers;i++)
	{
		TreeInsert(pBST,&customers[i],customers[i].iAccountNumber);
	}

	// Print the Inorder Traversal
	printf("\n***In order:\n");
	InOrder(pBST,PrintCustomer);
	printf("\n");

	// Print the Preorder Traversal
	printf("\n***Preorder:\n");
	PreOrder(pBST,PrintCustomer);
	printf("\n");

	// Print the Postorder Traversal
	printf("\n***Postorder:\n");
	PostOrder(pBST,PrintCustomer);
	printf("\n");

	// Search the tree for particular customers and print those customers
	Customer * pCustomer;
	printf("\n\nLooking for 111111\n");
	pCustomer=(Customer *)Search(pBST,111111);
	if (NULL==pCustomer)
	{
		printf("Customer 111111 not found!\n");
	}
	else
	{
		printf("Found: ");
		PrintCustomer(pCustomer);
		printf("\n");
	}
	printf("\n\nLooking for 222222\n");
	pCustomer=(Customer *)Search(pBST,222222);
	if (NULL==pCustomer)
	{
		printf("Customer 222222 not found!\n");
	}
	else
	{
		printf("Found: ");
		PrintCustomer(pCustomer);
		printf("\n");
	}


	// Delete some customers from the tree and then print the InOrder
	printf("\nDeleting 111111 ...\n");
	TreeDelete(pBST,111111);
	InOrder(pBST,PrintCustomer);
	printf("\n");
	printf("\nDeleting 222222 ...\n");
	TreeDelete(pBST,222222);
	InOrder(pBST,PrintCustomer);
	printf("\n");


	// Insert a couple of customers to the tree and then print the InOrder
	Customer c = {"Ned","Needleman",000000};
	Customer d = {"Lou","Reed",654321};
	printf("\nAdding 000000 ...\n");
	TreeInsert(pBST,&c,c.iAccountNumber);
	printf("\nAdding 654321 ...\n");
	TreeInsert(pBST,&d,d.iAccountNumber);
	InOrder(pBST,PrintCustomer);
	printf("\n");

	// Free memory allocated to tree
	DestroyTree(pBST);
}
