#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>



using namespace std;
 
int main(void)
{
	pid_t child_pid;
	pid_t c;
	int cstatus;
	vector<string> test1;
	string test2 = "ls";
	string test3 = "-a";
        string test7 = "&&";
	string test4 = "echo";
	string test5 = "please god work";
	test1.push_back(test2);
	test1.push_back(test3);
	test1.push_back(test7);
	test1.push_back(test4);
        test1.push_back(test5);

	vector<char *> argv(test1.size() + 1);
	
	for (size_t i = 0; i < test1.size(); i++)
	{
		argv[i] = &test1[i][0];
	}

	child_pid = fork();
	if(child_pid ==0)
	{	
	execvp(argv[0], argv.data());
	fprintf(stderr, "child process could not do execvp.\n");
	_exit(1);
	}
	
	
	 if(child_pid == -1)
	 {
	  fprintf(stderr,"Fork Falied.\n"); _exit(1);
	 }
	 else
         {
           c =wait(&cstatus);
           printf("Parent: child %ld exited with status = %d\n",
			(long) c, cstatus); 
         }
	
	
	return 0;

}

