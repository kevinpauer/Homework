#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HA04_EulerLib.h"

#define NUMOFSTATES 2 //

void RHS_MSD(double*rhs, double*y){ // mass spring damper

    double m = 1.0; // mass of object
    double c = 2; // feder constant
    double d = 3; // damper constant

    double x = y[0]; // position
    double v = y[1]; // speed

    /*calc derivatives and store in rhs*/
    rhs[0]=v;
    rhs[1]=-(d/m*v+c/m*x);

}

void eulerSettings_MSD(simHandle* handle){

    /*num of states*/
    handle->numOfStates=NUMOFSTATES;
    
    /*right hand site*/
    handle->f=&RHS_MSD;
    
    /*reserve storage for init state vec*/
    handle->stateVecInit=(double*) malloc(sizeof(double)*(handle->numOfStates));
    if (handle->stateVecInit==NULL)
    {
        printf("STORAGE CAN'T BE RESERVED\n");
        return;
    }
    
    /*get user defined Simtime*/
    printf("Simtime (in s): \n");
    scanf("%lf", &handle->simTime);
    if (handle->simTime<=0)
    {
        printf("A Simtime of %lf is not allowed! Pleas choose a Simtime greater than 0.\n", handle->simTime);
        return;
    }
    

    /*get user defined StepSize*/
    printf("StepSize (in s): \n");
    scanf("%lf", &handle->stepSize);
    if (handle->stepSize<=0)
    {
        printf("A StepSize of %lf is not allowed! Please choose a StepSize greater than 0.\n", handle->stepSize);
        return;
    }

    /*get init state position*/
    printf("position(t = 0): \n");
    scanf("%lf", &handle->stateVecInit[0]);

    /*get init state speed*/
    printf("speed(t = 0): \n");
    scanf("%lf", &handle->stateVecInit[1]);

    /*reserve storage for states and derivatives*/
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
    
    /*init states and derivatives with zero*/
    for (int i = 0; i < lenOfSim; i++)
    {
        handle->stateVec[i]=0;
        handle->derivStateVec[i]=0;
    }
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
        handle->f(&handle->derivStateVec[i*numOfStates], &handle->stateVec[i*numOfStates]);
        for(int j = 0; j < numOfStates; j++){ 
        /*euler step*/
        handle->stateVec[(i+1)*numOfStates+j]=handle->stateVec[i*numOfStates+j]+handle->stepSize*handle->derivStateVec[i*numOfStates+j];
       }
    }
}

void showResults_MSD(simHandle* handle){

    /*print data to text file*/
    FILE* fp;
    fp=fopen("simData.txt", "w");
    if (fp==NULL)
    {
        printf("Fehler beim öffnen der Datei!\n");
        return;
    }

    /*sizeOfSim is equivalent to the needed number of lines in the txt document */
    double sizeOfSim=(int)ceil(handle->simTime/handle->stepSize);
    for (int i = 0; i < sizeOfSim; i++)
    {
        fprintf(fp, "%lf %lf %lf\n", handle->stepSize*i, handle->stateVec[i*NUMOFSTATES], handle->stateVec[i*NUMOFSTATES+1]);   
    }
    fclose(fp);

    /*call gnuplot*/
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe==NULL)
    {
        printf("COULD NOT OPEN GNUPLOTPIPE!");
    }

    /*set titel for x and y axis*/
    fprintf(gnuplotPipe,"set title 'Feder-Dämpfer-System'\n");
    fprintf(gnuplotPipe,"set xlabel 't in seconds'\n");
    
    /*visualize results in gnuplot*/
    fprintf(gnuplotPipe, "plot 'simData.txt' using 1:2 title 'pos' with lines, '' using 1:3 title 'v' with lines\n");

    /*close pipe*/
    pclose(gnuplotPipe);
}