#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum { diploma = 0, bachelor, master, doctor } education;
// A struct for nodes of the linked list.
struct container {
    struct person *plink;	// points to a struct person.
    struct container *next;
};

// A struct to hold attributes of a person
struct person {
    char name[32];
    char email[32];
    int phone;
    education degree;
};
void branching(char c, struct container** pointerToHead); 	// given
char* get_name();	// given
void printFirst(struct container* root); 	// given
int insertion(struct container** pointerToHead); 	// Question 1
struct container* search(struct container* root, char* sname); 	// Question 2
void deleteFirst(struct container** pointerToHead); 	// Question 3
void deleteAll(struct container** pointerToHead); 	// Question 4
void printAll(struct container* root);	// Question 5

int main()
{
    struct container* head = NULL; // Declare head as a local variable of main function
    // Print a menu for selection
    char ch = ' ';
    do {
        printf("Enter your selection\n");
        printf("\ti: insert a new entry\n");
        printf("\td: delete one entry\n");
        printf("\tr: delete all entries\n");
        printf("\ts: search an entry\n");
        printf("\tp: print all entries\n");
        printf("\tq: quit \n");
        fflush(stdin);// Flush the input buffer.
        ch = getchar();
        ch = tolower(ch);	// Convert any uppercase char to lowercase.
        branching(ch, &head);
        printf("\n");
    } while (ch != 113);			// 113 is 'q' in ASCII
    return 0;
};

// Branch to different tasks: insert a person, search for a person, delete a person
// print all added persons.
void branching(char c, struct container** pointerToHead)
{
    char *p;
    switch (c) {
        case 'i':
            insertion(pointerToHead);
            break;
        case 's':
            p = get_name();
            search(*pointerToHead, p);
            break;
        case 'd':
            deleteFirst(pointerToHead);
            break;
        case 'r':
            deleteAll(pointerToHead);
            break;
        case 'p':
            printAll(*pointerToHead);
            break;
        case 'q':
            deleteAll(pointerToHead); // free all memory
            break;
        default:
            printf("Invalid input\n");
    }
};
// Read the input from the user.
char * get_name()
{
    char *p = (char *) malloc(32); // Use dynamic memory which does not go out of scope
    printf("Please enter a name for the search: ");
    scanf("%s", p);
    return p;
};
void printFirst(struct container* root)
{
    if (root != NULL)
    {
        
        printf("\n\nname = %s\n", root->plink->name);
        printf("email = %s\n", root->plink->email);
        printf("phone = %d\n", root->plink->phone);
        switch (root->plink->degree)
        {
            case diploma:
                printf("degree = diploma\n");
                break;
                
            case bachelor:
                printf("degree = bachelor\n");
                break;
                
            case master:
                printf("degree = master\n");
                break;
                
            case doctor:
                printf("degree = doctor\n");
                break;
                
            default:
                printf("System Error: degree information corruption.\n");
                break;
                
        }
    }
};
int insertion(struct container** pointerToHead)
{
    struct container *container;
    container = (struct container *) malloc(sizeof(struct container));
    struct person *person;
    person = (struct person *) malloc(sizeof(struct person));
    
    printf("Enter name, phone, email, degree (0-3):\n");
    scanf("%s", person->name);
    scanf("%d", &person->phone);
    scanf("%s", person->email);
    scanf("%d", &person->degree);
    
    container->plink = person;
    container->next = *pointerToHead;
    *pointerToHead = container;
    return 0;
};

struct container* search(struct container* root, char* sname)
{
    struct container *p = root, *b = NULL;
    while (p != NULL)
    {
        if (strcmp(sname, p->plink->name) == 0) {
            printf("%s\n", p->plink->name);
            printf("%d\n", p->plink->phone);
            printf("%s\n", p->plink->email);
            printf("%d\n", p->plink->degree);
            return b;
        }
        else
        {
            b = p;
            p = p->next;
        }
    }
    return 0;
};
void deleteFirst(struct container** pointerToHead)
{
    if (&(*pointerToHead) != NULL)
    {
        struct container *newHead = (*pointerToHead)->next;
        free((*pointerToHead)->plink);
        free((*pointerToHead)->next);
        (**pointerToHead) = *newHead;
    }
};
void deleteAll(struct container** pointerToHead)
{
    if (&(**pointerToHead) == NULL) {
        return;
    }
    else
    {
        deleteAll(&(**pointerToHead).next);
        deleteFirst(pointerToHead);
    }
};
void printAll(struct container *root)
{
    if ((root) == NULL) {
        return;
    }
    else
    {
        printAll(root->next);
        printFirst(root);
    }
};