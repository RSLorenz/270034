//programmed by Benedikt Weirich
//using Fisher-Yates-shuffeling for creating a randomised sequence

#include <string>
#include <iostream>

using namespace std;

//Bugflag must be set "manually" no CLO developed yet.
bool bugflag=false;

void rand_init();
int rand_module(int, int);

int main()
{
    string input;
    cin>>input;
    if(bugflag)
    {
        cout<<input<<endl;
    }
    //The String is split into substrings with 1 character per substring.
    string array[input.size()];
    for (int i=0;i<input.size(); i++)
    {
        array[i]= input.substr(i,1);
        if (bugflag)
        {
            cout<<array[i]<<endl;
        }
    }
    rand_init();
    int random;
    //The substrings are shuffeled
    for(int i=0; i<input.size()-1; i++)
    {
        random = rand_module(i,input.size());
        array[i].swap(array[random]);
    }
    //couting string...
    for (int i=0;i<input.size(); i++)
    {
        cout<<array[i];
    }
    return 0;
}

//For having a random number bigger than i
int rand_module(int i, int input_size)
{
    int random;
    do
    {
        random=rand()%input_size;
        if (bugflag)
        {
            cout <<random<<endl;
        }
    }
    while(i>random);
    return random;
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
