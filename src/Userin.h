#ifndef USERIN
#define USERIN

#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <cstring>
#include <stdlib.h>
#include <numeric>

using namespace std;

class userin {
protected:
	//string test1;
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
	bool parse(string A);
	void printall(string A);
	bool callfunct();

	bool funct(vector<string> test1);
	void test1(string A);
	void par1(vector<string> A);
	int testfunc(string teststring);
	int calltestfunc(vector<string> teststring);
	void execute();
};



#endif
