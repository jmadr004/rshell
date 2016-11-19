#INSTALLATION
git clone https://github.com/jmadr004/rshell.git
cd rshell
#INTRODUCTION
The purpose of this program is to further expand on the code created in assignment 2. This program will add the functionality of the test command in our rshell, as well as its symbolic equivalent []. To implement this code, we will use a second parse function within our Userin functionality. The send parse function will parse the input entered by the user and search out the test command or its equivalent [], the parse will also check to see if any flags are passed by the user, and in the case of no test flags assign a base flag of -e. The program will be able to run single or multiple commands, to include running commands with the test case and multiple flags.

#ALGORITHM
In order to execute multiple commands, we build a parse function that recursively run execvp on all commands entered. This was built by taking in a command line from the user and puts into a string. From there we call the first parse function which parses the command and adds all found commands into a vector of strings. This is done by checking postfix notation.

#Known Bugs
Currently there is an issue with the make file where in we are having an error when make is called.

