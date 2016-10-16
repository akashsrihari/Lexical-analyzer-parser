#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

using namespace std;

char str[100],stk[100],sym,pst[100];
int tos=0,ptr=0,j=0,stk1[100];

void resetStk()
{
	for(int i=0;i<100;i++)
		stk[i] = '\0';
	tos=0;
}

int F(char symbol)
{
	switch(symbol)
	{
		case '-':
		case '+': return 2;
		
		case '%':
		case '*':
		case '/': return 4;
		
		case '^':
		case '$': return 5;
		
		case '(': return 0;
		case '#': return -1;
		
		default : return 8;
	}
}

int G(char symbol)
{
	switch(symbol)
	{
		case '-':
		case '+': return 1;
		
		case '%':
		case '*':
		case '/': return 3;
		
		case '^':
		case '$': return 6;
		
		case '(': return 9;
		case ')': return 0;
		
		default : return 7;
	}
}

void post()
{
	stk[tos]='#';
	for(int i=0;i<strlen(str);i++)
	{
		sym = str[i];
		while(F(stk[tos])>G(sym))
		{
			pst[j] = stk[tos--];
			j++;
		}
		
		if(F(stk[tos])!=G(sym))
			stk[++tos] = sym;
		
		else
			tos--;
	}
	
	while(stk[tos]!='#')
	{
		pst[j++] = stk[tos--];
	}
}

int main()
{
	cout<<"\nenter infix expression - ";
	cin>>str;
	int x=0;
	post();
	cout<<"\npostfix exp is - "<<pst<<endl;
	resetStk();
	for(int i=0;i<strlen(pst);i++)
	{
		if(((pst[i]-48)>=0) && ((pst[i]-48)<=9))
		{
			cout<<"\nMOV R"<<tos<<",#"<<pst[i];
			stk1[tos++] = pst[i]-48;
		}
		
		else if(pst[i]=='+')
		{
			x = stk1[tos-1] + stk1[tos-2];
			stk1[tos-2] = x;
			cout<<"\nADD R"<<tos-1<<",R"<<tos-2;
			tos = tos-1;
		}
		
		else if(pst[i]=='*')
		{
			x = stk1[tos-1] * stk1[tos-2];
			stk1[tos-2] = x;
			cout<<"\nMUL R"<<tos-1<<",R"<<tos-2;
			tos = tos-1;
		}
		
		else if(pst[i]=='/')
		{
			x = stk1[tos-2] / stk1[tos-1];
			stk1[tos-2] = x;
			cout<<"\nDIV R"<<tos-2<<",R"<<tos-1;
			tos = tos-1;
		}
		
		else if(pst[i]=='-')
		{
			x = stk1[tos-2] - stk1[tos-1];
			stk1[tos-2] = x;
			cout<<"\nSUB R"<<tos-2<<",R"<<tos-1;
			tos = tos-1;
		}
		
		else if(pst[i]=='%')
		{
			x = stk1[tos-2] % stk1[tos-1];
			stk1[tos-2] = x;
			cout<<"\nMOD R"<<tos-2<<",R"<<tos-1;
			tos = tos-1;
		}
		
		else if(pst[i]=='^')
		{
			x = pow(stk1[tos-2],stk1[tos-1]);
			stk1[tos-2] = x;
			cout<<"\nPOW R"<<tos-2<<",R"<<tos-1;
			tos = tos-1;
		}
	}
	if(tos==1)
	{
		cout<<"\nresult is "<<stk1[tos-1]<<endl;
	}
	else
	{
		cout<<"\ninvalid exp\n";
		return 0;
	}
}
