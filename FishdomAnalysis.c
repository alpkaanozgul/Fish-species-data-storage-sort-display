// Alp Kaan Özgül 2638096

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"

int main(int argc, char *argv[]) {
    struct AVLNode* returned_tree;
    returned_tree =readData(argc,argv);
    int command;
    float length_intialise =-1;
    int exit = 0;
    while (!exit)      // this while loop controls the whole program's functionality
    {
        fflush(stdin);
        printf("\n********Welcome to Fishdom Analysis********\n"
               "*******************************************\n"
               "Menu\n"
               "1. Display the full index of fishdom\n"
               "2. Display the heaviest fishes\n"
               "3. Display the longest fishes\n"
               "4. Exit\n"
               "*******************************************\n");
        scanf("%d", &command);
        fflush(stdin);

        switch (command)
        {
            case 1:
                displayIndex(returned_tree);
                break;
            case 2:
                heaviestFish(returned_tree);
                break;
            case 3:
                longestFish(returned_tree,&length_intialise);
                break;
            case 4:
                exit = 1;
                break;
            default:
                printf("command not recognized\n");
                break;
        }
    }


    return 0;
}
struct AVLNode* readData(int argc, char *argv[]){
    char filename[100];
    strcpy(filename,argv[1]);

    FILE* filefish = fopen(filename, "r");              // here it acceses opens the file in read mode

    if (filefish == NULL) {
        printf("The file couldn't be found.\n");
        return NULL;                                  // Return NULL if file not found
    } else {
        printf("The %s file has been loaded successfully!\n", filename);
    }
    struct AVLNode* t;
    t = CreateTree();     //here it initialises a AVLNode tye pointer which points to NULL
    t= MakeEmptyTree(t); // in this program we don't need to make empty in any stages of the program but i wanted to add it to stick with the lab worksheet format

    char line[200];

    char name[100];
    float weight;
    float length;
    char date[100];
    char city [100];

    while (fgets(line, sizeof(line), filefish) != NULL){ // this while loop itarates through txt file and assign the input's to according variable than passes to the insert function

        sscanf(line, "%[^,;],%f,%f,%[^,;],%[^\n]", name, &weight, &length, date, city);
        t = insertFish(t,name,weight,length,date,city);

    }



    fclose(filefish);



    return t;
}
struct AVLNode* CreateTree(void)
{
    return NULL;
}

struct AVLNode* MakeEmptyTree(struct AVLNode* t)
{
    if (t != NULL)
    {
        MakeEmptyTree(t->left);
        MakeEmptyTree(t->right);
        free(t);
    }
    return NULL;
}



struct AVLNode* insertFish(struct AVLNode* t, char name[100], float weight, float length, char date[100], char city[100]) {
    if (t == NULL) {
        // Create a new node
        t = malloc(sizeof(struct AVLNode));
        if (t == NULL)
            printf("Out of memory space!!!\n");
        else {            //this part assignes the arguments of the function to newly created node
            strcpy(t->name, name);
            t->weight = weight;
            t->length = length;
            strcpy(t->date, date);
            strcpy(t->city, city);
            t->height = 0;
            t->left = t->right = NULL;
            t->next = NULL;
        }
    } else if (weight < t->weight) {
        // this part recursively insert into the left subtree
        t->left = insertFish(t->left, name, weight, length, date, city);

        if (AVLTreeHeight(t->left) - AVLTreeHeight(t->right) == 2)  //checks the balance
            if (weight < t->left->weight)
                t = SingleRotateWithRight(t);
            else
                t = DoubleRotateWithRight(t);
    } else if (weight > t->weight) {
        // this part recursively insert into the right subtree
        t->right = insertFish(t->right, name, weight, length, date, city);

        if (AVLTreeHeight(t->right) - AVLTreeHeight(t->left) == 2) //checks the balance
            if (weight > t->right->weight)
                t = SingleRotateWithLeft(t);
            else
                t = DoubleRotateWithLeft(t);
    } else {
        // here if the same weight is found, creates a new node for the linked list
        struct AVLNode* newNode = malloc(sizeof(struct AVLNode));
        if (newNode == NULL) {
            printf("Out of memory space for linked list node!!!\n");
        } else {
            // initialize the new node to insert daata
            strcpy(newNode->name, name);
            newNode->weight = weight;
            newNode->length = length;
            strcpy(newNode->date, date);
            strcpy(newNode->city, city);
            newNode->height = 0;
            newNode->left = newNode->right = NULL;
            newNode->next = t->next;
            t->next = newNode;
        }
    }

    // update the height of the current node
    t->height = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;

    return t;
}




// function to perform a single right rotation
struct AVLNode* SingleRotateWithRight(struct AVLNode* t) {
    // create a new node and assign it as the new root
    struct AVLNode* newRoot = t->left;

    // update the left child of the original root to be the right child of the new root
    t->left = newRoot->right;

    // Update the right child of the new root to be the original root
    newRoot->right = t;

    // update the height of the original root and the new root
    t->height = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;
    newRoot->height = Max(AVLTreeHeight(newRoot->left), AVLTreeHeight(newRoot->right)) + 1;

    return newRoot;
}


// function to perform a double right rotation
struct AVLNode* DoubleRotateWithRight(struct AVLNode* t) {
    t->left = SingleRotateWithLeft(t->left);
    return SingleRotateWithRight(t);
}

// function to perform a single left rotation
struct AVLNode* SingleRotateWithLeft(struct AVLNode* t) {
    // create a new node and assign it as the new root
    struct AVLNode* newRoot = t->right;

    // update the right child of the original root to be the left child of the new root
    t->right = newRoot->left;

    // update the left child of the new root to be the original root
    newRoot->left = t;

    // update the height of the original root and the new root
    t->height = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;
    newRoot->height = Max(AVLTreeHeight(newRoot->left), AVLTreeHeight(newRoot->right)) + 1;

    return newRoot;
}


// Function to perform a double left rotation
struct AVLNode* DoubleRotateWithLeft(struct AVLNode* t) {
    t->right = SingleRotateWithRight(t->right);
    return SingleRotateWithLeft(t);
}

int AVLTreeHeight(struct AVLNode* t) //this function finds and returns the height of the tree
{
    if (t == NULL)
        return -1;
    else
        return t->height;
}

int Max(int x, int y) //this finds the which one is greater
{
    if (x >= y)
        return x;
    else
        return y;
}

void displayIndex(struct AVLNode* t) {
    if (t != NULL) {
        // traverse the left subtree
        displayIndex(t->left);

        // displays the current node's content
        printf("Name: %s, Weight: %.2f, Length: %.2f, Date: %s, City: %s\n",
               t->name, t->weight, t->length, t->date, t->city);

        // ddisplay the linked list nodes
        struct AVLNode* linkedlist_of_AVLNode = t->next;
        while (linkedlist_of_AVLNode != NULL) {
            printf("Name: %s, Weight: %.2f, Length: %.2f, Date: %s, City: %s\n",
                   linkedlist_of_AVLNode->name, linkedlist_of_AVLNode->weight, linkedlist_of_AVLNode->length,
                   linkedlist_of_AVLNode->date, linkedlist_of_AVLNode->city);
            linkedlist_of_AVLNode = linkedlist_of_AVLNode->next;
        }

        // traverse the right subtree
        displayIndex(t->right);
    }
}

void heaviestFish(struct AVLNode* t) {
    struct AVLNode* heaviest_traverse = t;

    // traverse to the rightmost node in the AVL tree
    while (heaviest_traverse->right != NULL) {
        heaviest_traverse = heaviest_traverse->right;
    }

    // print information of the rightmost node
    printf("Name: %s, Weight: %.2f, Length: %.2f, Date: %s, City: %s\n",
           heaviest_traverse->name, heaviest_traverse->weight, heaviest_traverse->length,
           heaviest_traverse->date, heaviest_traverse->city);

    // traverse and print the linked list nodes
    while (heaviest_traverse->next != NULL) {
        heaviest_traverse = heaviest_traverse->next;
        printf("Name: %s, Weight: %.2f, Length: %.2f, Date: %s, City: %s\n",
               heaviest_traverse->name, heaviest_traverse->weight, heaviest_traverse->length,
               heaviest_traverse->date, heaviest_traverse->city);
    }
}
/* The time complexity of the heaviestFish function is O(n).

Traversing to the rightmost node in the AVL tree: This operation has a time complexity of O(log n) in a balanced AVL tree, where n is the number of nodes in the tree. However, if the tree is not balanced, it could degrade to O(n), where n is the number of nodes in the tree.

Traversing and printing the linked list nodes: This operation has a linear time complexity of O(n), where n is the number of nodes in the linked list.

Since the overall time complexity is dominated by the linear traversal of the linked list, the overall time complexity of the function is O(n). */

// function to find and print information about the fish with the longest length in an AVL tree
void longestFish(struct AVLNode* t, float* longest) { // adress of the longest variable is passed to a pointer because when i track the length of the fish in
    // each iteration if the variable was local to the function it would loose it's data
    struct AVLNode* longest_traverse = NULL;

    // calling the helper function to find the node with the longest fish length
    longest_traverse = longestFishHelper(t, longest, longest_traverse);

    // print information about the fish with the longest length
    printf("Name: %s, Weight: %.2f, Length: %.2f, Date: %s, City: %s\n",
           longest_traverse->name, longest_traverse->weight, longest_traverse->length,
           longest_traverse->date, longest_traverse->city);
}


// helper function to find the fish with the longest length in an AVL tree
struct AVLNode* longestFishHelper(struct AVLNode* t, float* longest, struct AVLNode* longest_traverse) {
    if (t != NULL) {
        // traverse the left subtree and update the longest fish information
        longest_traverse = longestFishHelper(t->left, longest, longest_traverse);

        // check if the current node has a linked list
        if (t->next != NULL) {
            // traverse the linked list and update the longest fish information
            struct AVLNode* list_trav = t;
            while (list_trav != NULL) {
                // check if the current fish has a longer length than the previously found longest
                if (*longest == -1 || *longest < list_trav->length) {
                    // update the longest fish information
                    *longest = list_trav->length;
                    longest_traverse = list_trav;
                }
                // move to the next fish in the linked list
                list_trav = list_trav->next;
            }
        }

        // check if the length of the current node is longer than the previously found longest
        if (*longest == -1 || *longest < t->length) {
            // update the longest fish information
            *longest = t->length;
            longest_traverse = t;
        }

        // traverse the right subtree and update the longest fish information
        longest_traverse = longestFishHelper(t->right, longest, longest_traverse);
    }

    return longest_traverse;
}

/* The time complexity of the longestfishhelper function is O(n), where n is the total number of nodes in the AVL tree.
 * This is because the function traverses each node in the tree once and performs constant-time operations for each node.

The function visits each node in the AVL tree exactly once due to the recursive nature of the traversal.
For each node, the function performs constant-time operations, such as comparisons and updates based on the lengths of fish.
The while loop that traverses the linked list within each node also takes constant time per node in the linked list.
As a result, the overall time complexity is O(n), where n is the total number of nodes in the AVL tree. */









