//programmed by Benedikt Weirich
//to create a randomised sequence with a statistical method

#include <string>
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Bugflag must be set "manually" no CLO developed yet.
bool bugflag=false;

void rand_init();

int main()
{
    string input;
    cin>>input;
    unsigned int length;
    length=input.length();
    if(bugflag)
    {
        cout<<length;
    }
    //creating a hashtable for calculating probabilities of each character
    map<string,int> table;
    string character;
    for (int i=0; i<length; i++)
    {
        character = input.substr (i,1);
        if (table.end()==table.find(character))
            {
                table[character]=1;
            }
            else
            {
                table[character]++;
            }
    }
    if(bugflag)
    {
        map<string,int>::iterator it;
        for ( it=table.begin() ; it!=table.end(); it++)
        {
            cout << (*it).first << " => " << (*it).second << endl;
        }
    }
    rand_init();
    if (bugflag)
    {
        cout<<table.size()<<endl;
    }
    //Probabilities and characters are rewritten in arrays
    int values[table.size()];
    char chars[table.size()];
    int i=0;
    map<string,int>::iterator it;
    char *cstr;
    for ( it=table.begin() ; it!=table.end(); it++)
    {
        values[i]=(*it).second;
        if (bugflag)
        {
            cout<<values[i]<<" "<<i<<endl;
        }
        character=(*it).first;
        cstr = new char[character.size()+1];
        strcpy (cstr, character.c_str());
        chars[i]=cstr[0];
        if (bugflag)
        {
            cout<<chars[i]<<" "<<i<<"  "<<values[i]<<endl;
        }
        delete[] cstr;
        i++;
    }
    if(bugflag)
    {
        cout<<"Writing in Array"<<table.size()<<endl;
        for(int i=0; i<table.size(); i++)
        {
            cout<<chars[i]<<" "<<values[i]<<" "<<i<<endl;
        }
    }
    //calculating the total score
    int total_score=0;
    int amount=table.size();
    int randop;
    for (int i=0; i<amount; i++)
    {
        total_score=total_score+values[i];
    }
    //creating the new sequence
    int j=0;
    for (int i=0; i<length; i++)
    {
        randop=rand()%total_score;
        for (j=0; j<length; j++)
        {
            randop=randop-values[j];
            if(randop<=0)
            {
                break;
            }
        }
        cout<<chars[j];
    }
    return 0;
}

void rand_init()
{
    srand(time(NULL));
    //This is a random disposer for better randomised numbers. Fist 10 - 20
    //random numbers are disposed. After that between 50 - 150 random values are
    //disposed. My personal experience shows a better (more randomised) result.
    for (int i=0; i<rand()%10+10;i++)
    {
        rand();
    }
    for (int i=0; i<rand()%100+50;i++)
    {
        rand();
    }
}
