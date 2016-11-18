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

	bool retval =this->callfunct();
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

void userin::par1(vector<string> A)
{
	string loader;
	string nextloader;
	string nextnextloader;
	char a;
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


