#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LexicAnalyser.cpp"

using namespace std;

char c,d1[2];
int i;
void match();
void statement_list();
void decision_stat();

void reset(char * str)
{
	for(int i=0;i<100;i++)
		str[i] = '\0';
}

void error()
{
	cout<<"\nwrong grammar\n";
	exit(0);
}

void match()
{
	i++;
	c = s1[i];
}

void nextToken()
{
	getToken();
	i=-1;
	match();
}

void id()
{
	if((c>=65 && c<=90) || (c>=97 && c<=122) || c=='_')
	{	
		while((c>=65 && c<=90) || (c>=97 && c<=122) || c=='_' || (c>=48 && c<= 57))
		{
			match();
		}
		nextToken();
	}
	
	else
	{
		cout<<"\nexpected id at line number - "<<ln<<endl;
		exit(0);
	}
}

void num()
{
	if(c>=48 && c<=57)
	{
	while(c>=48 && c<=57)
		match();
	nextToken();
	}

	else
	{
		cout<<"\nexpected num at line number - "<<ln<<endl;
		exit(0);
	}
}



void factor()
{
	if((c>=65 && c<=90) || (c>=97 && c<=122) || c=='_')
	{
		id();
	}
	
	else if(c>=48 && c<=57)
	{	
		num();
	}
	
	else
	{
		cout<<"\nexpected num or id at line - "<<ln<<endl;
		exit(0);
	}
}

void dprime()
{
	if(strcmp(s1,"else")==0)
	{
		nextToken();
		
		if(strcmp(s1,"if")==0)
		{
			nextToken();
			decision_stat();
		}
		
		else if(c == '{')
		{
			nextToken();
			statement_list();
			
			if(c == '}')
			{
				nextToken();
			}
			else 
			{
				cout<<"\nexpected } at line "<<ln<<endl;
				error();
			}
		}
		else 
		{
			cout<<"\nexpected { at line "<<ln<<endl;
			error();
		}
	}
}

void relop()
{
	if(c=='<' || c=='>' || c=='=' || c=='!')
	{
		match();
		if(c=='=')
		{
			nextToken();
		}
		else
			nextToken();
	}
	else 
	{
		cout<<"\nexpected <,>,= or ! at line "<<ln<<endl;
		error();
	}
}

void addop()
{
	if(c=='+' || c=='-')
	{
		nextToken();
	}
	
	else 
	{
		cout<<"\nexpected + or - at line "<<ln<<endl;
		error();
	}
}

void mulop()
{
	if(c=='*' || c=='/')
	{
		nextToken();
	}
	
	else 
	{
		cout<<"\nexpected * or / at line "<<ln<<endl;
		error();
	}
}

void tprime()
{
	if(c=='*' || c=='/')
	{
		mulop();
		factor();
		tprime();
	}
}

void term()
{
	factor();
	tprime();
}

void seprime()
{
	if(c=='+' || c=='-')
	{
		addop();
		term();
		seprime();
	}
}

void simple_expn()
{
	term();
	seprime();
}

void eprime()
{
	if(c=='<' || c=='>' || c=='=' || c=='!')
	{
		relop();
		simple_expn();
	}
}

void expn()
{
	simple_expn();
	eprime();
}

void assign_stat()
{
	id();
	if(c == '=')
	{	
		nextToken();
		expn();
	}	
	
	else if(c == '-')
	{
		nextToken();
		if(c == '-')
		{
			nextToken();
		}
		else 
		{
			cout<<"\nexpected - at line "<<ln<<endl;
			error();
		}
	}
	
	else if(c == '+')
	{
		nextToken();
		if(c == '+')
		{
			nextToken();
		}
		else 
		{
			cout<<"\nexpected + at line "<<ln<<endl;
			error();
		}
	}
		
	else 
	{
		cout<<"\nexpected =,- or + at line "<<ln<<endl;
		error();
	}
	
}

void decision_stat()
{
	if(c == '(')
	{
		nextToken();
		expn();
		if(c == ')')
		{
			nextToken();
			if(c=='{')
			{
				nextToken();
				statement_list();
				if(c=='}')
				{
					nextToken();
					dprime();
				}
				
				else 
				{
					cout<<"\nexpected } at line "<<ln<<endl;
					error();
				}
			}
			
			else 
			{
				cout<<"\nexpected { at line "<<ln<<endl;
				error();
			}
		}
		
		else 
		{
			cout<<"\nexpected ) at line "<<ln<<endl;
			error();
		}		
	}
	
	else 
	{
		cout<<"\nexpected ( at line "<<ln<<endl;
		error();
	}
}

void loop_stat()
{
	if(strcmp(s1,"for")==0)
	{
		nextToken();
		if(c=='(')
		{
			nextToken();
			assign_stat();
			if(c==';')
			{
				nextToken();
				expn();
				if(c==';')
				{
					nextToken();
					assign_stat();
					if(c==')')
					{
						nextToken();
						if(c=='{')
						{
							nextToken();
							statement_list();
							if(c=='}')
							{
								nextToken();
							}
							else 
							{
								cout<<"\nexpected } at the line "<<ln<<endl;
								error();
							}
						}
						else 
						{
							cout<<"\nexpected { at the line "<<ln<<endl;
							error();
						}
					}
					else 
					{
						cout<<"\nexpected ) at line "<<ln<<endl;
						error();
					}
				}
				else 
				{
					cout<<"\nexpected ; at line "<<ln<<endl;
					error();
				}
			}
			else 
			{
				cout<<"\nexpected ; at line "<<ln<<endl;
				error();
			}
		}
		else 
		{
			cout<<"\nexpected ( at line "<<ln<<endl;
			error();
		}
	}
	
	else if(strcmp(s1,"while")==0)
	{
		nextToken();
		if(c=='(')
		{
			nextToken();
			expn();
			if(c==')')
			{
				nextToken();
				if(c=='{')
				{
					nextToken();
					statement_list();
					if(c=='}')
					{
						nextToken();
					}
					else 
					{
						cout<<"\nexpected } at line "<<ln<<endl;
						error();
					}
				}
				else 
				{
					cout<<"\nexpected { at line "<<ln<<endl;
					error();
				}
			}
			else 
			{
				cout<<"\nexpected ) at line "<<ln<<endl;
				error();
			}
		}
		else 
		{
			cout<<"\nexpected ( at line "<<ln<<endl;
			error();
		}
	}
}

void statement()
{
	if(strcmp(s1,"if")==0)
	{
		nextToken();
		decision_stat();
	}
	
	else if(strcmp(s1,"for")==0 || strcmp(s1,"while")==0)
	{
		loop_stat();
	}
	
	else
	{
		assign_stat();
		if(c == ';')
			nextToken();
		else 
		{
			cout<<"\nexpected ; at line "<<ln<<endl;
			error();
		}
	}
}

void statement_list()
{
	if((c>=65 && c<=90) || (c>=97 && c<=122) || c=='_')
	{
		statement();
		statement_list();
	}
}

void identifier_list()
{
	id();
	if(c == '[')
	{
		nextToken();
		num();
		if(c == ']')
			nextToken();
		else 
		{
			cout<<"\nexpected ] at line "<<ln<<endl;
			error();
		}
	}
	if(c == ',')
	{
		nextToken();
		identifier_list();
	}
}

void data_type()
{
	if(strcmp(s1,"int") == 0 || strcmp(s1,"char") == 0 || strcmp(s1,"float")==0 || strcmp(s1,"double")==0)
	{
		nextToken();
	}
}

void declarations()
{
	if(strcmp(s1,"int")==0 || strcmp(s1,"char")==0 || strcmp(s1,"float")==0 || strcmp(s1,"double")==0)
	{
		data_type();
		identifier_list();
		if(c==';')
		{
			nextToken();
			declarations();
		}
		
		else 
		{
			cout<<"\nexpected ; at line "<<ln<<endl;
			error();
		}
	}
}

void program()
{
	if(strcmp(s1,"main")==0)
	{
		nextToken();
		if(c=='(')
		{
			nextToken();
			if(c==')')
			{
				nextToken();
				if(c=='{')
				{
					nextToken();
					declarations();
					statement_list();
					if(c=='}')
						nextToken();
					else 
					{
					cout<<"\nexpected } at line "<<ln<<endl;
					error();
					}
				}
				else 
				{
					cout<<"\nexpected { at line "<<ln<<endl;
					error();
				}
			}
			else 
			{
				cout<<"\nexpected ) at line "<<ln<<endl;
				error();
			}
		}
		else 
		{
			cout<<"\nexpected ( at line "<<ln<<endl;
			error();
		}
	}
	else 
	{
		cout<<"\nexpected main at line "<<ln<<endl;
		error();
	}
}

int main()
{
	i=0;
	getToken();
	program();
	if(d == EOF)
		cout<<"\nprogram accepted\n";
	else
		error();
	return 0;
}
