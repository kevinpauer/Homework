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

    /*
    SHOULD BE FINISHED
    */

    /* YOUR CODE HERE */
    listElement * currElem = start;
    if (currElem==NULL)
    {
        printf("\n THERE IS NO LIST ANYMORE! \n");
        return;
    } else if (currElem->nextElem == NULL)
    {
        printf("\n NO NEW ELEMENT ADDED! \n");
    }
    
    int count;

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

    /*
    SHOULD BE FINISHED
    */

    /* YOUR CODE HERE */
    int pos;
    printf("Löschen des Elements mit der Position: \n --> ");
    scanf("%d", &pos);

    // look if list is empty
    if (*start == NULL) 
        return; 
    
    listElement * temp = *start; 
  
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
  
    listElement *next = temp->nextElem->nextElem; 
  
    // Unlink the node from linked list 
    free(temp->nextElem);  
  
    temp->nextElem = next;  
    /* ---------------*/

}

void delList(listElement **start){

    /*
    SHOULD BE FINISHED
    */

    /* YOUR CODE HERE */
    listElement * prev = * start;
    
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

    /*
    SHOULD BE FINISHED
    */

    /* YOUR CODE HERE */
    char filename[50];
    FILE *f;
    listElement * currElem = start;

    printf("Enter the filename to open for saving the linkedList \n e.g. 'name.txt' --> ");
    scanf("%s", filename);

    f = fopen(filename, "w");

    if (f == NULL) {
        printf("es ist ein fehler mit dem FilePointer aufgetreten\n");
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

    /*
    SHOULD BE FINISHED
    */
	
	
    /* YOUR CODE HERE */
    char filename[50];
    FILE *f;
    listElement * currElem = start;

    system("ls *.txt");

    printf("Enter the filename to open for reading in the linkedList: \n");
    scanf("%s", filename);

    f = fopen(filename, "r");

    while(!feof(f)) //Check for file end
    {
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





