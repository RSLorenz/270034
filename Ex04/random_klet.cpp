//programmed by Benedikt Weirich
//creating a randomised sequence as in D.Kandel et al. Shuffeling biological sequences
//Discrete Applied Mathematics 71 (1996) 171 - 185

#include <string>
#include <iostream>

using namespace std;

//Bugflag must be set "manually" no CLO developed yet.
bool bugflag=false;

void rand_init();
int rand_module(int, int);
int rand_module_max(int, int, int);

int main()
{
    int klet;
    cin>>klet;
    klet--;
    string input;
    cin>>input;
    if(bugflag)
    {
        cout<<input<<endl;
    }
    rand_init();
    int random_a, random_b;
    int end_second, start_second;
    string swap;
    //The klet-Sequences are looked for if they exist the klet ends are swapped
    //if there are any nothing happens
    for(int i=0; i<input.size()-1; i++)
    {
        random_a=rand_module(i, input.size());
        start_second=input.find(input.substr(i,klet),random_a);
        random_b=rand_module_max(i,start_second, input.size());
        end_second=input.find(input.substr(random_b, klet),start_second);
        if(bugflag)
        {
            cout<<input<<endl<<i<<" "<<random_b<<" "<<start_second<<" "<<end_second<<endl;
        }
        if((random_b<start_second)&&(random_b>0)&&(start_second>0)&&(end_second>start_second)&&(random_b>i))
        {
            swap.clear();
            swap=input.substr(0,i);
            swap.append(input.substr(start_second, end_second-start_second));
            swap.append(input.substr(random_b, start_second-random_b));
            swap.append(input.substr(i,random_b-i));
            swap.append(input.substr(end_second, input.length()-end_second));
            if(bugflag)
            {
                cout<<"swap" <<swap<<endl;
            }
            input.clear();
            input.append(swap);
        }  
    }
    cout <<input;
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
    while(i>=random);
    return random;
}

//For having a random number bigger than i smaller than j
int rand_module_max(int i, int j, int input_size)
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
    while((i>=random)&&(j<=random));
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
