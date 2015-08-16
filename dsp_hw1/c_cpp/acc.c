#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char *argv[])
{
	printf("Check your input for test data:\n");
	for(int i=0;i<argc;i++)
	{
	printf("Command_Line_argument(%d):%s\n",i,argv[i]);
	}
	if(argc!=3)printf("Input wrong Command_Line_argument. Must be 3.\n");
	printf("\n");

	FILE * fAns =fopen(argv[1],"r");
	FILE * fResult =fopen(argv[2],"r");

	/*int * Answer;
	Answer =(int *)malloc(2500*sizeof(int));
	int * Result;
	Result=(int *)malloc(2500*sizeof(int));*/

	char tokenAns[15] = "";
	char tokenResult[15]="";

	double acc=0.0;

   	for(int loop=0;loop<2500;loop++)
   	{	
   		fscanf( fAns, "%s", tokenAns );
   		fscanf( fResult, "%s", tokenResult );
   		if((strcmp(tokenAns,tokenResult)==0))
   		{
			acc++;
			//printf("correct!\n");
		}
	}
	double acc_p=(acc/2500);
	//printf("acc:%lf\n",acc_p);
	FILE * Write_Acc = fopen("acc.txt","w");
	fprintf(Write_Acc,"acc:%lf",acc_p);
}