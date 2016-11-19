#include <iostream>
#include <vector>
#include <string>
#include "Userin.h"
#include <string>
#include <cstring>

using namespace std;

int main()
{
	string val1 = "(echo A && echo B) || (echo C && echo D)";
	//getline(cin, val1);

	//vector<string> val1;


	
	userin temp1;
	temp1.parse(val1);
	temp1.printall(val1);
	temp1.callfunct();

	cout << endl << "--ASSIGNMENT 3 TESTING -- " << endl;
	//temp1.test1(val1);


	return 0;
}
