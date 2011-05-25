#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//For memorising the input a single linked list is used
struct memory 
{
    string chain;
    struct memory *next;
};

struct linkedbool
{
    bool intra;
    struct linkedbool *next;
};

void readinginput(memory*);
int width(memory*);
int length(memory*);
int tablefill(memory*,int);
int convertstring(string chain);
void comp(int[],int[],int[],int,int,int,int);
int bigger(int,int);
bool bugflag = false;
bool breakflag = false;
void prestart(int, char*[]);
void help();
void asciiart();
void quote();
void wayplan(int[],int,int);
bool rightdown(int,int);
void map(int[],int,int);
int power(int);
//void mapplan(int[],int,int);

int main(int outer, char* options[])
{
    prestart(outer, options);
    if (breakflag)
    {
        return 0;
    }
    memory *StartWestEast = new memory;
    memory *cursor = StartWestEast;
    //Input is read for West East
    readinginput(StartWestEast);
    memory *StartNorthSouth = new memory;
    //Input is read for North South
    readinginput(StartNorthSouth);
    //the array for the scoring is built here for North-South
    int wns = width(StartNorthSouth);
    int lns = length (StartNorthSouth);
    if(bugflag)
    {
        cout<<"wns"<<wns<<"Lns"<<lns<<endl;
    }
    int NorthSouthMap[wns*lns];
    cursor = StartNorthSouth;
    //the north-south array is filled
    if (bugflag)
    {
        cout<<"North-South-Array:"<<endl;
    }
    for (int j=0; j<lns; j++)
    {
        cursor=cursor->next;
        for (int i=0; i<wns;i++)
        {
            NorthSouthMap[j*(wns)+i]=tablefill(cursor,i);
            if (bugflag)
            {
                cout<<tablefill(cursor,i)<<" "<<i<<"<-i"<<j<<"  j*lns+i:"<<j*(wns)+i<<"  ";
            }
        }
        if (bugflag)
        {
            cout<<endl;
        }
    }
    cursor = StartWestEast;
    //the array for the scoring is built here for West-East
    int wwe = width(StartWestEast);
    int lwe = length (StartWestEast);
    int WestEastMap[wwe*lwe];
    //the west-east array is filled
    if (bugflag)
    {
        cout<<"West-East-Array:"<<endl;
    }
    for (int j=0; j<lwe; j++)
    {
        cursor=cursor->next;
        for (int i=0; i<wwe;i++)
        {
            WestEastMap[j*lwe+i]=tablefill(cursor,i);
            if (bugflag)
            {
                cout<<WestEastMap[j*lwe+i]<<"  ";
            }
        }
        if (bugflag)
        {
            cout<<endl;
        }
    }
    if(bugflag)
    {
        for (int j=0; j<lns; j++)
        {
            for (int i=0; i<wns;i++)
            {
             cout<<NorthSouthMap[j*wns+i]<<" ";  
            }
            cout<<endl;
        }
    }
    // Hier Vllt noch die liste Löschen (brauche sie ja nicht mehr)!
    int scoring[lwe*wns];
    //Scoring-array is set to zero
    for (int i=0; i<wns; i++)
    {
        for (int j=0; j<lwe; j++)
        {
            scoring[j*lwe+i]=0;
        }
    }
    if (bugflag)
    {
        for (int i=0; i<wns; i++)
        {
            for (int j=0; j<lwe; j++)
            {
                cout<<scoring[j*lwe+i]<<"  ";
            }
            cout<<endl;
        }
    }
    //scoring [lwe*wns-1]=0;
    //the scoring array is computed here.
    for (int i=lwe-1; i>=0;i--)
    {
        for (int j=wns-1; j>=0; j--)
        {
            if(bugflag)
            {
                cout<<wns<<" "<<lwe<<"  "<<i<<"  "<<j<<endl;
            }
            comp(&scoring[0],&WestEastMap[0],&NorthSouthMap[0],lwe,wns,i,j);
        }
    }
    //The scoring matix is printed here is an old version new version in module
    //map
    /*
    if(false)
    {
        for (int i=0; i<lwe;i++)
        {
            for (int j=0; j<wns; j++)
            {
                cout<<scoring[i*lwe+j]<<" ";
            }
            cout<<endl;
        }
    }*/
    //wayplan prints the best route for the manhattan tourist problem
    wayplan(&scoring[0],lwe,wns);
    //scoring matix is printed here
    map(&scoring[0],lwe,wns);
    //mapplan(&scoring[0],lwe,wns);
    return 0;
}

//******************************************************************************

void readinginput(memory *cursor)
{
    bool breakbit;
    //Here the WestEast scoring is read and memorised in a list
    do
    {
        getline(cin, cursor->chain);
        if (bugflag)
        {
            cout<<cursor->chain<<endl;
        }
        breakbit = !cursor->chain.empty();
        cursor->next= new memory;
        cursor = cursor->next;
        cursor->next=0;
    }
    while (breakbit);
}

int width(memory* cursor)
{
    //The first row does not contain any data so it is ignored
    cursor=cursor->next;
    int start =-1;
    int i=0;
    //Here the number of numbers in one row is counted
    do
    {
        start=cursor->chain.find_first_of(" ",start+1);
        i++;
    }
    while (start < cursor->chain.npos);
    return i;
}

int length(memory* cursor)
{
    int j=0;
    //The number of rows is counted here. subtracting 2 is for the first and 
    //last row containing no data!
    while (cursor->next)
    {
        j++;
        cursor=cursor->next;
    }
    j=j-2;
    return j;
}

//splits our stream into numbers
int tablefill(memory* cursor,int width)
{
    int position=0;
    string number;
    for (int i=0;i<=width;i++)
    {
        number = cursor->chain.substr(cursor->chain.find_first_not_of(" ",position),cursor->chain.find_first_of(" ",position));
        position=cursor->chain.find_first_of(" ",position+1);
    }
    return convertstring(number);
}

//converts strings to integers
int convertstring(string chain)
{
    stringstream ss (chain);
    int ret;
    ss >> ret;
    return ret;
}

//computes the scoring matix
void comp(int scoring[],int WEM[],int NSM[],int LWE,int WNS,int l,int w)
{
    if(bugflag)
    {
        for(int i=0;i<LWE;i++)
        {
            for (int j=0; j<WNS-1;j++)
            {
                cout<<WEM[i*LWE+j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        for(int i=0;i<WNS;i++)
        {
            for (int j=0; j<LWE;j++)
            {
                cout<<NSM[i*WNS+j]<<" ";
            }
            cout<<endl;
        }
    }
    //This is the last element of the matrix
    if (LWE-1==l && WNS-1==w)
    {
        scoring[l*LWE+w]=0;
        if (bugflag)
        {
            cout<<"LWE-1==l && WNS-1==w"<<endl;
        }
        return;
    }
    //This is for one of the borders
    else if(LWE-1==l)
    {
        scoring[l*LWE+w]=scoring[l*LWE+w+1]+WEM[l*LWE+w];
        if(bugflag)
        {
            cout<<"MODE LWE-1==l:"<<l<<"w:"<<w<<"scoring(l*LWE+w+1)"<<scoring[l*LWE+w+1]<<"scoring(l*LWE+w+)"<<scoring[l*LWE+w]<<"WEM(l*LWE+w)"<<WEM[l*LWE+w]<<endl;
        }
        return;
    }
    //This is for the other border
    else if (WNS-1==w)
    {
        scoring[l*LWE+w]=scoring[(l+1)*LWE+w]+NSM[l*LWE+w];
        if(bugflag)
        {
            cout<<"MODE WNS-1==w:"<<l<<"w:"<<w<<"scoring(l*LWE+w)"<<scoring[l*LWE+w]<<"scoring((l+1)*LWE+w)"<<scoring[(l+1)*LWE+w]<<"NSM(l*LWE+w)"<<NSM[l*LWE+w]<<"l*lwe+w"<<l*LWE+w<<endl;
        }
        return;
    }
    else if (false)
    {
        scoring[l*LWE]=scoring[(l+1)*LWE]+NSM[l*LWE];
        if(bugflag)
        {
            cout<<"MODE w==0:"<<l<<"w:"<<w<<"scoring(l*LWE)"<<scoring[l*LWE]<<"scoring((l+1)*LWE)"<<scoring[(l+1)*LWE]<<"NSM(l*LWE)"<<NSM[l*LWE]<<endl;
        }
        return;
    }
    else if (false)
    {
        scoring [w]=scoring[w+1]+WEM[w];
        if(bugflag)
        {
            cout<<"MODE l==0:"<<l<<"w:"<<w<<"scoring (w)"<<scoring [w]<<"scoring(w+1)"<<scoring[w+1]<<"WEM(w+1)"<<WEM[w+1]<<endl;
        }
        return;
    }
    //This is for the rest...
    else
    {
        scoring[w+l*LWE]=bigger(scoring[w+1+l*LWE]+WEM[w+l*LWE], scoring[w+(l+1)*LWE]+NSM[w+l*LWE]);
        if(bugflag)
        {
            cout<<"MODE ELSE:"<<l<<"w:"<<w<<"scoring(w+l*LWE)"<<scoring[w+l*LWE]<<"bigger"<<bigger(scoring[w+1+l*LWE]+WEM[w+l*LWE], scoring[w+(l+1)*LWE]+NSM[w+l*LWE])<<"scoring(w+1+l*LWE)"<<scoring[w+1+l*LWE]<<"WEM(w+l*LWE)"<<WEM[w+l*LWE]<<"scoring(w+(l+1)*LWE)"<<scoring[w+(l+1)*LWE]<<"NSM(w+l*LWE)"<<NSM[w+l*LWE]<<endl;
        }
        return;
    }
}

//Returns the bigger integer...
int bigger(int lhv,int rhv)
{
    if(lhv<rhv)
    {
        return rhv;
    }
    else
    {
        return lhv;
    }
}

//Prestart sequence for the help and other settings...
void prestart(int outer, char*options[])
{
    for (int i=1; i<outer; i++)
    {
        switch(*options[i])
        {
            case 'b': bugflag = true;
            break;
            case 'q': quote();
            breakflag = true;
            break;
            case 'a': asciiart();
            breakflag =true;
            break;
            case 'h':
            default:
            help();
            breakflag = true;
            break;
        }
    }
    return;
}

//Help is printed...
void help()
{
    cout<<"This is the manual for this programm. With h this Help will come ";
    cout<<"up and programm will not run! If an option is not understand help ";
    cout<<"will come, too."<<endl;
    cout<<"with no option the Programm just give the result."<<endl;
    cout<<"with option b bugflag is set and many subsets will be printed."<<endl;
    cout<<"This programm needs an inputfile is given by '< [name]'"<<endl;
    cout<<"For the accurate layout of the input file see ex03.txt"<<endl;
    return;
}

//Some undocumented feature ;-)
void asciiart()
{
    cout<<"            __ __"<<endl;
    cout<<"           ,;::\\::\\ "<<endl;
    cout<<"        ,'/' `/'`/ "<<endl;
    cout<<"      _\\,: '.,-'.-':."<<endl;
    cout<<"     -./\"'  :    :  :\\/,"<<endl;
    cout<<"      ::.  ,:____;__; :-"<<endl;
    cout<<"      :\"  ( .`-*'o*',);"<<endl;
    cout<<"       \\.. ` `---'`' /"<<endl;
    cout<<"        `:._..-   _.'"<<endl;
    cout<<"        ,;  .     `."<<endl;
    cout<<"       /\"'| |       \\ "<<endl;
    cout<<"      ::. ) :        :"<<endl;
    cout<<"      |\" (   \\       |"<<endl;
    cout<<"      :.(_,  :       ;"<<endl;
    cout<<"       \\'`-'_/      / "<<endl;
    cout<<"        `...   , _,'"<<endl;
    cout<<"         |,|  : |"<<endl;
    cout<<"         |`|  | |"<<endl;
    cout<<"         |,|  | |"<<endl;
    cout<<"     ,--.;`|  | '..--."<<endl;
    cout<<"    /;' \"' ;  '..--. ))"<<endl;
    cout<<"    \\:.___(___   ) ))'"<<endl;
    cout<<"           SSt`-'-'' "<<endl;
    cout<<"http://de.wikipedia.org/wiki/ASCII-Art";
    cout<<endl<<endl<<endl;
    cout<<"           /!_.-_|\\                ||"<<endl;
    cout<<"           `-/_'--'            __./__\\               Snert"<<endl;
    cout<<"           (_(o)\\\\\\)          (_.(o)\\\\               , __  ,"<<endl;
    cout<<"            (||\\\\\\\\;_,          /__-`\\\\_             -/__\\-"<<endl;
    cout<<"             /  _-\".----.          \\,\\-,           .__O  ,;"<<endl;
    cout<<"           ./_-\"  /o,--.o\\         (_ -\\           (___  ||"<<endl;
    cout<<"          /      |o (  ) o|         | , \\              |=|`"<<endl;
    cout<<"         !__,--.__\\o `-'o/          | |  \\          __/  \\"<<endl;
    cout<<"          |_-__--__`----'           | |__J         /,-`   |   ,"<<endl;
    cout<<"         __,/\\_|\\/\\,                (     \\           !    \\  )\\ "<<endl;
    cout<<"        (   `/_'`X_;                |      \\._      _(_(   _=;_/"<<endl;
    cout<<"         `.____)____)               (_________\\    (_(__-__;"<<endl;
    cout<<"http://ascii.co.uk/art/hagar"<<endl;
    cout<<" @@@@@                                        @@@@@"<<endl;
    cout<<"@@@@@@@                                      @@@@@@@"<<endl;
    cout<<"@@@@@@@           @@@@@@@@@@@@@@@            @@@@@@@"<<endl;
    cout<<" @@@@@@@@       @@@@@@@@@@@@@@@@@@@        @@@@@@@@"<<endl;
    cout<<"     @@@@@     @@@@@@@@@@@@@@@@@@@@@     @@@@@"<<endl;
    cout<<"       @@@@@  @@@@@@@@@@@@@@@@@@@@@@@  @@@@@"<<endl;
    cout<<"         @@  @@@@@@@@@@@@@@@@@@@@@@@@@  @@"<<endl;
    cout<<"            @@@@@@@    @@@@@@    @@@@@@"<<endl;
    cout<<"            @@@@@@      @@@@      @@@@@"<<endl;
    cout<<"            @@@@@@      @@@@      @@@@@"<<endl;
    cout<<"             @@@@@@    @@@@@@    @@@@@"<<endl;
    cout<<"              @@@@@@@@@@@  @@@@@@@@@@"<<endl;
    cout<<"               @@@@@@@@@@  @@@@@@@@@"<<endl;
    cout<<"           @@   @@@@@@@@@@@@@@@@@   @@"<<endl;
    cout<<"           @@@@  @@@@ @ @ @ @ @@@@  @@@@"<<endl;
    cout<<"          @@@@@   @@@ @ @ @ @ @@@   @@@@@"<<endl;
    cout<<"        @@@@@      @@@@@@@@@@@@@      @@@@@"<<endl;
    cout<<"      @@@@          @@@@@@@@@@@          @@@@"<<endl;
    cout<<"   @@@@@              @@@@@@@              @@@@@"<<endl;
    cout<<"  @@@@@@@                                 @@@@@@@"<<endl;
    cout<<"   @@@@@                                   @@@@@"<<endl;
    cout<<"http://www.asciiworld.com/"<<endl;
    return;
}

//another undocumented feature...
void quote()
{
    cout<<"The strength of a civilization is not measured by its ability to";
    cout<<" fight wars, but rather by its ability to prevent them."<<endl;
    cout<<"Gene Roddenberry (Earth: Final Conflict)"<<endl;
}

//compares two values and gives a proposal for the dicection
bool rightdown(int lhv, int rhv)
{
    if(lhv<rhv)
    {
        return false;
    }
    else if (lhv==rhv)
    {
        cout<<"Both equal!"<<endl;
        return true;
    }
    else
    {
        return true;
    }
}

//The wayplan is printed...
void wayplan(int scoring[],int LWE, int WNS)
{
    int i=0, j=0;
    do
    {
        if(bugflag)
        {
            cout <<i<<"  "<<j<<endl;
        }
        if (rightdown(scoring[i+1+j*LWE],scoring[i+(j+1)*LWE])&&i<WNS-1)
        {
            cout<<"East"<<endl;
            i++;
        }
        else if (j<LWE-1)
        {
            cout<<"South"<<endl;
            j++;
        }
        else
        {
            return;
        }
    }while((i+j*LWE)<(LWE*WNS));
}

void map(int scoring[], int lwe, int wns)
{
    int power_of_ten=1, k=0;
    power_of_ten=power(scoring[0]);
    if(bugflag)
    {
        cout<<"Power of ten"<<power_of_ten<<endl;
    }
    for (int i=0; i<lwe;i++)
    {
        for (int j=0; j<wns; j++)
        {
            k=0;
            cout<<scoring[i*lwe+j];
            for(k;k<power_of_ten-power(scoring[i*lwe+j])+3;k++)
            {
                cout<<" ";
            }
        }
        cout<<endl;
    }
}

int power(int biggest)
{
    int power_of_ten=1;
    while(biggest>10)
    {
        power_of_ten++;
        biggest=biggest/10;
    }
    return power_of_ten;
}

/*void mapplan(int scoring[], int lwe, int wns)
{
    int i=0, j=0, k=0, l=0;
    linkedbool *start = new linkedbool;
    linkedbool *cursor = start;
    do
    {
        if(bugflag)
        {
            cout <<i<<"  "<<j<<endl;
        }
        if (rightdown(scoring[i+1+j*lwe],scoring[i+(j+1)*lwe])&&i<wns-1)
        {
            cursor->intra=0;
            cursor->next = new linkedbool;
            cursor = cursor->next;
            i++;
        }
        else if (j<lwe-1)
        {
            cursor->intra=1;
            cursor->next = new linkedbool;
            cursor = cursor->next;
            j++;
        }
        else
        {
            return;
        }
    }while((i+j*lwe)<(lwe*wns));
    for(j=0; j<lwe;j++)
    {
        for(i=0; i<wns;j++)
        {
            
}*/
