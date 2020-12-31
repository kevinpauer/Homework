#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HA03_linkedListLib.h"

void addListElem(listElement *start)
{

    listElement *new;
    new = (listElement *)malloc(sizeof(listElement));
    if (new == NULL)
    {
        printf("can't reserve storage.\n");
        return;
    }

    listElement *currElem = start;
    while (currElem->nextElem != NULL)
        currElem = currElem->nextElem; // get last elem in list
    currElem->nextElem = new;          // add new to the end of list
    new->nextElem = NULL;

    /* fill data in new element */
    printf("Please enter last name: \n");
    scanf("%s", new->lastName);
    printf("Please enter first name: \n");
    scanf("%s", new->firstName);
    printf("Please enter age: \n");
    scanf("%d", &(new->age));
    printf("end of function\n");
}

void printList(listElement *start)
{
    /* YOUR CODE HERE */
    listElement *currElem = start;
    int counter = 0;
    int position = 1;

    printf("------------------------------\n");
    //check if there are elements added, that can be printed
    if (currElem->nextElem == NULL)
    {
        printf("\nLIST IS EMPTY, PLEASE ADD AN ELEMENT!\n\n");
        return;
    }
    //counter is relevant for future deletion of the object
    //to see position
    counter = getLenOfList(start);
    for (int i = 0; i < counter; i++)
    {
        currElem = currElem->nextElem;
        printf("%d) %s ", position, currElem->lastName);
        printf("%s ", currElem->firstName);
        printf("%d\n", currElem->age);
        position++;
    }
    printf("------------------------------\n");
    /* ---------------*/
}

void delListElem(listElement *start)
{

    /* YOUR CODE HERE */
    int elemPosToDel;
    printList(start);

    if (start->nextElem!=NULL)
    {
        //ask user which element to delete
        printf("Which Element is to be deleted?\n--> ");
        scanf("%d", &elemPosToDel);
        if (elemPosToDel == 0 || elemPosToDel > getLenOfList(start))
        {
            printf("INVALID CHOICE. CHOSE A VALID ELEMENT!\n");
            return;
        }

        listElement *previousElem = start;

        //get element before elemPosToDel
        for (int i = 1; i < elemPosToDel; i++)
        {
            previousElem = previousElem->nextElem;
        }

        //coppel element before elemPosToDel to elem after elemPosToDel 
        listElement *elemDelet = previousElem->nextElem;
        listElement *elemToCoppel = previousElem->nextElem->nextElem;
        previousElem->nextElem = elemToCoppel;

        //free storage
        free(elemDelet);
    }
    /* ---------------*/
}

void delList(listElement *start)
{

    /* YOUR CODE HERE */
    listElement * prev;
    listElement * currentElement = start;
    int lenOfList = getLenOfList(start);

    if (currentElement->nextElem==NULL)
    {
        printf("LIST IS ALREADY EMPTY!\n\n");
        return;
    }
    
    listElement *elemDelet;
    listElement *elemToCopel;

    //free the memory of every element
    for (int i = 0; i < lenOfList; i++)
    {
        currentElement = start;
        prev = currentElement;
        elemDelet = prev->nextElem;
        elemToCopel = prev->nextElem->nextElem;
        prev->nextElem = elemToCopel;

        free(elemDelet);
    }
    
    printf("List successfully deleted!\n\n");
    /* ---------------*/
}

int getLenOfList(listElement *start)
{ // we use this for save list fcn

    int counter = 0;
    listElement *currElem = start;
    while (currElem->nextElem != NULL)
    { // get last elem in list
        currElem = currElem->nextElem;
        counter++;
    }
    return counter;
}

void saveList(listElement *start)
{

    /* YOUR CODE HERE */
    char filename[50];
    int counter;
    char txtFile[] = ".txt";
    FILE *f;
    listElement *currElem = start;

    printf("Enter the filename to open for saving the linkedList \n'*.txt'--> ");
    scanf("%s", filename);

    //build filename
    strcat(filename, txtFile);

    f = fopen(filename, "w");
    if (f == NULL)
    {
        printf("\nUNABLE TO OPEN FILE, PLEASE TRY AGAIN!\n\n");
        return;
    }

    //check if list is empty
    if (currElem==NULL)
    {
        fclose(f);
        printf("LIST IS EMPTY\n\n");
    }
    
    currElem = currElem->nextElem;

    //counter for print to work
    counter = getLenOfList(start);
    for (int i = 0; i < counter; i++)
    {
        fprintf(f, " %s %s %d\n", currElem->lastName, currElem->firstName, currElem->age);
        currElem = currElem->nextElem;
    }

    fclose(f);
    /* ---------------*/
}

void loadList(listElement *start)
{

    /* YOUR CODE HERE */
    char filename[50];
    char txtFile[] = ".txt";

    system("ls *.txt");

    printf("Enter the filename to open for reading in the linkedList:\n'*.txt'--> ");
    scanf("%s", filename);

    //build filename
    strcat(filename, txtFile);

    FILE *f;
    f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("\nUNABLE TO OPEN FILE, PLEASE TRY AGAIN!\n\n");
        return;
    }

    while (fgetc(f) != EOF) //Check for file end, no whitespaces
    {
        //creating new list element, siehe addListElem function
        listElement *new;
        new = (listElement *)malloc(sizeof(listElement));
        if (new == NULL)
        {
            printf("can't reserve storage.\n");
            return;
        }

        listElement *currElem = start;
        while (currElem->nextElem != NULL)
            currElem = currElem->nextElem; // get last elem in list
        currElem->nextElem = new;          // add new to the end of list
        new->nextElem = NULL;

        char ageAsString[50], lastname[50], firstname[50];
        int age;

        //scan document and transfer information to new variable
        fscanf(f, "%s", lastname);
        fscanf(f, "%s", firstname);
        fscanf(f, "%s", ageAsString);
        age = atoi(ageAsString);
        //convert to int
        strcpy(new->lastName, lastname);
        strcpy(new->firstName, firstname);
        new->age=age;
    }    
    
    //delete last element, siehe code delListElem
    int elemPos = getLenOfList(start);
    listElement *previousElem = start;

    for (int i = 1; i < elemPos; i++)
    {
        previousElem = previousElem->nextElem;
    }

    listElement *elemDelet = previousElem->nextElem;
    listElement *elemToCopel = previousElem->nextElem->nextElem;
    previousElem->nextElem = elemToCopel;

    free(elemDelet);

    //close file
    fclose(f);
    /* ---------------*/

    printf("loading data will be append to current list...\n");
    printList(start); // show loaded list
}

void exitFcn(listElement *start)
{

    printf("\n>> exitFcn fcn is tbd.\n\n");
}

void sortList(listElement *start)
{

    printf("\n>>sortList fcn is tbd.\n\n");
}

void stringToLower(char *string)
{

    printf("\n>>stringToLower fcn is tbd.\n\n");
}
