#ifndef USERIN
#define USERIN

#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


using namespace std;

class userin{
protected:
	string test1= " ";
	std::vector <string > comarg;
	std::vector <string> con;
	std::vector <int> intvec1;
	std::string builder;
	std::string connector;
	int j = 0;
	int k = 0;

	char conectest;
	int valoc = 0 ;
public:
	userin() {};
	~userin() {};
	void funct(vector<string> test1);
	void fill() {
	getline(cin, this->test1);
	}
	void parse();
	void print1(){
		std::cout << std::endl << "the string entered is: " << std::endl << this->test1 << std::endl;

		std::cout << std::endl << "the command/argument string vector is as follow: " << std::endl;
		for (unsigned int i = 0; i < this->comarg.size(); i++)
		{
			std::cout << "[" << i << "]" << comarg.at(i) << std::endl;
		}
		std::cout << std::endl;

		std::cout << "the connector string vector is as follow: " << std::endl;
		for (unsigned int k = 0; k < this->con.size(); k++)
		{
			std::cout << "[" << k << "]" << con.at(k) << std::endl;
		}
		std::cout << std::endl;
	}
};

void userin::parse() {
for (unsigned int i = 0; i < test1.size(); i++)
{
    conectest = test1[i];
    valoc = i;
	
    if ((conectest == ';'))
	{
		
		this->intvec1.push_back(valoc);
		//used to test code//std::cout << intvec1[this->intvec1.size()-1] << std::endl;
		connector += ';';
		this->con.push_back(connector);
		connector.clear();
	}
	else if((conectest == '&'))
	{
		this->intvec1.push_back(valoc);
		//used to test code//std::cout << intvec1[this->intvec1.size()-1] << std::endl;
		i++;
		k = 1;
		connector += '&';
		connector += '&';
		this->con.push_back(connector);
		connector.clear();
	}
	else if ((conectest == '|')) 
	{
		this->intvec1.push_back(valoc);
		//used to test code//std::cout << intvec1[this->intvec1.size()-1] << std::endl;
		i++;
		k = 1;
		connector += '|';
		connector += '|';
		this->con.push_back(connector);
		connector.clear();
	}
	else if ((conectest == ' ')) 
	{
		if (k == 0) 
		{
			this->comarg.push_back(builder);
			//std::cout << builder << std::endl;
			builder = "";
		}
		if (k == 1)
		{
			k = 0;
		}
	}
	else
	{
		builder += conectest;
	}
}
this->comarg.push_back(builder);
funct(comarg);
}

void userin::funct(vector<string> test1)
{
	pid_t child_pid;
	pid_t c;
	int cstatus;
	vector<string> test0 = test1;


	vector<char *> argv(test1.size() + 1);

	for (size_t i = 0; i < test1.size(); i++)
	{
		argv[i] = &test1[i][0];
	}

	child_pid = fork();
	if (child_pid == 0)
	{
		execvp(argv[0], argv.data());
		fprintf(stderr, "child process could not do execvp.\n");
		_exit(1);
	}


	if (child_pid == -1)
	{
		fprintf(stderr, "Fork Falied.\n"); _exit(1);
	}
	else
	{
		c = wait(&cstatus);
		printf("Parent: child %ld exited with status = %d\n",
			(long)c, cstatus);
	}
	argv.clear();
}










#endif