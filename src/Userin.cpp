#include "Userin.h"
#pragma GCC diagnostic ignored "-Wwrite-strings"


bool userin::parse(string A) {
	this->k = 0;
	this->j = 0;
	this->valoc = 0;

	//old cleanup and begin parse
	for (unsigned int i = 0; i < A.size(); i++)
	{
		conectest = A[i];
		valoc = i;

		if ((conectest == ';'))
		{
			this->comarg.push_back(builder);
			builder.clear();
			connector += ';';
			this->con.push_back(connector);
			connector.clear();
			k = 1;
		}
		else if ((conectest == '&'))
		{
			this->comarg.push_back(builder);
			builder.clear();
			i++;
			k = 1;
			connector += '&';
			connector += '&';
			this->con.push_back(connector);
			connector.clear();
		}
		else if ((conectest == '|'))
		{
			this->comarg.push_back(builder);
			builder.clear();
			i++;
			k = 1;
			connector += '|';
			connector += '|';
			this->con.push_back(connector);
			connector.clear();
		}
		else if ((conectest == ' '))
		{
			if (builder.size() > 1)
			{
				builder += ' ';
			}
		}
		else
		{
			builder += conectest;
		}
	}
	this->comarg.push_back(builder);
	connector = ';';
	this->con.push_back(connector);

	bool retval = this->callfunct();
	builder.clear();
	return retval;
}


bool userin::funct(vector<string> test1)
{
	bool Bstatus = true;
	char *cstr = new char[test1[0].length() + 1];
	strcpy(cstr, test1[0].c_str());

//	char * val1[] = { cstr };
	char * name[] = {
		"/bin/bash",
		"-c",
		cstr,
		NULL
	};
	
	pid_t child_pid;
	int cstatus;
	child_pid = fork();
	if (child_pid == -1)
	{
		Bstatus = false;
		fprintf(stderr, "Fork Failed. \n");
		_exit(1);
	}
	if (child_pid == 0)
	{
		execvp(name[0], name);
		fprintf(stderr, "child process could not do execvp.\n");
		_exit(1);
	}
	else
	{
		waitpid(child_pid, &cstatus, 0);
		printf("Parent: child %ld exited with status = %d\n", (long)cstatus, cstatus);
	}

	return Bstatus;

}


void userin::printall(string A)
{
	std::cout << std::endl << "the string entered is: " << std::endl << A << std::endl;

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

bool userin::callfunct()
{
	string loader;
	string nextloader;
	string nextnextloader;
	char a;
	bool booltest = true;
	bool retbool = true;

	for (unsigned int i = 0; i < this->comarg.size(); i++)
	{
		//at this point loader has a string in it and nextloader has the next string in it <-- if there even is a next string

		for (unsigned int j = 0; j < this->con.size(); j++)
		{
			loader = comarg.at(i);
			if (i + 1 < this->comarg.size()) { nextloader = comarg.at(i + 1); }
			else { nextloader.clear(); }

			a = this->con[j].at(0);

			// at this point a has first connector ans b has the second connector  <-- if there even is a next connector

			if ((a == ';') && (booltest == true))//call funct and pass loader as an argument
			{
				callf.push_back(loader);
				//std::cout << loader << std::endl;
				booltest = this->funct(callf);
				callf.clear();
				i++;
			}
			if (a == '&' && (booltest == true))//call funct and pass loader as first arg and nextloader as second arg
			{
				callf.push_back(loader);
				//std::cout << loader << std::endl;
				booltest = this->funct(callf);
				retbool = booltest;
				i++;
				callf.clear();
				if (booltest == true)
				{
					callf.push_back(nextloader);
					//std::cout << nextloader << std::endl;
					booltest = this->funct(callf);
					if (booltest == true)
					{
						retbool = false;
					}
					callf.clear();
					i++;
					j++;
				}
				
			}
			if ((a == '|') && (booltest == false)) //call funct and pass first argument   !! IF !! it fails then pass second argument
			{
				if (i != 0)
				{
					//execute loader then
					callf.push_back(loader);
					booltest = this->funct(callf);
					//std::cout << loader << std::endl;
					callf.clear();
					i++;

					if (booltest == false)
					{
						callf.push_back(nextloader);
						booltest = this->funct(callf);
						//std::cout << loader << std::endl;
						callf.clear();
						i++;
						j++;
					}
				}
			}
			if ((a == '|') && (booltest == true))
				{
					i++;
					j++;
				}
		}
	}

	comarg.clear();
	con.clear();
	loader.clear();
	nextloader.clear();

	return retbool;
}
void userin::functest0(string A)
{
	//variables used here
	char m = ' ';
	string whoa;
	vector<string> B;
	//end of variables used

	for (unsigned int i = 0; i < A.size(); i++)
	{
		m = A[i];
		if (m == '(')
		{
			i++;
			m = A[i];
			while (m != ')')
			{
				whoa += A[i];
				i++;
				m = A[i];
			}
			cout << whoa << endl;
			B.push_back(whoa);
			whoa.clear();
		}
	}
	
	cout << endl;
	this->par1(B);
}

void userin::par1(vector<string> A)
{
	string loader;
	string nextloader;
	string nextnextloader;
	bool parbool = true;
	//cout << A[0] << endl << A[1] << endl;

	//this->parse(A.at(0)); //execute first parentheses
	//this->parse(A.at(1)); //execute second parentheses
	
	
	for (unsigned int k = 0; k < A.size(); k++)
	{
		if (parbool == true)
		{
			parbool = this->parse(A.at(k));
		}
	}
}

void userin::execute()
{
	cout << "logout" << endl;
	exit(0);

}



//calltestfunc calls the test function after ensuring that there is a
//left and right [] or a "test", if not found a cout statement is called with a test error returning a negative value
int userin::calltestfunc(vector<string> tstring)
{
	string Atest1;
	Atest1 = accumulate(tstring.begin(),tstring.end(), Atest1);

	string test2;
	test2 = accumulate(tstring.begin(),tstring.end(), test2);

	//takes in a vector<string> from the call funct command and checks for [] or test call
	if ((Atest1.at(0) == '[') && Atest1.at(Atest1.size() - 1) == ']')
	{
		//The [] need to be removed to run the stat command this will remove the left and right []'s
		test2 = Atest1.substr(1, Atest1.size() - 2);
		//passing the now cleaned up test case to the test function
		testfunc(test2);
		return 0;
	}
	else if (Atest1.compare(0, 4, "test") == 0)//checks to see if not [] that a test value is passed
	{
		//removes the test value from the string which is not need for the stat function to run
		test2 = Atest1.substr(5, Atest1.size() - 1);
		//passes the cleaned vector<string> to testfunction
		testfunc(test2);
		return 0;
	}
	else
	{
		//if the cases are not found a error is printed to the screen
		cout << "Test error" << endl;
		return -1;
	}

}

//testfunc uses the stat test to test to see if the values passes by the user are a directory 

int userin::testfunc(string teststring)
{
	//checks to see if the the position at zero has a flag command if not the default of -e is entered
	if (teststring[0] != '-')
	{
		teststring.insert(0,"-e");
	}
	//creates a char array and sets it to the size of the passed teststring
	char *cstr = new char[teststring.length() + 1];
	//cstr now holds a cstring of teststring
	strcpy(cstr, teststring.c_str());
	//in order to prevent errors from user input we want to remove all the spaces
	char* rem_cstr = strtok(cstr, " ");
	//creating an array to hold the now space removed cstr
	char* carray[100];
	//initialize a int to transverse rem_cstr and input it into carray
	int inull = 0;
//	using a while loop to transverse the array, the loop will stop when rem_cstr equals a 0
	while (rem_cstr != 0)
	{
		carray[inull++] = rem_cstr;
		rem_cstr = strtok(NULL, " ");
	}
	//this ensured that there is a null character at the end of carray to ensure that the stat function works
	carray[inull] = NULL;
	//stat function to return information about a file
	struct stat sb;
	stat(carray[1], &sb);
		//checks to see if the value at position zero/zero of the array is a flag
		//the second part checks to see if position zero/one of the array if an e for  file/directory exists
		if (carray[0][0] == '-' &&  carray[0][1] == 'e')
		{
			if (S_ISDIR(sb.st_mode) || S_ISREG(sb.st_mode)) //S_ISDIR is the directory? call
			{
				cout << "(TRUE)" << endl; //if the file is a directory a true value call is printed and a 0 is returned
				return 0;
			}
			else
			{
				cout << "(FALSE)" << endl; //if it fails then a false if printed and a 1 returned
				return 1;
			}
		}		//the second part checks to see if position zero/one of the array if an d for  file/directory exists
		else if (carray[0][0] == '-' && carray[0][1] == 'd')
		{
			if (S_ISDIR(sb.st_mode)) //S_ISDIR is the directory? call
			{
				cout << "(TRUE)" << endl;//if the file is a directory a true value call is printed and a 0 is returned
				return 0;
			}
			else
			{
				cout << "(FALSE)" << endl;//if it fails then a false if printed and a 1 returned
				return 1;
			}
		}
	//the second part checks to see if position zero/one of the array if an f for  file/directory exists
		else if (carray[0][0] == '-' && carray[0][1] == 'f')
		{
			if (S_ISREG(sb.st_mode))
			{
				cout << "(TRUE)" << endl;
				return 0;
			}
			else
			{
				cout << "(FALSE)" << endl;//if it fails then a false if printed and a 1 returned
				return 1;
			}
		}
};

