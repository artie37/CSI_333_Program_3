/*
 * Program 3
 *
 * Arthur Knapp
 * ID: ak146316
 * Scott Nearing
 * ID: sn379745
 * Lab: Wednesday 9:20
 *
 * This program has the user input strings into a linked list and with each new string,
 * there is a count that goes along with the string that is set to one.
 *
 * If the user entersmore than one of the same string, the node that holds the will 
 * have its count incremented by one instead of being inserted again. 
 * 
 * The program also has functions that can insert strings, delete strings, force delete strings,
 * print the list, print various stats about the list, print a range of
 * strings based on the counts, search the list and print a string based on
 * the prefix, and search the list and print a string based on a given suffix.
 * 
 * LIST OF FUNCTIONS EACH TEAM MEMBER DID:
 *
 * main: Scott Nearing
 * insert: Arthur Knapp
 * delete: Arthur Knapp
 * forcedDelete: Scott Nearing
 * sortList: Arthur Knappp 
 * printStats: Scott Nearing
 * printList: Arthur Knapp
 * printByCount: Scott Nearing
 * printPrefix: Arthur Knapp
 * printSuffix: Scott Nearing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 11
/* Size of char array for the string */

#define COMMAND_SIZE 4
/* Size of char array for the command*/
#define PREFIX_SIZE 11
/* Size of char array for prefix */

#define SUFFIX_SIZE 11
/* Size of char array for suffix */

#define COMPARE_TO 3
/* Number of spots to compare command up until */

#define FIRST_COUNT 1
/* Sets count to 1 */

#define SORT 1
/* Used to determine whether to sort list or not */

#define DONT_SORT 0
/* Used to determine whether to sort list or not */

#define LARGE_NUM 100000
/* Array size for int array for count in printStats */

#define ONE 1
/* Used in calculations */

/* Function Prototypes */
void insert(char[STRING_SIZE]);
void createNewList(char[STRING_SIZE]);
void delete(char[STRING_SIZE], int);
void forcedDelete(int);
void sortList();
int  printStats();
void printList();
int  printByCount(int, int);
void printPrefix(char[PREFIX_SIZE]);
void printSuffix(char[SUFFIX_SIZE]);
/* Function Prototypes */
/* Explainations are within the function themselves */

typedef struct LinkedList
/* Structrure definition for the linked list nodes */
{
    char symbol[STRING_SIZE]; /* String in node */
    int count; /* Count of node */
    
    struct LinkedList *next;
} Node;
/* Struct for nodes of the linked list */

Node *pHead = NULL;
/* Pointer to head node */
Node *pTail = NULL;
/* Pointer to tail node */

/* Pointers to the node */

int main(void)
/* Main function */
{
    char command[COMMAND_SIZE];
    /* char array to store command */
    char string[STRING_SIZE];
    /* char array to store string */
    char ins[] = "ins";
    /* string command ins to commpare */
    char del[] = "del";
    /* string command del to commpare */
    char fde[] = "fde";
    /* string command fde to commpare */
    char prl[] = "prl";
    /* string command prl to commpare */
    char end[] = "end";
    /* string command end to commpare */
    char pcr[] = "pcr";
    /* string command pcr to commpare */
    char pst[] = "pst";
    /* string command pst to commpare */
    char ppr[] = "ppr";
    /* string command ppr to commpare */
    char psu[] = "psu";
    /* string command psu to commpare */
    char pre[PREFIX_SIZE];
    /* char array for user entered prefix */
    char suf[SUFFIX_SIZE];
    /* char array for user entered suffix */
    int val;
    /* value to print range */
    int val2;
    /* value to print range */
    
    printf("Enter a command: "); fflush(stdout);
    scanf("%s", command);
    /*
     * Prompt user to enter a command and
     * input command into string
     */
    
    while (strcmp(command, end) != 0)
    /* Run while command doesn't equal "end" */
    {
        if (strcmp(command, ins) == 0)
        /* Do this if user enters ins for insert */
        {
            scanf("%s", string);
            /* input string */
            insert(string);
            /* call insert function */
        }
        
        else if (strcmp(command, del) == 0)
        /* Do this if user enters del */
        {
            scanf("%s", string);
            /* input string */
            delete(string, SORT);
            /* call delete function */
        }
        
        else if (strcmp(command, fde) == 0)
        /* Do this if user enters fde */
        {
            scanf("%d", &val);
            /* input int to force delete from */
            forcedDelete(val);
            /* call forcedelete function */
        }
        
        else if (strcmp(command, prl) == 0)
        /* Do this if user enters prl */
        {
            printList();
            /* call printList function */
        }
        
        else if (strcmp(command, pcr) == 0)
        /* Do this if user enters pcr */
        {
            scanf("%d", &val);
            /* input int to print count from */
            scanf("%d", &val2);
            /* input int to print count up until */
            printByCount(val, val2);
            /* call printByCount function */
        }
        
        else if (strcmp(command, pst) == 0)
        /* Do this if users enters pst */
        {
            printStats();
            /* Call printStats function */
        }
        
        else if (strcmp(command, ppr) == 0)
        /* Do this if user enters ppr */
        {
            scanf("%s", pre);
            /* input string into prefix variable */
            printPrefix(pre);
            /* call printPrefix function */
        }
        
        else if (strcmp(command, psu) == 0)
        /* Do this if user enters psu */
        {
            scanf("%s", suf);
            /* input string into suffix variable */
            printSuffix(suf);
            /* call printSuffix function */
        }
        
        printf("\nEnter a command: "); fflush(stdout);
        scanf("%s", command);
        /* Prompt user to enter a command and
         * input command into string
         */
    }
    
    if (strcmp(command, end) == 0)
    /* Do this if user inputs "end" */
    {
        printf("\nProgram Closing\n"); fflush(stdout);
    }
}

void insert(char string[STRING_SIZE])
{
/*
 * This function inserts nodes into the linked list.
 * At the end of the function, the sort list function 
 * will be called and the list will be sorted.
 */

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
        /* Call create newList function */
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
            /* Do this if the second node being input equals head node */
            {
                pHead -> count++;
                /* Increment head count by one */
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
            /* run while node does not equal null */
            {
                if (strcmp(pLoop -> symbol, pNewNode -> symbol) == 0)
                /* Do this if new node symbol equals current node symbol */
                {
                    pLoop -> count++;
                    /* Increment current node count by one */
                    break;
                    /* break out of loop */
                }
                
                else if (pLoop -> next == NULL)
                /* Do this if next node equals null */
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
                /* increment linked list */
            }
        }
        
        sortList();
        /* call sortList function */
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

void delete(char string[STRING_SIZE], int sort)
/* Function to delete a node */
{
    Node *pCurr = pHead;
    Node *pPrev = NULL;
    /*
     * *pCurr is a pointer to the head node.
     * *pPrev is a pointer that will reference
     * the node before it. This will be used to
     * delete the current node by linking the
     * previous node to the next node.
     */
    
    if (pHead == NULL)
    {
        printf("This List Is Empty\n"); fflush(stdout);
    }
    
    while (pCurr != NULL)
    /*
     * Loop through the linked list until
     * the nodes address is null. This is
     * the end of the linked list.
     */
    {
        if (strcmp(pCurr -> symbol, string) == 0)
        /* Do this if the current nodes symbol equals user inputed string */
        {
            if (pCurr -> count > 1)
            /* If current node has a count greater than one*/
            {
                pCurr -> count--;
                /* Decrement current node count by one */
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
                    free(pCurr);
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
                    /* If the next node equals null */
                    {
                        pTail = pPrev;
                        /* Make tail node the previous node */
                        pTail -> next = NULL;
                        /* Have tail reference null */
                        free(pCurr);
                        /* free current node from memory */
                    }
                    
                    else
                    {
                        pPrev -> next = pCurr -> next;
                        /*
                         * Remove the reference to the current node
                         * by making the previous node reference next node.
                         * This will remove the node from the list.
                         */
                        free(pCurr);
                        /*
                         * Free removed node from memory.
                         */
                    }
                }
            }
        }
        
        pPrev = pCurr;
        /* have the current node equal previous node */
        pCurr =  pCurr -> next;
        /* Increment current node */
    }
    
    if (sort == 1)
    /* 
     * If sort equals 1 run sort function.
     * The sort function will not be called 
     * if forcedDelete is called.
     */
    {
        sortList();
        /* Call sortList function */
    }
}

void printList()
/* printList function */
{
    Node *pCurr = pHead;
    
    if (pHead == NULL)
    /* If head node equals null */
    {
        printf("The list is empty.\n"); fflush(stdout);
    }
    
    else
    {
        printf("\nStrings Entered:\n"); fflush(stdout);
        
        printf("\n"); fflush(stdout);
        
        while (pCurr != NULL)
        /* run while current node isn't null */
        {
            printf("%s", pCurr -> symbol); fflush(stdout);
            printf(" %d\n", pCurr -> count); fflush(stdout);
            /* Print symbol and count from current node */
            
            pCurr = pCurr -> next;
            /* Move to next node */
        }
        
        
    }
}

void forcedDelete(int min)
/* function to delete nodes based on count */
{
    Node *pCurr = pHead;
    
    int nodeCount;
    
    if (pHead == NULL)
    {
        printf("This List Is Empty\n"); fflush(stdout);
    }
    
    while(pCurr != NULL)
    /* run while current node isn't null */
    {
        nodeCount = pCurr -> count;
        /* insert current nodes count into int variable */
        if (nodeCount <= min)
        /* if nodeCount is less than min */
        {
            while(nodeCount > 0)
            /* Run while nodeCount is greater than zero */
            {
                nodeCount--;
                /* decrement nodeCount by one */
                delete(pCurr -> symbol, DONT_SORT);
                /* Call delete function with current symbol and don't sort list */
            }
            
        }
        pCurr = pCurr -> next;
        /* move to next node */
    }
    
}

void sortList()
/* Function to sort the list */
{
    Node *pCurr = pHead;
    Node *pNext = NULL;
    Node *pPrev = NULL;

    while (pCurr != NULL)
    /* Run while current node isn't null */
    {
        pNext = pCurr -> next;
        /* set the next node */
        
        if (pPrev == NULL)
        /* Check to see if it the head node */
        {
            if (pNext == NULL);
            /* if next equals null, */
            else if (pCurr -> count < pNext -> count)
            {
                if (pNext -> next == NULL)
                /*
                 * If there are only 2 nodes in the linked list
                 */
                {
                    pCurr -> next = pNext -> next;
                    /* Set current reference to next reference */
                    pHead = pNext;
                    /* Set next node equal to head */
                    pTail = pCurr;
                    /* Set current equal to tail */
                    pHead -> next = pTail;
                    /* have head node reference tail */
                }
                
                else
                /*
                 * If there are more than 2 nodes in the linked list
                 */
                {
                    pCurr -> next = pNext -> next;
                    /* Set current reference to next referenec */
                    pHead = pNext;
                    /* Set next node equal to head */
                    pHead -> next = pCurr;
                    /* have head equal current node */
                    sortList();
                    /* call sortList again to continue sorting */
                }
            }
        }
        
        else if (pNext == NULL)
        /* Do this if next node equals null */
        {
            break;
            /* break out of loop */
        }
        
        
        else if (pCurr -> count < pNext -> count)
        /* do this if current count is less than next count */
        {
            if (pNext -> next == NULL)
            /*
             * If there are only 2 nodes in the linked list
             */
            {
                pCurr -> next = pNext -> next;
                /* have current node reference the node next is pointing to */
                pPrev -> next = pNext;
                /* have previous node reference the next node */
                pTail = pCurr;
                /* insert current node into tail node */
                pNext -> next = pCurr;
                /* have next node reference current node */
                sortList();
                /* call sortList function to continue sorting list */
            }
            
            else
            {
                pPrev -> next = pNext;
                /* have previous node reference next node */
                pCurr -> next = pNext -> next;
                /* have current node reference node the next node is referencing */
                pNext -> next = pCurr;
                /* have next node reference the current node */
                sortList();
                /* call sortList function to continue sorting list */
            }
        }
        
        pPrev = pCurr;
        /* have previous node equal current node */
        pCurr = pCurr -> next;
        /* move to next node */
    }
}



int printByCount(int v1, int v2)
/* function to print out nodes between the range of the inputed count values */
{
    Node *pCurr;
    /* node pointer for current node */
    int nodeCount;
    /* int variable for node count */
    
    if(pHead == NULL)
    /* do this if head is null */
    {
        printf("%s\n","The list is empty"); fflush(stdout);
        return 0;
        /* leave function */
    }
    
    pCurr = pHead;
    
    printf("\n"); fflush(stdout);
    while(pCurr != NULL)
    /* loop through list while current doesn't equal null */
    {
        nodeCount = pCurr -> count;
        /* insert current node count into nodeCount variables */
        if(nodeCount >= v1 && nodeCount <= v2)
        /* 
         * Do this if nodeCount is greater than or equal to
         * v1 and if node count is less than or equal to v2 
         */
        {
            printf("%s",pCurr -> symbol); fflush(stdout);
            printf(" %d\n", pCurr -> count); fflush(stdout);
            /* print node */
        }
        
        pCurr = pCurr -> next;
        /* move to next node */
    }
    
    return 0;
}


int printStats()
/* function to print stats of nodes */
{
    
    Node *pCurr;
    /* pointer to current node */
    int min = LARGE_NUM;
    /* minimum value */
    int max = 0;
    /* max value */
    double mean = 0;
    /* mean value */
    int numCount = 0;
    /* count value */
    int nodeCount;
    /* count value */
    int numCount2;
    /* count value */
    int allCounts[LARGE_NUM];
    /* array of all counts */
    
    
    if(pHead == NULL)
    /* if list is empty */
    {
        printf("%s\n","The list is empty."); fflush(stdout);
        return 0;
        /* leave function */
    }
    
    pCurr = pHead;
    /* insert head node into current */
    
    while(pCurr != NULL)
    /* run while there are nodes in the linked list */
    {
        nodeCount = pCurr -> count;
        /* set nodeCount to current count */
        numCount++;
        /* increment numCount by one */
        
        if(nodeCount > max)
        /* if nodeCount is greater than the max value */
        {
            max = nodeCount;
            /* Set max value to current nodeCount */
        }
        
        if(nodeCount < min)
        /* If nodeCount is less than the max value */
        {
            min = nodeCount;
            /* Set min value to current nodeCount */
        }
        
        
        allCounts[numCount - ONE] = nodeCount;
        /* Insert nodeCount into allCounts array at next available position */
        
        
        pCurr = pCurr -> next;
        /* Set current node to next node */
    }
    
    numCount2 = numCount;
    /* Insert numCount into numCount2 */
    
    while(numCount2 > -ONE)
    /* run while numCount2 is greater than negative one */
    {
        mean = mean + allCounts[numCount2 - ONE];
        /* adds total count to mean to be calculated */
        numCount2--;
        /* decrement numCount2 by one */
    }
    
    mean = mean / numCount;
    /* Calculates mean */
    
    printf("\n"); fflush(stdout);
    printf("%s","The number of nodes in the list: "); fflush(stdout);
    printf("%d\n",numCount); fflush(stdout);
    /* Prints the number of nodes in the list */
    printf("%s","The maximum count in the list: "); fflush(stdout);
    printf("%d\n",max); fflush(stdout);
    /* Prints the maximum count in the list */
    printf("%s","The minimum count in the list: "); fflush(stdout);
    printf("%d\n",min); fflush(stdout);
    /* prints the minimum count in the list */
    printf("%s","The mean of the list's count values: "); fflush(stdout);
    printf("%f\n",mean); fflush(stdout);
    /* prints the mean of all the counts in the list */
    return 0;
    /* return to main function */
}

void printPrefix(char pre[PREFIX_SIZE])
/* Function to print prefix */
{
    Node *pCurr = pHead;
    
    if (pHead == NULL)
    /* Run if the list is empty */
    {
        printf("The List Is Empty\n"); fflush(stdout);
    }
    
    else
    {
        printf("\n"); fflush(stdout);
        while (pCurr != NULL)
        {
            if (strstr(pCurr -> symbol, pre) != NULL)
            /* Runs if the prefix the user inputs is in the current node */
            {
                if ((strcspn(pCurr -> symbol, pre) == 0) || (strncmp(pCurr -> symbol, pre, 3) == 0))
                /* 
                 * Runs if the user inputs a single character and that
                 * single character is the first character of the string.
                 * Or it runs if the user enters multiple characters and 
                 * that sequence is found in the string.
                 */
                {
                    printf("%s", pCurr -> symbol); fflush(stdout);
                    printf(" %d\n", pCurr -> count); fflush(stdout);
                    /* Print string and count of string */
                }

            }
            pCurr = pCurr -> next;
            /* move to next node */
        }
    }
}



void printSuffix(char suf[SUFFIX_SIZE])
/*
 * This function takes in a user's string
 * and prints all nodes for which the passed string
 * is a suffix.
 */
{
    int sufLen = 0;
    int symLen = 0;
    int index = 0;
    int nineNineK;
    /* integers used for string manipulations */

    char endSym[LARGE_NUM];
    /* 
     * char array that stores the last n characters of a node's symbol
     * where n is the length of the passed string
     * this is then compared to the passed string to determine if it is a suffix
     */
    
    Node *pCurr;
    /* pointer to a node; this is used to walk across the list */
    
    if(pHead == NULL)
    /* prints "the list is empty if the first node in the list is NULL */
    {
        printf("%s\n", "The list is empty"); fflush(stdout);
    }
    
    else
    {
        pCurr = pHead;
        /* sets node to first node in list */
        
        printf("\n");

        while(pCurr != NULL)
        /* loops while nodes remain */
        {
            index = 0;
            nineNineK = LARGE_NUM - ONE;
            /* resetting variables used to keep track of positions in arrays */
            
            while(nineNineK > - ONE)
            /* this loop sets every position of char array to '\0' */
            {
                endSym[nineNineK] = '\0';
                nineNineK = nineNineK - ONE;
            }
            
            symLen = (int)(strlen(pCurr -> symbol));
            sufLen = (int)strlen(suf);
            /* gets length of symbol and passed string */
            
            while(sufLen > 0)
            /* adds last n characters to new array to compare */
            {
                endSym[index] = pCurr->symbol[symLen-sufLen];
                sufLen = sufLen - 1;
                index = index + 1;
            }
        
            if(strstr(endSym, suf) != NULL)
            /* 
             * if passed string is in new string it is a suffix
             * prints contents of node
             */
            {
                printf("%s",pCurr-> symbol); fflush(stdout);
                printf(" %d\n", pCurr-> count); fflush(stdout);
            }
            
            pCurr = pCurr-> next;
            /* moves to next node in list */
        }
    }
}
