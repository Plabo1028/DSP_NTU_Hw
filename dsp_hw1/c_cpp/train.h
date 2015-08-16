#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hmm.h"
#include "function.h"
//#include "train.h"

void train(HMM *hmm,const char *filename)
{
	  int s_num=hmm->state_num;
	  int o_num=hmm->observ_num;
	  double *** gama_array;//[Sample][State][Time]
	  double ** gama_arrayWOT;//[Sample][State]
	  double *** epsilon_arrayWOT;//[Sample][State][State]
	  gama_array=(double ***)malloc(10000*sizeof(double **));
	  gama_arrayWOT=(double **)malloc(10000*sizeof(double *));
	  epsilon_arrayWOT=(double ***)malloc(10000*sizeof(double **));

	  int StringToStateALL[10000][Time];//[Sample][Time]
    int StringToState[Time];
	  char token[Time]="";

	  FILE *fp = fopen(filename, "r" );
  	if ( fp ==NULL ) { printf("開讀檔失敗!"); }
  	int loop=0.0;
  	while( fscanf( fp, "%s", token ) > 0 )
  	//for(int loop=0;loop<10;loop++)
  	{
  		//fscanf( fp, "%s", token );
   		for(int i=0;i<50;i++)
    	{
     		//printf("%c",token[i] );
      		switch(token[i])
   	  		{ 
        		case 'A':
          			StringToStateALL[loop][i]=0;
                StringToState[i]=0;
          			break;
        		case 'B':
          			StringToStateALL[loop][i]=1;
                StringToState[i]=1;
          			break;
        		case 'C':
          			StringToStateALL[loop][i]=2;
                StringToState[i]=2;
          			break;
        		case 'D':
          			StringToStateALL[loop][i]=3;
                StringToState[i]=3;
          			break;
        		case 'E':
          			StringToStateALL[loop][i]=4;
                StringToState[i]=4;
          			break;
        		case 'F':
          			StringToStateALL[loop][i]=5;
                StringToState[i]=5;
          			break;
   	  		}
  		}
  		//printf("\n");
  		//for(int i=0;i<50;i++)printf("%d", StringToState[i]);
  		double ** alpha_array;
    	double ** beta_array;

    	alpha_array=alpha(hmm,StringToState);
    	beta_array=beta(hmm,StringToState);
    	gama_array[loop]=gama(alpha_array,beta_array,hmm->state_num);
    	gama_arrayWOT[loop]=gama_withoutTime(gama_array[loop],hmm->state_num);
    	epsilon_arrayWOT[loop]=epsilon(hmm,alpha_array,beta_array,StringToState);

    	/*
    	printf("alpha\n");
    	for(int i=0;i<s_num;i++)
    	{
    		for(int t=0;t<Time;t++)
    		{
    			printf("%lf",alpha_array[i][t] );
    			if(t%10==9)printf("\n");
    		}
    		printf("\n");
    	}
    	printf("beta\n");
    	for(int i=0;i<s_num;i++)
    	{
    		for(int t=0;t<Time;t++)
    		{
    			printf("%lf",alpha_array[i][t] );
    			if(t%10==9)printf("\n");
    		}
    		printf("\n");
    	}
    	printf("gama:\n");
		  for(int j = 0 ; j < s_num ; j++ )
		  {
        	for(int t = 0 ; t < Time ; t++ )
        	{
          		printf( "%lf ",gama_array[loop][j][t]);
          		if(t%10==9)printf("\n");
        	}
        	printf("\n");
  		}
  		printf("gama_WOT\n");
        for(int j = 0 ; j < s_num ; j++ )
        {
          	printf( "%lf ",gama_arrayWOT[loop][j]);
          	if(j%6==5)printf("\n");
        }
        printf("\n");
       	printf("Epsilon_WOT\n");
        for(int i = 0 ; i < s_num ; i++ )
    	{
          	for(int j = 0 ; j < s_num ; j++ )
          	{
          		printf( "%lf ",epsilon_arrayWOT[loop][i][j]);
          		if(j%6==5)printf("\n");
          	}
    	}
    	printf("\n");
    	*/
    	free(alpha_array);
    	free(beta_array);
    	loop=loop+1.0;
	  }
	
	  double sum_gama_Time1[s_num];
	  double sum_gama[s_num];
	  double sum_observationA[o_num];
	  double sum_observationB[o_num];
	  double sum_observationC[o_num];
	  double sum_observationD[o_num];
	  double sum_observationE[o_num];
	  double sum_observationF[o_num];

	  for(int i=0;i<o_num;i++)
	  {
		  sum_observationA[i]=0.0;
		  sum_observationB[i]=0.0;
		  sum_observationC[i]=0.0;
		  sum_observationD[i]=0.0;
		  sum_observationE[i]=0.0;
		  sum_observationF[i]=0.0;
	  }
	  //sum=0.0 initial 
    for(int i=0;i<s_num;i++){sum_gama_Time1[i]=0.0;sum_gama[i]=0.0;}
  	//update Pi	
  	for(int i=0;i<s_num;i++)
  	{
    	for(int count=0;count<loop;count++)
    	{
     		//printf("%lf\n",gama_arrayWOT[count][i]);
      		sum_gama_Time1[i]=(sum_gama_Time1[i]+(gama_array[count][i][0]));
      		sum_gama[i]=(sum_gama[i]+(gama_arrayWOT[count][i]));
    	}
    	hmm->initial[i]=sum_gama_Time1[i]/(double)(loop);
	  }
	  //update A
	  double sum_epsilon=0.0;
	  for(int i=0;i<s_num;i++)
  	{
    	for(int j=0;j<s_num;j++)
    	{
      		sum_epsilon=0.0;
      		for(int count=0;count<loop;count++)
      		{
          		sum_epsilon=(sum_epsilon+(epsilon_arrayWOT[count][i][j]));
      		}
      		hmm->transition[i][j]=(sum_epsilon/(sum_gama[i]));
      		sum_epsilon=0.0;
    	}
  	}
  	//sum 
    //printf("%d\n",loop);
  	for(int count=0;count<loop;count++)
  	{
  		for(int t=0;t<Time;t++)
  		{
        if((StringToStateALL[count][t])==0)//observation=A
        {
            for(int i=0;i<s_num;i++)
            {
                sum_observationA[i]=sum_observationA[i]+gama_array[count][i][t];
            }   
  			}
        else if((StringToStateALL[count][t])==1)//observation=B
        {
            for(int i=0;i<s_num;i++)
            {
                sum_observationB[i]=sum_observationB[i]+gama_array[count][i][t];
            }
        }
        else if((StringToStateALL[count][t])==2)//observation=C
        {
            for(int i=0;i<s_num;i++)
            {
                sum_observationC[i]=sum_observationC[i]+gama_array[count][i][t];
            }
        }
        else if((StringToStateALL[count][t])==3)//observation=D
        {
            for(int i=0;i<s_num;i++)
            {
                sum_observationD[i]=sum_observationD[i]+gama_array[count][i][t];
            }
        }
        else if((StringToStateALL[count][t])==4)//observation=E
        {
            for(int i=0;i<s_num;i++)
            {
                sum_observationE[i]=sum_observationE[i]+gama_array[count][i][t];
            }
        }
        else if((StringToStateALL[count][t])==5)//observation=F
        {
            for(int i=0;i<s_num;i++)
            {
                sum_observationF[i]=sum_observationF[i]+gama_array[count][i][t];
            }
        }
        else
        {
          printf("Error in StringToStateALL\n");
        }
  		}
  	}
    //update B
    for(int o=0;o<o_num;o++)
    {
      for(int i=0;i<s_num;i++)
      {
        if(o==0)
        {
          hmm->observation[o][i]=(sum_observationA[i]/sum_gama[i]);
        }
        else if(o==1)
        {
          hmm->observation[o][i]=(sum_observationB[i]/sum_gama[i]);
        }
        else if(o==2)
        {
          hmm->observation[o][i]=(sum_observationC[i]/sum_gama[i]);
        }
        else if(o==3)
        {
          hmm->observation[o][i]=(sum_observationD[i]/sum_gama[i]);
        }
        else if(o==4)
        {
          hmm->observation[o][i]=(sum_observationE[i]/sum_gama[i]);
        }
        else if(o==5)
        {
          hmm->observation[o][i]=(sum_observationF[i]/sum_gama[i]);
        }
      }
    }

    /*
  	printf("PI:\n");
	  for(int i=0;i<s_num;i++)printf("%lf ",hmm->initial[i]);
		printf("\n");

	  printf("A:\n");
	  for(int i = 0 ; i < s_num ; i++ )
    {
    	for(int j = 0 ; j < s_num ; j++ )
      {
        	printf( "%lf ",hmm->transition[i][j]);
          if(j%6==5)printf("\n");
      }
    }
    printf("B:\n");
    for(int o=0;o<o_num;o++)
    {
      for(int i=0;i<s_num;i++)
      {
        printf("%lf", hmm->observation[o][i]);
        if(i%6==5)printf("\n");
      }
    }*/

printf("\n");
}