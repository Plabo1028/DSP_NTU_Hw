#include <stdio.h>
#include <stdlib.h>
#include "train.h"
#include "hmm.h"

int main(int argc,char *argv[])
{
	printf("Chek your input for train data:\n");
	for(int i=0;i<argc;i++)
	{
	printf("Command_Line_argument(%d):%s\n",i,argv[i]);
	}

	if(argc!=5)printf("Input wrong Command_Line_argument.\n");

	printf("\n");

	HMM hmm_initial;
	loadHMM(&hmm_initial,argv[2]);

	for(int iteration=0;iteration<atoi(argv[1]);iteration++)
	{	
	printf("Train %s (iteration %d )\n",argv[3],(iteration+1) );
	train(&hmm_initial,argv[3]);
	}
	
	FILE *fp =fopen(argv[4],"w");
	dumpHMM(fp,&hmm_initial);
}