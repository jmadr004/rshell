#include "Userin.h"
#pragma GCC diagnostic ignored "-Wwrite-strings"

void userin::parse() {
	this->k = 0;
	this->j = 0;		
	this->valoc = 0;



	for (unsigned int i = 0; i < test1.size(); i++)
	{
		conectest = test1[i];
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
void userin::print1()
{
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



void userin::callfunct()
{
	string loader;
	string nextloader;
	string nextnextloader;
	char a;
	bool booltest = true;

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
				i++;
				callf.clear();
				if (booltest == true)
				{
					callf.push_back(nextloader);
					//std::cout << nextloader << std::endl;
					booltest = this->funct(callf);
					callf.clear();
					i++;

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
}


void userin::execute()
{
	cout << "logout" << endl;
	exit(0);

}


