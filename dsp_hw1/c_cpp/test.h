#include "hmm.h"
#include "function.h"

int * test(HMM *hmms,const char *filename)
{
	int StringToState[Time];
	char token[Time]="";
  int * Result;
  Result=(int *)malloc(2500*sizeof(int));

	FILE *fp = fopen(filename, "r" );
	if ( fp ==NULL ) { printf("開讀檔失敗!\n"); }
	int loop=0;
	while( fscanf( fp, "%s", token ) > 0 )
  //for(loop=0;loop<3;loop++)
  {
  		//fscanf( fp, "%s", token );
		  for(int i=0;i<50;i++)
    	{
     		//printf("%c",token[i] );
      		switch(token[i])
   	  		{ 
        		case 'A':
                	StringToState[i]=0;
          			break;
        		case 'B':
                	StringToState[i]=1;
          			break;
        		case 'C':
                	StringToState[i]=2;
          			break;
        		case 'D':
                	StringToState[i]=3;
          			break;
        		case 'E':
                	StringToState[i]=4;
          			break;
        		case 'F':
                	StringToState[i]=5;
          			break;
   	  		}
  		}
  		//printf("\n");
  		Result[loop]=FindMaxModel(hmms,StringToState);
      loop++;
  		
  }
  //for(int i=0;i<loop;i++)
  //{
      //printf("%d\n",Result[i]);
  //}
  //printf("\n");
  return Result;
}