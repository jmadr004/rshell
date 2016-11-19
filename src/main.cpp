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

<<<<<<< HEAD
	//vector<string> val1;
=======
	vector<string> kal1;
>>>>>>> 337c2dde5d6a62d3bc1319905db8a913223d7808


	
	userin temp1;
<<<<<<< HEAD
	temp1.parse(val1);
	temp1.printall(val1);
	temp1.callfunct();

	cout << endl << "--ASSIGNMENT 3 TESTING -- " << endl;
	//temp1.test1(val1);
=======
	//temp1.parse(val1);
	//temp1.printall(val1);
	//temp1.callfunct();

	cout << endl << "--ASSIGNMENT 3 TESTING -- " << endl;
	temp1.test1(val1);
>>>>>>> 337c2dde5d6a62d3bc1319905db8a913223d7808


	return 0;
}
