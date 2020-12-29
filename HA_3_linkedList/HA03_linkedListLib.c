#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HA03_linkedListLib.h"

void addListElem(listElement *start){
    
    listElement * new;
    new = (listElement *)malloc(sizeof(listElement));
    if (new == NULL) {
        printf("can't reserve storage.\n"); 
        return;
        }

    listElement * currElem = start;
    while (currElem->nextElem != NULL) currElem = currElem->nextElem;// get last elem in list
    currElem->nextElem = new; // add new to the end of list
    new->nextElem = NULL;
    
    /* fill data in new element */
    printf("Please enter last name: \n");
    scanf("%s",new->lastName);
    printf("Please enter first name: \n");
    scanf("%s",new->firstName);
    printf("Please enter age: \n");
    scanf("%d",&(new->age));
    printf("end of function\n");
}

void printList(listElement *start){

    /* YOUR CODE HERE */
    listElement * currElem = start;
    //check if there are elements added, that can be printed
    if (currElem->nextElem == NULL)
    {
        printf("\nNO NEW ELEMENT ADDED!\n");
        return;
    } 

    //count is relevant for future deletion of the object
    int count = 0;

    while (currElem->nextElem != NULL)
    { 
        currElem = currElem->nextElem;
        printf("%d) %s ",count+1, currElem->lastName);
        printf("%s ", currElem->firstName);
        printf("%d\n", currElem->age);
        count++;
    }
    /* ---------------*/


}

void delListElem(listElement **start){

    /* YOUR CODE HERE */
    int pos;
    listElement * temp = *start;
    listElement * next = temp->nextElem->nextElem; 

    printf("Löschen des Elements mit der Position: \n--> ");
    scanf("%d", &pos);

    // look if list is empty
    if (*start == NULL) 
        return; 
  
    // If head needs to be removed 
    if (pos == 0) 
    { 
        *start = temp->nextElem;   
        free(temp);               
        return; 
    } 
  
    // Find previous node of the node to be deleted 
    for (int i=0; temp!=NULL && i<pos-1; i++) 
        temp = temp->nextElem; 
  
    // If position is more than number of nodes 
    if (temp == NULL || temp->nextElem == NULL) 
        return; 
  
    // Unlink the node from linked list 
    free(temp->nextElem);  
  
    temp->nextElem = next;  
    /* ---------------*/

}

void delList(listElement **start){

    /* YOUR CODE HERE */
    listElement * prev = * start;
    
    //free the memory of every element
    while (*start)
    {
        *start = (*start)->nextElem;
        free(prev);
        prev = *start;
    }

    printf("List successfully deleted!\n\n");
    /* ---------------*/
}

int getLenOfList(listElement *start){ // we use this for save list fcn

    int counter = 0;
    listElement * currElem = start;
    while (currElem->nextElem != NULL) {// get last elem in list
        currElem = currElem->nextElem; counter++;
        }
    return counter;
}

void saveList(listElement *start){

    /* YOUR CODE HERE */
    char filename[50];
    FILE *f;
    listElement * currElem = start;

    printf("Enter the filename to open for saving the linkedList \n e.g. '*.txt' --> ");
    scanf("%s", filename);

    f = fopen(filename, "w");

    //if filepointer is not NULL then print all elements of the list in the .txt file
    if (f == NULL) {
        printf("Error with filePointer\n");
    } else
    {
        currElem = currElem->nextElem;
        while (currElem!=NULL)
        {
            fprintf(f, "%s %s %d\n", currElem->lastName, currElem->firstName,currElem->age);
            currElem=currElem->nextElem;
        }
    }

    fclose(f);
    /* ---------------*/
}

void loadList(listElement *start){
	
    /* YOUR CODE HERE */
    char filename[50];
    FILE *f;
    listElement * currElem = start;

    system("ls *.txt");

    printf("Enter the filename to open for reading in the linkedList:\n--> ");
    scanf("%s", filename);

    f = fopen(filename, "r");

    while(!feof(f)) //Check for file end
    {
        //creating new list element, siehe addListElem function
        listElement * new;
        new = (listElement *)malloc(sizeof(listElement));
        if (new == NULL) {
            printf("can't reserve storage.\n"); 
            return;
        }

        listElement * currElem = start;
        while (currElem->nextElem != NULL) currElem = currElem->nextElem;// get last elem in list
        currElem->nextElem = new; // add new to the end of list
        new->nextElem = NULL;

        //scan document and transfer information to new element, till EOF
        if(fscanf(f, "%s %s %d", new->lastName, new->firstName, &new->age) == EOF) {
            break;
        }
    }

    fclose(f);
    /* ---------------*/

	printf("loading data will be append to current list...\n");
	printList(start); // show loaded list
}

void exitFcn(listElement *start){

    printf("\n>> exitFcn fcn is tbd.\n\n");

}

void sortList(listElement *start){
	
	printf("\n>>sortList fcn is tbd.\n\n");
    
}

void stringToLower(char *string) {
	
    printf("\n>>stringToLower fcn is tbd.\n\n");

}





