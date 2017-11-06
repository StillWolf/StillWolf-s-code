#include<stdio.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstring>
#include<list>
using namespace std;
const int SIZE=505;
char inputFile[SIZE],outputFile[SIZE];
char x;
int currentLine;
char Text[SIZE];//Modified
list<char *> buffer;
void ViewBuffer()
{
	list<char *>::iterator i;
	//cout<<*--buffer.end()<<endl;
	for(i=buffer.begin();i!=buffer.end();i++)
		puts(*i);
}
char * FindString(int n)
{
	int t=0;
	list<char *>::iterator i;
	for(i=buffer.begin();i!=buffer.end();i++)
	{
		if(t==n)
		{
			return *i;
			break;
		}
		else
			t++;
	}
}
void outputCurrent()
{
	if(buffer.empty())
	{
		printf("File buffer is empty(please use command r to read file to buffer).\n");
		return ;
	}
	printf("%d : ",currentLine);
	puts(FindString(currentLine));
	//ViewBuffer();
	//printf("\n");
}
void InsertString(int pos,char * Text)
{
	int t=0;
	list<char *>::iterator i;
	for(i=buffer.begin();i!=buffer.end();i++)
	{
		if(t==pos)
		{
			buffer.insert(i,Text);
			break;
		}
		else
			t++;
	}
}
void ReadDatainFile()
{
	ifstream fin(inputFile);
	buffer.clear();
    char *data=new char [SIZE];
    while(fin.getline(data,SIZE))
    {
    	buffer.push_back(data);
    	data=new char [SIZE];
	}
	currentLine=buffer.size()-1;
	return ;
}
void opHelp()
{
	printf("Valid commands are: b(egin) c(hange) d(el) e(nd)\n");
	printf("f(ind) g(o) h(elp) i(nsert) l(ength) n(ext) p(rior)\n");
	printf("q(uit) r(ead) s(ubstitute) v(iew) w(rite)\n");
}
void MoveTo(int pos)
{
	if(buffer.empty())
		printf(" Warning: empty buffer\n");
	else
		currentLine=pos;
}
void ChangeStringTo(int pos,char *newc)
{
	int t=0;
	//char *data=new char [SIZE];
	list<char *>::iterator i;
	if(pos==buffer.size()-1)
	{
		buffer.pop_back();
		buffer.push_back(newc);
		//cout<<*)--buffer.end()<<endl;
		return ;
	}
	for(i=buffer.begin();i!=buffer.end();i++)
	{
		if(t==pos)
		{
			buffer.insert(i,newc);
			buffer.erase(++i);
			//data=new char [SIZE];
			break;
		}
		else
			t++;
	}
}
void ChangeBuffer()
{
	int i,j;
	char Text[SIZE],NewText[SIZE];
	char* now;
	if(buffer.empty())
	{
		printf(" Warning: empty file\n");
		return ;
	}
	printf(" What text segment do you want to replace? ");
	gets(Text);
	printf(" What new text segment do you want to add in? ");
	gets(NewText);
	now=FindString(currentLine);
	int ln=strlen(now),lt=strlen(Text),la=strlen(NewText),post=-1;
	for(i=0;i<ln-lt+1;i++)
	{
		for(j=0;j<lt;j++)
			if(now[i+j]!=Text[j])
				break;
		if(j!=lt)
			continue;
		post=i;
		break;
	}
	if(post==-1)
		printf(" Error: Substitution failed\n");
	else
	{
		if(lt>la)
		{
			for(i=post;i<post+la;i++)
				now[i]=NewText[i-post];
			for(i=post+la;i<ln-(lt-la);i++)
				now[i]=now[i+(lt-la)];
			ln-=(lt-la);
			now[ln]=0;
		}
		else
		{
			for(i=ln+(la-lt-1);i>=post+lt;i--)
				now[i]=now[i-(la-lt)];
			for(i=post;i<post+la;i++)
				now[i]=NewText[i-post];
			ln+=(la-lt);
			now[ln]=0;
		}
	}
	ChangeStringTo(currentLine,now);
}
void DeleteByLine(int pos)
{
	int t=0;
	if(pos==buffer.size()-1)
	{
		if(currentLine)
			currentLine--;
		buffer.pop_back();
		return ;
	}
	list<char *>::iterator i;
	for(i=buffer.begin();i!=buffer.end();i++)
	{
		if(t==pos)
		{
			buffer.erase(i);
			break;
		}
		else
			t++;
	} 
}
void DeleteBuffer()
{
	if(buffer.empty())
	{
		printf(" Error: Deletion failed\n");
		return ;
	}
	DeleteByLine(currentLine);
}
void FindNow()
{
	int i,j,ln,lt,post=-1;
	char Text[SIZE];
	char * now;
	if(buffer.empty())
	{
		printf(" Warning: empty file\n");
		return ;
	}
	printf(" Enter string to search for:\n");
	gets(Text);
	now=FindString(currentLine);
	lt=strlen(Text);
	ln=strlen(now);
	for(i=0;i<ln-lt+1;i++)
	{
		for(j=0;j<lt;j++)
			if(now[i+j]!=Text[j])
				break;
		if(j!=lt)
			continue;
		post=i;
		break;
	}
	if(post==-1)
		printf(" String was not found.\n");
	else
	{
		puts(now);
		for(i=0;i<post;i++)
			printf(" ");
		for(i=1;i<=lt;i++)
			printf("^");
		printf("\n");
	}
}
void GoByLine()
{
	//char x;
	int posLine;
	printf(" Goto what line number? ");
	scanf("%d",&posLine);
	scanf("%c",&x);
	if(posLine<0||posLine>=buffer.size())
	{
		printf(" Warning: No such line\n");
		return ;
	}
	currentLine=posLine;
}
void Insert()
{
	int pos;
	char Text[SIZE];
	printf(" Insert what line number? ");
	scanf("%d",&pos);
	scanf("%c",&x);
	printf(" What is the new line to insert? ");
	gets(Text);
	if(pos<0||pos>=buffer.size())
	{
		printf(" Error: Insertion failed\n");
		return ;
	}
	InsertString(pos,Text);
	currentLine=pos;
}
void Lenth()
{
	printf("There are %d lines in the file.\n",buffer.size());
}
void NextLine()
{
	if(currentLine>=buffer.size()-1)
	{
		printf(" Warning: at end of buffer\n");
		return ;
	}
	currentLine++;
}
void PreLine()
{
	if(currentLine==0)
	{
		printf(" Warning: at start of buffer\n");
		return ;
	}
	currentLine--;
}
void WriteBuffer()
{
	ofstream fout(outputFile);
	list<char *>::iterator i;
	for(i=buffer.begin();i!=buffer.end();i++)
		fout<<*i<<endl;
}
void ReplaceString()
{
	char Text[SIZE];
	int pos;
	printf(" Substitute what line number? ");
	scanf("%d",&pos);
	scanf("%c",&x);
	if(pos<0||pos>=buffer.size())
	{
		printf(" Error: Substitution failed\n");
		return ;
	}
	printf(" What is the new line to substitute?\n");
	gets(::Text);//Modified
	//cout<<Text;
	ChangeStringTo(pos,::Text); //Modified
	
	//cout<<*--buffer.end()<<endl;
	currentLine=pos;
}
void work()
{
	char op[SIZE];
	while(1)
	{
		//ViewBuffer();
		printf("??");
		gets(op);
		if(op[0]=='h')
		{
			opHelp();
			outputCurrent();
			continue;
		}
		if(op[0]=='b')
		{
			MoveTo(0);
			outputCurrent();
			continue;
		}
		if(op[0]=='c')
		{
			ChangeBuffer();
			outputCurrent();
			continue;
		}
		if(op[0]=='d')
		{
			DeleteBuffer();
			outputCurrent();
			continue;
		}
		if(op[0]=='e')
		{
			MoveTo(buffer.size()-1);
			outputCurrent();
			continue;
		}
		if(op[0]=='f')
		{
			FindNow();
			outputCurrent();
			continue;
		}
		if(op[0]=='g')
		{
			GoByLine();
			outputCurrent();
			continue;
		}
		if(op[0]=='i')
		{
			Insert();
			outputCurrent();
			continue;
		}
		if(op[0]=='l')
		{
			Lenth();
			outputCurrent();
			continue;
		}
		if(op[0]=='n')
		{
			NextLine();
			outputCurrent();
			continue;
		}
		if(op[0]=='p')
		{
			PreLine();
			outputCurrent();
			continue;
		}
		if(op[0]=='q')
			exit(0);
		if(op[0]=='r')
		{
			ReadDatainFile();
			outputCurrent();
			continue;
		}
		if(op[0]=='v')
		{
			ViewBuffer();
			outputCurrent();
			continue;
		}
		if(op[0]=='w')
		{
			WriteBuffer();
			outputCurrent();
			continue;
		}
		if(op[0]=='s')
		{
			ReplaceString();
			outputCurrent();
			continue;
		}
		printf("Press h or ? for help or enter a valid command:\n");
		outputCurrent();
	}
}
int main()
{
	printf("Please input inputfile name(eg. file_in.txt):");
	gets(inputFile);
	printf("Please input outputfile name(eg. file_out.txt):");
	gets(outputFile);
	printf("File buffer is empty(please use command r to read file to buffer).\n");
	work();
	return 0;
}

