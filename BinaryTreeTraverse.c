// Claire Cashmore
// CS315 Homework
// Traversal through a BST
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct binarySearchTreeNode{
  char userValue;
  char userString[10];
  struct binarySearchTreeNode *right;
  struct binarySearchTreeNode *left;
}BSTN;

typedef struct binarySearchTreeStack{
  struct binarySearchTreeStack *next;
  BSTN* addressOfBSTN;
}top;

void insert(BSTN** BST, BSTN* ptrToNewTemp);
void inorder(BSTN** BST, top* ptrToStack);
void preorder(BSTN** BST, top* ptrToStack);
void find(BSTN** BST, top* ptrToStack, char userInput);
void push(BSTN* traversePoint, top** ptrToPtrToStack);
BSTN* pop(top** ptrToPtrtoStack);

int stackIsEmpty(top *stack);

int main(){
   BSTN *BST = NULL;
   BSTN *ptrToNewTemp = NULL;
   top* stack = NULL;
   char userChar = 'o';
   char userString[10];
   
   printf("Select an option: i for insert, f for Find, q for Quit: ");
   scanf(" %c", &userChar);
   
     while(userChar != 'q'){
       if(userChar == 'i'){
         printf("Enter a character to be inserted: ");
         scanf(" %c",&userChar);
         printf("Enter a string: ");
         scanf("%s", &userString);
              
         ptrToNewTemp = malloc(sizeof(BSTN));
         ptrToNewTemp->userValue = userChar;
         strcpy(ptrToNewTemp->userString,userString);
         
         insert(&BST, ptrToNewTemp);
         preorder(&BST, stack);
         inorder(&BST, stack);  
         
       }
       else if((userChar == 'f')&&(BST == NULL)){
         printf("\n Your list is empty \n");
       }
       else if(userChar =='f'){
         printf("Enter the character you wish to find: ");
         scanf(" %c", &userChar);
         find(&BST,stack,userChar);
       }
       else{
         printf("\nNot an option. Try Again.\n");
       }
        printf("Select an option: i for insert, f for Find, q for Quit: ");
        scanf(" %c", &userChar);
     }
}


void insert(BSTN** PointerToPointerToBST, BSTN* ptrToNewTemp){
  // Create traverse pointer
  BSTN* traversePointer;
  //Create a flag for the traversal
  int travFlag = 0;
  
  //If the binary search tree is empty
  if(*PointerToPointerToBST == NULL){
    *PointerToPointerToBST = ptrToNewTemp;
    // Make children nodes NULL
    (*PointerToPointerToBST)->left = NULL;
    (*PointerToPointerToBST)->right = NULL;
  }
  else{
    traversePointer = *PointerToPointerToBST;
    while(travFlag != 1){
      //Case nothing has been put in the left OR right node
      if((traversePointer->right ==NULL)&&(traversePointer->left == NULL)){
        if(traversePointer->userValue > ptrToNewTemp->userValue)
          traversePointer->left = ptrToNewTemp;
        else
          traversePointer->right = ptrToNewTemp;
        
        //SET OUR FLAG TO FINISH TRAVERSE  
        travFlag = 1;
      }
      //CASE: Nothing in the LEFT NODE
      else if((traversePointer->right != NULL) && (traversePointer->left == NULL)){
        if(traversePointer->userValue >ptrToNewTemp->userValue){
          traversePointer->left = ptrToNewTemp;
        }
        else
        traversePointer = traversePointer->right;
        
        // SET OUR FLAG TO FINISH TRAVERSE
        travFlag = 1;
      }
      // CASE: nothing in RIGHT NODE
      else if((traversePointer->right == NULL) && (traversePointer->left != NULL)){
        if(traversePointer->userValue < ptrToNewTemp->userValue){
          traversePointer->right = ptrToNewTemp;
        }
        else 
        traversePointer= traversePointer->left;
        
        //SET OUR FLAG
        travFlag = 1;
      }
      //CASE:
      else{
        if(traversePointer->userValue > ptrToNewTemp->userValue)
          traversePointer = traversePointer->left;
        else
          traversePointer = traversePointer->right;
      }
    }
  }
}
//FIND FUNCTION
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

// PREORDER IS VISIT, LEFT, RIGHT
void preorder(BSTN** BST, top* ptrToStack){
  BSTN* traversePointer = *BST;
  int endFlag = 0;
  printf("Current Preorder traversal: ");
  while(endFlag != 1){
    while(traversePointer != NULL){
      // Print out the value we visited
      printf( " %c ", traversePointer->userValue);
      
      //CASE: LEFT IS NOT EMPTY
      if(traversePointer->left != NULL){
      //Move the pointer to the left child and push
        push(traversePointer, &ptrToStack);
        traversePointer = traversePointer->left;
      }
      // CASE: LEFT IS EMPTY
      else{
      // Move pointer to the right child
        traversePointer = traversePointer->right;
      }
    }
    //If we now have NULL, end the preorder
    if(ptrToStack == NULL){
      endFlag = 1;
      putchar('\n');
    }
    else{
      traversePointer = pop(&ptrToStack);
      traversePointer =  traversePointer->right;
    }
  }
  
}

//IN ORDER IS LEFT, VISIT, RIGHT
void inorder(BSTN** BST, top* ptrToStack){
  BSTN* traversePointer = *BST;
   int endFlag = 0;
   printf("\nCurrent inorder traversal:");
   while(endFlag != 1){
      while(traversePointer != NULL){
      // CASE: LEFT CHILD IS NOT EMPTY
         if(traversePointer->left != NULL){
         // Push and move pointer to left
            push(traversePointer, &ptrToStack);
            traversePointer = traversePointer->left;
         }
         //CASE: LEFT IS EMPTY
         else{
           // VISIT NODE
            printf(" %c ",traversePointer->userValue);
            traversePointer = traversePointer->right;
         }
      }
      if(ptrToStack == NULL){
         endFlag = 1;
         putchar('\n');
         
      }
      else{
         traversePointer = pop(&ptrToStack);
         printf(" %c ",traversePointer->userValue);
         traversePointer = traversePointer->right;
      }
   }
}


void push(BSTN* traversePointer, top** ptrToPtrToStack){
  top* temp;
  temp = (top*) malloc(sizeof(BSTN));
  
  if(temp){
  temp->addressOfBSTN = traversePointer;
  temp->next = *ptrToPtrToStack;
  *ptrToPtrToStack = temp; 
  }
}
BSTN* pop(top** ptrToPtrToStack){
  BSTN* temp;
  if(*ptrToPtrToStack){
    temp = (*ptrToPtrToStack)->addressOfBSTN;
    *ptrToPtrToStack = (*ptrToPtrToStack)->next;
  }
  return temp;
}
