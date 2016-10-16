#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>

using namespace std;

FILE *fp = fopen("sample.c","r");
int ptr=0,flag=0,ln=1;
char d;
char f = EOF;
char s1[100];

void reset(char *d,int ptr)
{
	for(int i=0;i<ptr;i++)
		d[i] = '\0';
}

void getToken()
{
	reset(s1,100);
	if(flag==0)
		d = getc(fp);
	else
		flag=0;
	if(d != f)
	{
		if(d=='\n' || d==' ' || d=='\t')
		{
			while(d=='\n' || d==' ' || d=='\t')
			{	
				if(d=='\n')
					ln++;
				d= getc(fp);
			}
		}
		
		if(d == '"')
		{
		d=getc(fp);
			while(d!='"')
			{
				d=getc(fp);
			}
		d=getc(fp);
		}
		
		while(d!=' ' && d!='\t' && d!='\n' && d!=',' && d!=';' && d!='[' && d!= ']' && d!= '(' && d!=')' && d!='{' && d!='}' && d!='=' && d!='<' && d!='>' && d!='!' && d!='+' && d!='-' && d!='*' && d!='/' && d!='^' && d!=EOF)
		{
			s1[ptr++] = d;
			d = getc(fp);
		}
		
		if(ptr>0)
		{
			ptr=0;
			cout<<endl<<"new token - "<<s1<<endl;
			flag = 1;
			return;
		}
		
		if(d==',' || d==';' || d=='[' || d==']' || d=='(' || d==')' || d=='{' || d=='}' || d=='+' || d=='-' || d=='*' || d=='/' || d=='^')
		{
			s1[0] = d;
			cout<<endl<<"new token - "<<s1<<endl;
			return;
		}
		
		if(d=='=' || d=='<' || d=='>' || d=='!')
		{
			s1[0]=d;
			d = getc(fp);
			if(d=='=')
			{
				s1[1]=d;
				s1[2] = '\0';
				cout<<endl<<"new token - "<<s1<<endl;
				return;
			}
			else
			{
				flag=1;
				cout<<endl<<"new token - "<<s1<<endl;
				return;
			}
		}
	}
}
