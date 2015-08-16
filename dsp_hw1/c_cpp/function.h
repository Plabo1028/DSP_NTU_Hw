#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef Time
# define Time  50
#endif

#ifndef Sample
# define Sample  10000
#endif

double ** alpha(HMM *hmm,int *StringToState)
{
	  double **alpha;
    int s_num=hmm->state_num;
    int o_num=hmm->observ_num;
    
    //creat array[MAX_STATE][TIME]
    alpha =(double **)malloc(s_num * sizeof(double *));
    for(int i = 0; i < s_num; i++)
    {
        alpha[i] =(double *)malloc(Time * sizeof(double));
    }
    //inital alpha
    for(int i=0;i<s_num;++i)
    {
    alpha[i][0]=hmm->initial[i]*hmm->observation[StringToState[0]][i];
    }
    //Induction
    double sum=0.0;
    for(int t=1;t<Time;t++)
    {
      for(int j=0;j<s_num;j++)
        {
          sum=0.0;
          for(int i=0;i<s_num;i++)
          {
              sum = sum + ((alpha[i][t-1])*(hmm->transition[i][j]));
          }
          alpha[j][t]=sum*hmm->observation[StringToState[t]][j];
          sum=0.0;
        }
    }

    /*
    printf("alpha:\n");
	  for( i = 0 ; i < s_num ; i++ )
	  {
        for( t = 0 ; t < Time ; t++ )
        {
          printf( "%.4lf ", alpha[i][t]);
          if(t%10==9)printf("\n");
        }
        printf("\n");
   	}*/

   	return alpha;
    free(alpha);
}

double ** beta(HMM *hmm,int *StringToState)
{
	  double **beta;
    int s_num=hmm->state_num;
    int o_num=hmm->observ_num;
 
    //creat beta[MAX_STATE][TIME]
    beta = (double **)malloc(s_num * sizeof(double *));
    for(int i = 0; i < s_num; i++)
    {
        beta[i] =(double *)malloc(Time * sizeof(double));
    }
    //inital beta
    for(int i=0;i<s_num;i++)
    {
    	beta[i][Time-1]=1.0;	
    }
   	//Induction
    double sum=0.0;
   	for(int t=Time-2;t>=0;t--)
   	{
   		for(int i=0;i<s_num;i++)
   		{
   			sum=0.0;
   			for(int j=0;j<s_num;j++)
   			{
   				sum=sum+(hmm->transition[i][j]*hmm->observation[StringToState[t+1]][j]*beta[j][t+1]);
   			}
   			beta[i][t]=sum;
        sum=0.0;
   		}
   	}
    /*
    printf("beta:\n");
	  for( i = 0 ; i < s_num ; i++ )
	  {
        for( t = 0 ; t < Time ; t++ )
        {
          printf( "%lf ", beta[i][t]);
          if(t%10==9)printf("\n");
        }
        printf("\n");
   	}*/
   	return beta;
    free(beta);
}
double ** gama(double **alpha,double **beta,int s_num)
{
	double ** gama;

	//create array
	gama =(double **)malloc(s_num*sizeof(double *));
	for(int j=0;j<s_num;j++)
	{
		gama[j]=(double *)malloc(Time*sizeof(double *));
	}

  double sum = 0.0;
	for(int t=0;t<Time;t++)
	{
		sum = 0.0;
		for(int j=0;j<s_num;j++)
		{
			sum=sum+((alpha[j][t])*(beta[j][t]));
		}
		for(int j=0;j<s_num;j++)
		{
      		if(sum!=0)
      		{
			       gama[j][t]=((alpha[j][t])*(beta[j][t]))/sum;
      		}
		}
	}
  /*
	printf("gama:\n");
	for( j = 0 ; j < s_num ; j++ )
	{
        for( t = 0 ; t < Time ; t++ )
        {
          printf( "%lf ",gama[j][t]);
          if(t%10==9)printf("\n");
        }
        printf("\n");
  }*/
  
  return gama;
  free(gama);
}
double * gama_withoutTime(double ** gama,int s_num)
{
  double * gama_WOT;

  gama_WOT =(double *)malloc(s_num * sizeof(double));

  double sum = 0.0;
  for(int j=0;j<s_num;j++)
  {
    sum=0.0;
    for(int t=0;t<Time;t++)
    {
      sum=sum+(gama[j][t]);
    }
    gama_WOT[j]=sum;
    sum=0.0;
  }

  return gama_WOT;
  free(gama_WOT);
}
double ** epsilon(HMM *hmm,double **alpha,double **beta,int *StringToState)
{
     
    int s_num=hmm->state_num;
    int o_num=hmm->observ_num;
    double epsilon[Time-1][s_num][s_num];
    double ** epsilon_WOT;

    epsilon_WOT = (double **)malloc(s_num * sizeof(double *));
    for(int j=0;j<s_num;j++)
    {
      epsilon_WOT[j]=(double *)malloc(Time*sizeof(double ));
   }     
    double sum=0.0;
    for(int t=0;t<(Time-1);t++)
    {
      sum=0.0;
      for(int i = 0 ; i < s_num ; i++ )
      {
          for(int j = 0 ; j < s_num ; j++ )
          {
            sum=sum+((alpha[i][t])*(hmm->transition[i][j])*(hmm->observation[StringToState[t+1]][j])*(beta[j][t+1]));
          }
      }
      for(int i = 0 ; i < s_num ; i++ )
      {
          for(int j = 0 ; j < s_num ; j++ )
          {
            if(sum!=0)
            {
              epsilon[t][i][j]=(((alpha[i][t])*(hmm->transition[i][j])*(hmm->observation[StringToState[t+1]][j])*(beta[j][t+1]))/sum);
            }
          }
      }
      sum=0.0;
    }
    
    /*printf("epsilon:\n");    
    for(int t=0;t<Time-1;t++)
    {
      printf("%d\n",t);
      for(int i = 0 ; i < s_num ; i++ )
      {
          for(int j = 0 ; j < s_num ; j++ )
          {
            printf( "%lf ", epsilon[t][i][j]);
            if(j%6==5)printf("\n");
          }
          if(i%6==5)printf("\n");
      }
    }*/
    sum=0.0;
    for(int i = 0 ; i < s_num ; i++ )
    {
          for(int j = 0 ; j < s_num ; j++ )
          {
            sum=0.0;
            for(int t=0;t<Time-1;t++)
            {
              //printf("%lf",sum);
              sum=sum+epsilon[t][i][j];
            }
            epsilon_WOT[i][j]=sum;
            sum=0.0;
          }
          
    }
    return epsilon_WOT;
    free(epsilon_WOT);
}
double  findmax(double *** array,HMM *hmms,int model,int t,int j)
{
  int s_num=hmms[0].state_num;
  double ans=0.0;
  double temp=0.0;

  for(int i=0;i<s_num;i++)
  {
    temp=((array[model][t][i])*(hmms[model].transition[i][j]));
    if(temp>ans)
    {
      ans=temp;
    }
  }
  //printf("%lf\n",ans);
  return ans;
}

int FindMaxModel(HMM *hmms,int *StringToState)
{
  int s_num=hmms[0].state_num;
  int o_num=hmms[0].observ_num;

  double *** delta_array;//[Model][Time][State]

  delta_array=(double ***)malloc(5*sizeof(double **));
  for(int model=0;model<5;model++)
  {
    delta_array[model]=(double **)malloc(Time*sizeof(double *));
    for(int t=0;t<Time;t++)
    {
      delta_array[model][t]=(double *)malloc(s_num*sizeof(double));
    }
  }

  //initial
  for(int model=0;model<5;model++)
  {
    for(int i=0;i<s_num;i++)
    {
      delta_array[model][0][i]=((hmms[model].initial[i])*(hmms[model].observation[StringToState[0]][i]));
    }
  } 
  //findmax(delta_array,hmms,0,0,0);
  //induction
  for(int model=0;model<5;model++)
  {
    for(int t=1;t<Time;t++)
    {
      for(int j=0;j<s_num;j++)
      {
        double temp=0.0;
        temp=findmax(delta_array,hmms,model,t-1,j);
        delta_array[model][t][j]=(temp*(hmms[model].observation[StringToState[t]][j]));
      }
      
    }
  }
  /*for(int model=0;model<5;model++)
  {
    for(int i=0;i<s_num;i++)
    {
      printf("M(%d),S(%d):%lf\t",model,i,delta_array[model][49][i]);
      
    }
    printf("\n");
  }*/
  double Max_In_Observation=0.0;
  int Max_Model=0;
  for(int model=0;model<5;model++)
  {
    for(int i=0;i<s_num;i++)
    {
      if(((delta_array[model][49][i])>=Max_In_Observation))
      {
          Max_In_Observation=(delta_array[model][49][i]);
          Max_Model=model;
      }
    }
  }
  return Max_Model;
}




