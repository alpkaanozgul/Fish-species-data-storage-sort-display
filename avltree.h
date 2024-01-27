// Alp Kaan Özgül 2638096
// Created by alpka on 26.12.2023.
//

#ifndef UNTITLED14_AVLTREE_H
#define UNTITLED14_AVLTREE_H

#endif //UNTITLED14_AVLTREE_H



struct AVLNode {
    char name[100];
    float weight;
    float length;
    char date[100];
    char city [100];
    struct AVLNode* left;
    struct AVLNode* right;
    struct AVLNode* next;
    int height;
};

struct AVLNode* readData(int argc, char *argv[]);
struct AVLNode* CreateTree(void);
struct AVLNode* MakeEmptyTree(struct AVLNode* t);
void DisplayTreeStructure(struct AVLNode* t, int depth);
struct AVLNode* insertFish(struct AVLNode* t,char name[100],float weight,float length,char date[100],char city[100]);
int AVLTreeHeight(struct AVLNode* t);
int Max(int x, int y);
struct AVLNode* SingleRotateWithRight(struct AVLNode* t);
struct AVLNode* DoubleRotateWithRight(struct AVLNode* t);
struct AVLNode* SingleRotateWithLeft(struct AVLNode* t);
struct AVLNode* DoubleRotateWithLeft(struct AVLNode* t);
struct AVLNode* search(struct AVLNode* t, float weight);
void displayIndex(struct AVLNode* t);
void heaviestFish(struct AVLNode* t);
struct AVLNode* longestFishHelper(struct AVLNode* t, float* longest, struct AVLNode* longest_traverse);
void longestFish(struct AVLNode* t, float* longest);