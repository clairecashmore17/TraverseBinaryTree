
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct binarySearchNode{
   char userValue;
   char userString[10];
   struct binarySearchNode* right;
   struct binarySearchNode* left;
} BSTN; //BSTN = Binary Search Node

typedef struct binarySearchTreeptrToStack{
   struct binarySearchTreeptrToStack* next;
   BSTN* addressOfBSTN;
}top;

void insert(BSTN** BST, BSTN* ptrToNewTemp);
void inorder(BSTN** BST, top* ptrToStack);
void preorder(BSTN** BST, top* ptrToStack);
void find(BSTN** BST, top* ptrToStack, char userInput);
void push(BSTN* traversePoint, top** ptrToPtrToStack);
BSTN* pop(top** ptrToPtrtoStack);
int stackIsEmpty(top *ptrToStack);

int main(){
   BSTN* BST = NULL; //BST = Binary Search Tree
   BSTN* temp = NULL;
   top* ptrToStack = NULL;
   char userChar;
   char userCharString[10];
   
   printf("Enter an i to insert, a f to traverse, and a q to exit: ");
 
   
   scanf(" %c",&userChar);
   
   while(userChar != 'q'){
      if(userChar == 'i'){
         printf("\nEnter a character to be inserted: ");
         scanf(" %c",&userChar);
         printf("Enter a string: ");
         scanf("%s",userCharString);
         
         temp = malloc(sizeof(BSTN));
         temp->userValue = userChar;
         strcpy(temp->userString,userCharString);
         
         insert(&BST, temp);
         preorder(&BST, ptrToStack);
         inorder(&BST, ptrToStack);
      }
      else if((userChar == 'f') && (BST == NULL)){
         printf("\nEmpty List\n\n");
      }
      else if(userChar == 'f'){
         printf("Enter a character to be found: ");
         scanf(" %c",&userChar);
         find(&BST, ptrToStack, userChar);
      }
      else{
         printf("\nInvalid operation.\n\n");
      }

      printf("\nEnter an i to insert, an f to find, and a q to exit: ");
      
      scanf(" %c",&userChar);
   }
   
   return 0;
}

void insert(BSTN** BST, BSTN* temp){
   BSTN* traversePointer;
   int traversalFlag = 0;
   if(*BST == NULL){
      *BST = temp;
      (*BST)->left = NULL;
      (*BST)->right = NULL;
   }
   else{
      traversePointer = *BST;
      while(traversalFlag != 1 ){
         if((traversePointer->right == NULL) && (traversePointer->left == NULL)){
            if(traversePointer->userValue > temp->userValue)
               traversePointer->left = temp;
            else
               traversePointer->right = temp;
            traversalFlag = 1;
         }
         else if((traversePointer->right != NULL) && (traversePointer->left == NULL)){
            if(traversePointer->userValue > temp->userValue){
               traversePointer->left = temp;
               traversalFlag = 1;
            }
            else
               traversePointer = traversePointer->right;
         }
         else if((traversePointer->right == NULL) && (traversePointer->left != NULL)){
            if(traversePointer->userValue < temp->userValue){
               traversePointer->right = temp;
               traversalFlag = 1;
            }
            else
               traversePointer = traversePointer->left;
         }
         else{
            if(traversePointer->userValue > temp->userValue)
               traversePointer = traversePointer->left;
            else
               traversePointer = traversePointer->right;
         }
      }
   }
}

void find(BSTN** BST, top* ptrToStack, char findChar){
   BSTN* traversePointer;
   int findFlag = 0;
   traversePointer = *BST;
   while((findFlag != 1) && (traversePointer != NULL)){
         if(traversePointer->userValue == findChar){
            printf("Found this: %s\n", traversePointer->userString);
            findFlag = 1;
         }
         else if(traversePointer->userValue < findChar)
            traversePointer = traversePointer->right;
         else
            traversePointer = traversePointer->left;
   }
   if(findFlag ==0)
      printf("Could not find %c\n", findChar);
}

void preorder(BSTN** BST, top* ptrToStack){
   BSTN* traversePointer = *BST;
   int finishedFlag = 0;
   printf("\nPreorder traversal:");
   while(finishedFlag != 1){
      while(traversePointer != NULL){
         printf(" %c ",traversePointer->userValue);
         if(traversePointer->left != NULL){
            push(traversePointer, &ptrToStack);
            traversePointer = traversePointer->left;
         }
         else{
            traversePointer = traversePointer->right;
         }
      }
      if(ptrToStack == NULL){
         finishedFlag = 1;
         putchar('\n');
      }
      else{
         traversePointer = pop(&ptrToStack);
         traversePointer = traversePointer->right;
      }
   }
}

void inorder(BSTN** BST, top* ptrToStack){
   BSTN* traversePointer = *BST;
   int finishedFlag = 0;
   printf("\ninorder traversal:");
   while(finishedFlag != 1){
      while(traversePointer != NULL){
         if(traversePointer->left != NULL){
            push(traversePointer, &ptrToStack);
            traversePointer = traversePointer->left;
         }
         else{
            printf(" %c ",traversePointer->userValue);
            traversePointer = traversePointer->right;
         }
      }
      if(ptrToStack == NULL){
         finishedFlag = 1;
         putchar('\n');
      }
      else{
         traversePointer = pop(&ptrToStack);
         printf(" %c ",traversePointer->userValue);
         traversePointer = traversePointer->right;
      }
   }
}

void push(BSTN* traversePointer, top** ptrToStack){
   top* temp;
   temp = (top*) malloc(sizeof(BSTN));
   if(temp){
      temp->addressOfBSTN = traversePointer;
      temp->next = *ptrToStack;
      *ptrToStack = temp;
   }
}

BSTN* pop(top** ptrToStack){
   BSTN* temp;
   if(*ptrToStack){
      temp = (*ptrToStack)->addressOfBSTN;
      *ptrToStack = (*ptrToStack)->next;
   }
   return temp;
}
