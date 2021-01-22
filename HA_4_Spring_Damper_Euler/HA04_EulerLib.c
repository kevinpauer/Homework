#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HA04_EulerLib.h"

#define NUMOFSTATES 2 //

void RHS_MSD(double*rhs, double*y){ // mass spring damper

    double m = 1.0; // mass of object
    double c = 5; // feder constant
    double d = 0.25; // damper constant

    double x = y[0]; // position
    double v = y[1]; // speed

    /*calc derivatives and store in rhs*/
    rhs[0]=v;
    rhs[1]=-(d/m*v+c/m*x);
    /* YOUR CODE HERE */
    /* ---------------*/

}

void eulerSettings_MSD(simHandle* handle){

    /*num of states*/

    /* YOUR CODE HERE */
    handle->numOfStates=NUMOFSTATES;
    /* ---------------*/
    
    /*right hand site*/
    
    /* YOUR CODE HERE */
    handle->f=&RHS_MSD;
    /* ---------------*/
    
    /*reserve storage for init state vec*/
    
    /* YOUR CODE HERE */
    handle->stateVecInit=(double*) malloc(sizeof(double)*(handle->numOfStates));
    if (handle->stateVecInit==NULL)
    {
        printf("STORAGE CAN'T BE RESERVED\n");
        return;
    }
    /* ---------------*/
    
    /*get user defined Simtime*/
    printf("Simtime (in s): \n");

    /* YOUR CODE HERE */   
    // scanf("%lf", &handle->simTime);
    handle->simTime=60;
    /* ---------------*/

    /*get user defined StepSize*/
    printf("StepSize (in s): \n");

    /* YOUR CODE HERE */
    // scanf("%lf", &handle->stepSize);
    // if (handle->stepSize==0)
    // {
    //     printf("A STEPSIZE OF 0 IS NOT ALLOWED, PLEASE TRY AGAIN!\n");
    //     return;
    // }
    
    handle->stepSize=0.01;
    /* ---------------*/

    /*get init state position*/
    printf("position(t = 0): \n");

    /* YOUR CODE HERE */
    // scanf("%lf", &handle->stateVecInit[0]);
    handle->stateVecInit[0]=500;
    /* ---------------*/

    /*get init state speed*/
    printf("speed(t = 0): \n");

    /* YOUR CODE HERE */
    // scanf("%lf", &handle->stateVecInit[1]);
    handle->stateVecInit[1]=-1;
    /* ---------------*/

    /*reserve storage for states and derivatives*/
    
    /* YOUR CODE HERE */
    double lenOfSim=(int)ceil(handle->simTime/handle->stepSize);
    handle->stateVec=(double*) malloc(sizeof(double)*(lenOfSim*NUMOFSTATES));
    if (handle->stateVec==NULL)
    {
        printf("STORAGE CAN'T BE RESERVED\n");
        return;
    }

    handle->derivStateVec=(double*) malloc(sizeof(double)*(lenOfSim*NUMOFSTATES));
    if (handle->derivStateVec==NULL)
    {
        printf("STORAGE CAN'T BE RESERVED\n");
        return;
    }
    /* ---------------*/
    
    /*init states and derivatives with zero*/
    
    /* YOUR CODE HERE */
    for (int i = 0; i < lenOfSim; i++)
    {
        handle->stateVec[i]=0;
        handle->derivStateVec[i]=0;
    }
    
    /* ---------------*/
}

void eulerForward(simHandle* handle){ // this is called only once
    int numOfStates = handle->numOfStates;
    int integratorSteps = (int)ceil(handle->simTime/handle->stepSize);

    /*write init states*/
    for(int i = 0; i < numOfStates; i++){
        handle->stateVec[i] = handle->stateVecInit[i];
    }
    for(int i = 0; i < integratorSteps; i++){
        /*get derivatives*/

        /* YOUR CODE HERE */
        handle->f(&handle->derivStateVec[i*numOfStates], &handle->stateVec[i*numOfStates]);
        /* ---------------*/
        for(int j = 0; j < numOfStates; j++){ 
        /*euler step*/
        
        /* YOUR CODE HERE */
        handle->stateVec[(i+1)*numOfStates+j]=handle->stateVec[i*numOfStates+j]+handle->stepSize*handle->derivStateVec[i*numOfStates+j];
        /* ---------------*/
       }
    }
}

void showResults_MSD(simHandle* handle){

    /*print data to text file*/

    /* YOUR CODE HERE */
    FILE* fp;
    fp=fopen("simData.txt", "w");
    if (fp==NULL)
    {
        printf("Fehler beim öffnen der Datei!\n");
        return;
    }
    double lenOfSim=(int)ceil(handle->simTime/handle->stepSize);
    for (int i = 0; i < lenOfSim; i++)
    {
        fprintf(fp, "%lf %lf %lf\n", handle->stepSize*i, handle->stateVec[i], handle->derivStateVec[i]);   
    }
    fclose(fp);

    /* ---------------*/

    /*call gnuplot*/
    
    /* YOUR CODE HERE */
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe==NULL)
    {
        printf("COULD NOT OPEN GNUPLOTPIPE!");
    }

    fprintf(gnuplotPipe,"set title 'Feder-Dämpfer-System'\n");
    fprintf(gnuplotPipe,"set xlabel 'Stuff auf der x-Achse\n");
    fprintf(gnuplotPipe,"set ylabel 't in seconds'\n");

    fprintf(gnuplotPipe, "plot 'simData.txt'\n");
    pclose(gnuplotPipe);
    /* ---------------*/

}

