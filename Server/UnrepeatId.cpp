#include<vector>
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
vector<int>disnum;
int startnum=100000;
int addnum=1000;
void random(int n)
{
	int index, tmp, i;
	srand(time(NULL));
	for(i=n-1; i>0; i--)
	{   
    	index=rand()%i;
	 	tmp=disnum[i];
		disnum[i]=disnum[index];
		disnum[index]=tmp;
	}
} 

int getUnrepeatId()
{
    if(disnum.size()==0) 
    {   disnum.reserve(addnum);
        for (int i = startnum; i <= startnum+addnum; ++i) 
        {disnum.push_back(i);
        }
        random(addnum);
        startnum+=addnum;
    }   
    int num=disnum.back();
    disnum.pop_back();
    return num;
}
