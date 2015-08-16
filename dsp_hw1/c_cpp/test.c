#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "hmm.h"

int main(int argc,char *argv[])
{
	int * Result;
	Result=(int *)malloc(2500*sizeof(int));
	printf("Check your input for test data:\n");
	for(int i=0;i<argc;i++)
	{
	printf("Command_Line_argument(%d):%s\n",i,argv[i]);
	}
	if(argc!=4)printf("Input wrong Command_Line_argument. Must be 4.\n");

	printf("\n");

	HMM hmms[5];
	load_models( argv[1], hmms, 5);
	//dump_models( hmms, 5);

	Result=test(hmms,argv[2]);
	FILE *fp =fopen(argv[3],"w");

	for(int i=0;i<2500;i++)
	{	
		switch(Result[i])
		{
			case 0:
				//printf("model_01.txt\n");
				fprintf( fp, "%s\n","model_01.txt");
				break;
			case 1:
				//printf("model_02.txt\n");
				fprintf( fp, "%s\n","model_02.txt");
				break;
			case 2:
				//printf("model_03.txt\n");
				fprintf( fp, "%s\n","model_03.txt");
				break;
			case 3:
				//printf("model_04.txt\n");
				fprintf( fp, "%s\n","model_04.txt");
				break;
			case 4:
				//printf("model_05.txt\n");
				fprintf( fp, "%s\n","model_05.txt");
				break;
		}
		//printf("%d\n",Result[i]);
	}
}