#include <iostream>
#include <cstdio>
#include <cstring>
#include <windows.h>
#include <queue>
#include <QDebug>
#include "myhuffman.h"
#define  pp  system("pause");
#define  t1  cout<<"test1"<<endl;
#define  t2  cout<<"test2"<<endl;
#define  t3  cout<<"test3"<<endl;
using namespace std;  
const int nmax=600;
const int inf=0x3f3f3f3f;
int Count;
int cnt[nmax+2],cnt2[nmax+2],size;//统计字符个数；
queue<char> q;
struct node
{
	int cnt;  unsigned char ch;
    node* lef,*rig;
    node() { cnt=0; ch=0; lef=rig=NULL; }
};
node *root=NULL;
void calcnt(FILE *fin)
{
    memset(cnt, 0, sizeof cnt);
    char ch;
    while(fscanf(fin,"%c",&ch)==1)
    {
        unsigned char ch2=(unsigned char) ch;
     // putchar(ch2);   //debug
        cnt[ch2]++;
	}
}
node* createtree()
{
	node *(p[nmax]);
	int k=0;   for(int i=0; i<300; i++) 	if(cnt[i]!=0) k++;
	size=300;
	for(int j=1; j<=k-1; j++)
	{
		int min1=inf,p1=-1;
		for(int i=0; i<nmax; i++)
			if(cnt[i]!=0&&cnt[i]<min1) min1=cnt[i],p1=i;
		cnt[p1]=0; 
		int min2=inf,p2=-1;
        for(int i=0; i<nmax; i++)
        	if(cnt[i]!=0&&cnt[i]<min2) min2=cnt[i],p2=i;
        cnt[p2]=0;  
        cnt[size++]=min1+min2;
        
        if(p1<300) { p[p1]=new node;  p[p1]->ch=p1;  p[p1]->cnt=cnt[p1]; }
        if(p2<300) { p[p2]=new node;  p[p2]->ch=p2;  p[p2]->cnt=cnt[p2]; }
        p[size-1]=new node;   p[size-1]->cnt=cnt[size-1];  p[size-1]->lef=p[p1];  p[size-1]->rig=p[p2]; 
        if(j==k-1)  return p[size-1];
	}
}
char table[nmax][100];
char st[100];
void initail()
{
	for(int i=0; i<nmax; i++)
		table[i][0]='\0';
	st[0]='\0';
}
void code(node *root)
{
	if(root->lef==NULL && root->rig==NULL)
	{
		strcpy(table[root->ch],st);   return;
	}
	int len=strlen(st);
	st[len]='0'; st[len+1]='\0';
	code(root->lef);
	st[len]='\0';
	st[len]='1'; st[len+1]='\0'; 
	code(root->rig);
	st[len]='\0';
}
unsigned char stoch()
{
	unsigned char ans=0x00;
	for(int i=1;i<=8; i++)
	{
		unsigned char  t=(q.front()-'0');
	    ans=ans*2+t;
	    q.pop();	
	}
	return ans;
}
void writebin(FILE *fin, FILE *fout)
{
	
	char ch;  
	while(!q.empty())  q.pop();
	while(fscanf(fin,"%c",&ch)==1)
	{
		unsigned char ch2=(unsigned char) ch;
        for(int i=0;i<strlen(table[ch2]);i++)
        {
            q.push(table[ch2][i]);
        }
        while(q.size()>=8)
        {
            unsigned char t=stoch();
            fprintf(fout,"%c",t);
        }
	}
	if(!q.empty())
	{
		int add=8-q.size();
		while(add--)  q.push('0');
		unsigned char t=stoch();
        fprintf(fout,"%c",t);
	}
}
void writediction(FILE *fout)
{
	for(int i=0; i<300; i++)
    {
        fprintf(fout," %d",cnt2[i]);
	}
}
void del(node* root)
{
	if(root!=NULL)
	{
		del(root->lef);
		del(root->rig);
		delete root;
	}
}
void decode(char* deFname,  char *outFname)
{
    qDebug()<<"1    "<<deFname<<"   2   "<<outFname<<endl;
    FILE * fin=fopen(deFname,"rb");
    memset(cnt,0,sizeof cnt);
	for(int i=0; i<300; i++)
	fscanf(fin,"%d",&cnt[i]);
    root=createtree();
    Count=root->cnt;
    initail();
    code(root);
    qDebug()<<"plese input out filename:";
    char* fname;       fname = outFname;          //scanf("%s",fname);
    char tmp[200];
    char* ptmp;
    ptmp = tmp;
    int len = strlen(deFname);
    for( int i = len-1; i>=0; i--)
    {
        if (deFname[i]=='/' || deFname[i] == '\\')
        {
            qDebug()<<"i  "<<i;
            for(int  j=0; j<=i; j++)
                tmp[j] = deFname[j];
            tmp[i+1] = '\0';
            qDebug()<<tmp;
            int j = 0;
            for(j=0; j< strlen(outFname); j++)
                tmp[i+1+j] = outFname[j];
            tmp[i+1+j] = '\0';
            break;
        }
    }
//    qDebug()<<"tmp333";
//    qDebug()<<tmp;
//    ptmp = "C:/Users/11613/Desktop/4.txt";
//    qDebug()<<ptmp;
//    ptmp = "C:/9.txt";
    FILE * fout=fopen(tmp,"wb");
    printf("file has decompress!\n");
	char ch,bit;  node* t=root;
	while(fscanf(fin,"%c",&ch)==1)
	{
		unsigned char ch2=(unsigned char) ch;
		for(int i=7; i>=0; i--)
	    {
	    	if(Count==0) break;
	        if(ch2>=(1<<7))  bit=1; else bit=0;
            ch2=ch2<<1;
		    	if(bit==0)   t=t->lef;   if(bit==1)    t=t->rig;
	    	if(t->lef==NULL && t->rig==NULL)
            { fprintf(fout,"%c",t->ch);  t=root;  Count--; }
	    }
	}
    fclose(fin);  fclose(fout);
    del(root);
}

int huff(int select, char* inFname,char* deFname, char* outFname)
{ 
    qDebug()<<"1111"<<endl;
    //cout<<1<<endl;
    //system("chcp 65001");
    //while(1)
    {
        cout<<endl<<endl;
        qDebug()<<"        ****************************************************\n";
        qDebug()<<"                               menu            \n";
        qDebug()<<"                       1.------compress--------      \n";
        qDebug()<<"                       2.------decompress------      \n";
        qDebug()<<"                       3.------exit--------      \n";
        qDebug()<<"        ****************************************************\n";
        int n;   n = select;         //cin>>n;
        if(n==1)
        {
            qDebug()<<("请输入压缩文件名：  end");   char fname[1000];       //scanf("%s",fname);
//            std::cout<<strlen(inFname)<<std::endl;
            int i=0;
            for(i=0; i<strlen(inFname); i++)
            {
                fname[i] = inFname[i];
            }
            fname[i]= '\0';
            std::cout<<"infname  "<<fname<<endl;
            FILE *fin=fopen(fname,"rb");
            /*统计*/
            calcnt(fin);
            memcpy(cnt2,cnt,sizeof cnt2);
            /*建树并求出字典*/
            root=createtree();
            Count=root->cnt;
            initail();
            code(root);
            /*debug  观察字典 */
            for(int i=0; i<nmax; i++) if(table[i][0]!='\0')
                printf("%c     ",i),     puts(table[i]);
            /*将二进制写入输出文件*/ 
            int len = strlen(fname);
            for( int i = len-1; i>=0; i--)
            {
                if (inFname[i]=='.')
                {
                    char* tmp = ".lwg";
                    int j=0;
                    for(j=0; j<=3; j++)
                        fname[i+j] = tmp[j];
                    fname[i+j] = '\0';
                }
            }
            qDebug()<<"out  "<<fname<<endl;
            FILE *fout=fopen(fname,"wb");
            rewind(fin);
            writediction(fout);
            writebin(fin,fout);
	    	long long fsize1=ftell(fin);  long long fsize2=ftell(fout);
            printf("压缩前字节数: %I64d\n压缩后字节数： %I64d \n",fsize1,fsize2);
            printf("压缩比为：    ");
            printf("%.2lf%%\n",100*(1.0*fsize2/fsize1));
            fclose(fin);  fclose(fout);
            del(root);
	    }
        if(n==2)
	    {  
            qDebug()<<"2222";
            decode(deFname, outFname);
	    }
//	    else if(n==3)  break;
//      else  {  cout<<"输入错误，重新选择！\n";  continue; }
    }
    return 0;
}
