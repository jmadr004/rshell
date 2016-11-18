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
#include <signal.h>
#include <cstring>

using namespace std;

class userin {
protected:
	string test1;
	//string test1= " ";
	std::vector <string > comarg;
	std::vector <string> con;
	std::vector <string> callf;
	std::string builder;
	std::string connector;
	int j;
	int k;
	char conectest;
	int valoc;


public:
	userin() {};
	~userin() {};
	void fill() { getline(cin, this->test1); }
	void parse();
	void print1();
	void callfunct();
	void funct(vector<string> test1);
};


#endif
