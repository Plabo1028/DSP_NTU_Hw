#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "Ngram.h"
#define BUFSIZE 4096

using namespace std;

int main(int argc, char* argv[])
{
	Vocab vocab;
	Ngram lm(vocab, 2); 
	vector<string> splitLine;
	map<string, set<string> > mapping;
	map<string, set<string> >::iterator map_iter;
	vector<string> BestLine;
	vector<string>::iterator Best_iter;
	FILE * TextFile;
	FILE * MapFile;

	char ch;
	char tmpstr[BUFSIZE];

	for(int i=0 ; i<argc ; i++)
	{
		if(string("-text")==argv[i])
		{
			TextFile = fopen(argv[i+1],"r");
		}
		if(string("-map")==argv[i])
		{
			MapFile = fopen(argv[i+1], "r");
		}
		if(string("-lm")==argv[i])
		{
			File lmFile(argv[i+1],"r"); 
			lm.read(lmFile);
			lmFile.close();
		}
	}
	//read MapFile into map<string, set<string> > mapping
	while(fgets(tmpstr,4096,MapFile))
	{
		char *tok=strtok(tmpstr,"\n");
		string Key,StringTok;
		set<string> ZhuYin;
		while(tok!=NULL)
		{
			StringTok=string(tok);
			Key = StringTok.substr(0,2);//read the first ZhuYin or ChuIn to key
			int pos;
			string tmpLine=StringTok.substr(3);
			while((pos = tmpLine.find(" "))!=-1)
			{
				tmpLine.erase(pos,1);
			}
			assert(tmpLine.size()%2==0);
			for(int i=0 ; i<tmpLine.size() ; i+=2)
			{
				string buf = tmpLine.substr(i, 2);
				ZhuYin.insert(buf);
			}
			mapping[Key]=ZhuYin;
			tok = strtok(NULL,"\n");
			ZhuYin.clear();
		}
	}
	//read TextFile into vector<string> splitLine
	int line =0;
	while(fgets(tmpstr,4096,TextFile))
	{
		line++;
		char *tok=strtok(tmpstr,"\n");//Splite into one line
		string tmpLine = string(tok);    	
		while(tok!=NULL)
		{	
			int pos;
			while((pos = tmpLine.find(" "))!=-1)
			{
				tmpLine.erase(pos,1);
			}
			assert(tmpLine.size()%2==0);
			for(int i=0 ; i<tmpLine.size() ; i+=2)
			{
				string buf = tmpLine.substr(i, 2);
				splitLine.push_back(buf);//push one word to splitLine 
			}
			tok = strtok(NULL,"\n");
		}
		splitLine.push_back("\n");	
	}
	int count = 1;
	//Viterbi
	for(int i=0;i<splitLine.size();i++)
	{
		set<string> TmpSet;
		if(i==0)
		{
			//cout << count << endl;
			BestLine.push_back("<s>");
			BestLine.push_back(" ");
		}
		if(splitLine[i]=="\n")
		{
			count++;
			//cout << endl;
			//cout << count << endl;
			BestLine.push_back("</s>");
			BestLine.push_back("\n"); 
			BestLine.push_back("<s>");
			BestLine.push_back(" ");
		}
		else
		{
			//cout <<  splitLine[i];//print every line without space
			map_iter = mapping.find(splitLine.at(i));//find the splitline[i] in mapping to map_iter
			//cout << (map_iter -> first).c_str() << endl;
			set<string> EveryPossibleZhuYin = map_iter -> second;
			//all possible ZhuYin in ChuIn
			set<string>::iterator iBegin=EveryPossibleZhuYin.begin();
			string PreString;

			for(iBegin;iBegin!=EveryPossibleZhuYin.end();++iBegin)
			{
				//cout << *iBegin->c_str() <<endl;
			}
			//sleep(1);
			string TempString;
			double maxProb = -1000.0;
			VocabIndex wid;
			string best;
			for(set<string>::iterator i=EveryPossibleZhuYin.begin();i!=EveryPossibleZhuYin.end();++i)
			{
				TempString = *i;
				//cout << TempString.c_str() << endl;

				//sleep(1);
				VocabIndex context[]={vocab.getIndex(PreString.c_str()),Vocab_None};
				wid=vocab.getIndex(TempString.c_str());
				if(wid == Vocab_None) 
				{
					//printf("Not in bigram.lm\n");
				}
				else
				{
					double pro=lm.wordProb(wid,context);

					if(pro>maxProb)
					{	
						best = TempString;
						maxProb=pro;
					}
				}
			}
			PreString=best;
			BestLine.push_back(PreString);
			BestLine.push_back(" ");

		}
	}
	for(vector<string>::iterator i=BestLine.begin();i!=(BestLine.end()-2);++i)
	{
		cout << *i ;
	}

}


