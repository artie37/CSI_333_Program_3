
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 11
/* Size of char array */
#define COMMAND_SIZE 4
#define COMPARE_TO 3
/* Number of spots to compare command up until */
#define FIRST_COUNT 1
/* Sets count to 1 */

void insert(char[STRING_SIZE]);
void createNewList(char[STRING_SIZE]);
void delete(char[STRING_SIZE]);
void forcedDelete(int);
void insertSort();
void deleteSort();
void printStats();
void printList();
void printCountRange();
void printPrefix();
void printSuffix();

typedef struct LinkedList
{
    char symbol[STRING_SIZE];
    int count;
    
    struct LinkedList *next;
} Node;
/* Struct for nodes of the linked list */

Node *pHead = NULL;
Node *pTail = NULL;

/* Pointers to the node */

int main(void)
{
    char command[COMMAND_SIZE];
    char string[STRING_SIZE];
    char ins[] = "ins";
    char del[] = "del";
    char fde[] = "fde";
    char prl[] = "prl";
    char end[] = "end";
    int val;
    
    printf("Enter a command: "); fflush(stdout);
    scanf("%s", command);
    /*
     * Prompt user to enter a command and
     * input command into string
     */
    
    while (strcmp(command, end) != 0)
    {
        if (strcmp(command, ins) == 0)
        /* Do this if user enters ins for insert */
        {
            scanf("%s", string);
            
            insert(string);
            /* call insert function */
        }
        
        else if (strcmp(command, del) == 0)
        {
            scanf("%s", string);
            
            delete(string);
        }
        
        else if (strcmp(command, fde) == 0)
        {
            scanf("%d", &val);
            
            forcedDelete(val);
        }
        
        else if (strcmp(command, prl) == 0)
        {
            printList();
        }
        
        
        printf("\nEnter a command: "); fflush(stdout);
        scanf("%s", command);
        /* Prompt user to enter a command and
         * input command into string
         */
    }
    
    if (strcmp(command, end) == 0)
    {
        printf("\nProgram Closing\n");
    }
}

void insert(char string[STRING_SIZE])
{
    Node *pNewNode = malloc(sizeof(Node));
    Node *pLoop = pHead;
    
    if (pHead == NULL)
    /*
     * Check to see if head node is pointing to null.
     * If pHead is pointing to null, that means
     * there are no nodes and a new list needs to
     * be created.
     */
    {
        createNewList(string);
    }
    
    else
    {
        strcpy(pNewNode -> symbol, string);
        
        if (pHead == pTail)
        /*
         * Check to see if the that is about to be
         * inserted is the second node.
         * If head and tail refer to eachother, that means
         * that pNewNode is the second node.
         */
        {
            if (strcmp(pHead -> symbol, pNewNode -> symbol) == 0)
            {
                pHead -> count++;
            }
            
            else
            {
                pNewNode -> count = FIRST_COUNT;
                pHead -> next = pNewNode;
                /* Have the head node point to the new node */
                pTail = pNewNode;
                /* Insert the new node into tail */
                
                pNewNode -> next = NULL;
                /* Remove the new from the list */
            }
        }
        
        else
        /*
         * This runs if the new node is not
         * the second node.
         */
        {
            while (pLoop != NULL)
            {
                if (strcmp(pLoop -> symbol, pNewNode -> symbol) == 0)
                {
                    pLoop -> count++;
                    break;
                }
                
                else if (pLoop -> next == NULL)
                {
                    pNewNode -> count = FIRST_COUNT;
                    pTail -> next = pNewNode;
                    /* Point the tail node to the new node */
                    pNewNode -> next = NULL;
                    /* Remove the new node frome the list */
                    pTail = pNewNode;
                    /* Insert the new node into tail */
                    break;
                }
                
                pLoop = pLoop -> next;
            }
        }
        
        insertSort();
        
    }
}

void createNewList(char string[STRING_SIZE])
/* Function to create a new list */
{
    Node *pNewNode = malloc(sizeof(Node));
    /*
     * Creates new node to be inserted
     * into the linked list.
     */
    
    pNewNode -> next = NULL;
    
    strcpy(pNewNode -> symbol, string);
    /* Insert user's string into node */
    pNewNode -> count = FIRST_COUNT;
    pHead = pTail = pNewNode;
    
    /*
     * When there is one node
     * all nodes must refer to eachother
     */
}

void delete(char string[STRING_SIZE])
/* Function to delete a node */
{
    Node *pCurr = pHead;     
    Node *pPrev = NULL;
    Node *pDel = NULL;
    /*
     * *pCurr is a pointer to the head node.
     * *pPrev is a pointer that will reference
     * the node before it. This will be used to
     * delete the current node by linking the
     * previous node to the next node.
     */
    
    while (pCurr != NULL)
    /*
     * Loop through the linked list until
     * the nodes address is null. This is
     * the end of the linked list.
     */
    {
        if (strcmp(pCurr -> symbol, string) == 0)
        {
            if (pCurr -> count > 1)
            {
                pCurr -> count--;
            }
            
            else
            {
                if (pCurr == pHead)
                /*
                 * Checks to see if the node that is
                 * going to be delete is the head node.
                 */
                {
                    pHead = pCurr -> next;
                    /*
                     * Remove the head node by setting the
                     * address of the head node to the second node.
                     * The second node becomes the head node.
                     */
                    pDel = pCurr;
                    free(pDel);
                    /*
                     * Free original head node from memory.
                     */
                }
                
                else
                /*
                 * Used if node to be deleted is not the head node.
                 */
                {
                    if ((pPrev == pHead) && (pCurr -> next == NULL))
                    /*
                     * Checks to see if this is the second node in
                     * the linked list when there are only 2 nodes.
                     */
                    {
                        pTail = pHead;
                        pHead -> next = NULL;
                        /*
                         * Make tail = head to allow input after the
                         * second node is deleted and only the head node remains.
                         * If this is not done, the linked list will not
                         * allow the user to input any more nodes. This happens
                         * because there is a test in the insert function to
                         * see if the node that is about to be input into the
                         * list is the second node, and this makes it true. If
                         * thats tests true, the head node can reference the new
                         * node making it the second node.
                         */
                    }
                    
                    else if (pCurr -> next == NULL)
                    {
                        pTail = pPrev;
                        pTail -> next = NULL;
                        pDel = pCurr;
                        free(pDel);
                    }
                    
                    else
                    {
                        
                        pPrev -> next = pCurr -> next;
                        /*
                         * Remove the reference to the current node
                         * by making the previous node reference next node.
                         * This will remove the node from the list.
                         */
                        pDel = pCurr;
                        free(pDel);
                        /*
                         * Free removed node from memory.
                         */
                    }
                }
            }
        }
        
        pPrev = pCurr;
        pCurr =  pCurr -> next;
    }
}

void printList()
{
    Node *pCurr = pHead;
    
    if (pHead == NULL)
    {
        printf("The list is empty.\n"); fflush(stdout);
    }
    
    else
    {
        printf("\nStrings Entered:\n"); fflush(stdout);
        
        while (pCurr != NULL)
        {
            printf("%s", pCurr -> symbol);
             printf(" %d\n", pCurr -> count);
            
            pCurr = pCurr -> next;
        }
        
        
    }
}

//function to delete nodes based on count
void forcedDelete(int min){
    
    //  printf("\n%s", "fde1");
    
    Node *pCurr = pHead;
    
    int nodeCount;
    
    while(pCurr != NULL){
        
        nodeCount = pCurr -> count;
        if (nodeCount <= min){
            
            while(nodeCount > 0){
                
                nodeCount--;
                delete(pCurr -> symbol);
            }
            
        }
        pCurr = pCurr -> next;
    }
    
}

void insertSort()
{
    Node *pCurr = pHead;
    Node *pNext = NULL;
    
    while (pCurr != NULL)
    {
        pNext = pCurr -> next;
        
        pHead = pCurr -> next;
        
        
        pCurr = pCurr -> next;
        
        if ((pNext -> count >= pCurr -> count) ||(pNext == NULL))
        {
            printf("List Sorted\n");
            break;
        }
    }
}



