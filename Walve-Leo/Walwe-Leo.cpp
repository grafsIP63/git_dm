#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <string>
#include <string.h>

#define SOURCE "Graf.csv"
#define INFINITY 9999

using namespace std;

struct Lenth
{
    bool used=false;
    int lenth=INFINITY;
};

int size=0,connect=0,finish=0;

void readFile(FILE *fd,int **&array);
void createArray(int **&array);
void sMatrix(int **&array);
void Walwe(Lenth *&sizeM,int **&array,queue<int> q,int start,int prev);

int main(void)
{
    FILE *fd=fopen(SOURCE,"r");
    int **array=NULL;
    readFile(fd,array);
    sMatrix(array);
    struct Lenth *sizeMatrix=(struct Lenth*) malloc(sizeof(struct Lenth)*size);
    int st=0;
    cout<<"Enter Start:";
    cin>>st;
    cout<<"Enter Finish:";
    cin>>finish;
    st--;
    finish--;
    //cout<<"FSFFSFSF";
    //sizeMatrix[st].used=true;
    //sizeMatrix[st].lenth=0;
    //cout<<st<<";"<<sizeMatrix[st].used;
    queue<int> q;
    q.push(st);
    Walwe(sizeMatrix,array,q,st,st);
    cout<<endl;
    cout<<"Our distance:"<<endl;
    for(int i=0;i<size;i++)
    {
        cout<<"From "<<st+1<<" to "<<i+1<<":"<<sizeMatrix[i].lenth<<";"<<endl;
    }
}

void readFile(FILE *fd,int **&array)
{
    
    if(!fd)
    {
        cout<<"Error:Can't open the file";
        //system("pause");
        return;
    }
    else
    {
        fscanf(fd,"%i %i",&size,&connect);
        //cout<<size<<connect;
        createArray(array);
        int position1=0,position2=0;
        while(!feof(fd))
        {
            fscanf(fd,"%i %i",&position1,&position2);
            //cout<<position1<<";"<<position2<<endl;
            if(position2<=size && position1<=size && position2>=1 && position1>=1)
            {
                array[position1-1][position2-1]=1;
            }
            else
            {
                cout<<"Error:Incorect data";
                return;
            }
        }
    }
}

void createArray(int **&array)
{
    array=new int*[size];
    for(int i=0;i<size;i++)
    {
        array[i]=new int[size];
    }
    
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            array[i][j]=0;
        }
    }
}

void sMatrix(int **&array)
{
    cout<<endl<<"sMatrix"<<endl;
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            cout<<array[i][j]<<"   ";
        }
        cout<<endl;
    }
}

void Walwe(Lenth *&sizeM,int **&array,queue<int> q,int start,int prev)
{
    //sstream ss;
   // cout<<start<<";"<<sizeM[start].used;
    sizeM[start].used=true;
    for(int i=0;i<size;i++)
    {
        if(array[start][i]==1 && !sizeM[i].used)
        {
            q.push(i);
            sizeM[i].lenth=sizeM[prev].lenth+1;
        }
    }
    int next=0;
    for(int i=0;i<q.size();i++)//q.top()==start
    {
        next=q.front();
        q.pop();
        if(next==finish)
        {
            cout<<finish+1<<";"<<start+1<<";";
        }
        Walwe(sizeM,array,q,next,start);
        return ;
    }
}