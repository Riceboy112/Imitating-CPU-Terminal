// Name:        Nicholas Kong
// Date Due:    March 8, 2020

#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <dirent.h>
using namespace std;



// Displays functional help command
void help_command()
{
    cout << "command: 'ls'  --> list files" << endl;
    cout << "command: 'pwd' --> current working directory" << endl;
    cout << "command: 'hostname'    --> display hostname and domain name" << endl;
    cout << "command: 'whoami'  --> display username" << endl;
    cout << "command: 'open'  --> opens file option" << endl;
    cout << "command: 'cd [arg]' --> goes into directory" << endl;
    cout << "command: 'mkdir [arg]'  --> makes a new directory" << endl;
}



// This will stop the terminal program
int exit_command(int exit_now)
{
    cout << "logout" << endl;
    cout << "Connection to terminal closed." << endl;
    exit(0);
}



void cd_command(string command, string argument)
{
    // If we select cd, will check to see if it has argument
    if(command == "cd")
    {
        //cout << "This is command 0: " << command_argument_parse[0] << endl;
        //cout << "This is command 1: " << command_argument_parse[1] << endl;
        // If cd has no argument, will send user back to home
        if(argument == "")
        {
            chdir(getenv("HOME"));
            //continue;
        }
        // If there is an argument, it will cd into the directory.
        else
        {
            
            char* args_cd[2];
            string path;
            path = argument;
            args_cd[1] = (char*)path.c_str();
            int directory = chdir(args_cd[1]);
            if(directory == -1)
            {
                cout << "-bash: " << command << ": " << argument;
                cout << ": No such file or directory" << endl;
            }
            /*
             else
             {
             cout << "This is args[0]: " << args_cd[0] << endl;
             cout << "This is args[1]: " << args_cd[1] << endl;
             }
             */
        }
       // continue;
    }
}


// Runs commands with 0 arguments
void no_argument(string command)
{
    char* args[2];
    args[0] = (char*)command.c_str(); // Converts the command to a c string
    args[1] = 0; // There is no argument
    pid_t pid = fork(); // Creates a child process
    
    // If incorrect command was entered, display error message
    if(pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            cout << "-bash: " << command << ": Command not found." << endl;
        }
        exit(0); // This kills child process when command is not found.
    }
    // Needed to seperate spaces if incorrect command was entered
    if (pid > 0)
    {
        if (wait(0) == -1){
            perror("Loading...");
        }
    }
};



// Runs commands with one argument
void arguments(string command, string argument)
{
    char* args[3];
    args[0] = (char*)command.c_str(); // Converts the command to a c string
    args[1] = (char*)argument.c_str(); // Converts the argument to a c string
    args[2] = 0; // There is no second argument
    pid_t pid = fork(); // Creats a child process
    
    // If incorrect command was entered, display error message
    if(pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            cout << "-bash: " << command << " " << argument << ": Command not found." << endl;
        }
        exit(0); // This kills child process when command is not found.
    }
    // Needed to seperate spaces if incorrect command was entered
    if (pid > 0)
    {
        if (wait(0) == -1){
            perror("Loading...");
        }
    }
};



// The Terminal program that controls commands
void terminal(string username)
{
    string user_command; // String that will hold user inputted commands
    // While loop that does not break unless "exit" is entered
    while(user_command != "exit")
    {
        int argument_number = 0; // Keeps track of the amount of arguments entered
        bool command_argument = false; // True if it has an argument, false if it has no argument
        
        // Will parse the command argument entered
        vector<string> command_argument_parse;
        
        // Sets up the basic terminal
        cout << "(base) " << username << "$ ";
        getline(cin, user_command);
        
        // If the user simply presses enter without any value, display the prompt again
        if(user_command == "")
        {
            continue;
        }
        
        // Displays all functions supported by terminal program
        else if(user_command == "help")
        {
            help_command();
            continue;
        }
        
        // Use to split the string by whitespaces
        istringstream split_command;
        split_command.str(user_command);
        
        // Splits all the words from user_command
        do
        {
            string temp;
            split_command >> temp;
            command_argument_parse.push_back(temp);
        }
        while(split_command);
        
        // Gets the number of arguments in the command line
        for (int i = 0; i < command_argument_parse.size()-1; i++)
        {
            argument_number++;
        }
        
        // Sets true if command has arguments
        if (argument_number > 1)
        {
            command_argument = true;
        }
        // Set false if command does not have argument
        else
        {
            command_argument = false;
        }
        
        //If the user types "exit", it exits out of the program.
        if (command_argument_parse[0] == "exit")
        {
            int exit = 0;
            exit_command(exit);
            break;
        }
        
        // Command cd will close child process before command executes, this will make cd work.
        if(command_argument_parse[0] == "cd")
        {
            // Calls to cd_command with two arguments
            cd_command(command_argument_parse[0], command_argument_parse[1]);
            continue;
        }

        // If command has no arguments, go to function that handles no arguments
        if(command_argument == false)
        {
            // Calls to no_argument function since it only has a command and no argument
            no_argument(command_argument_parse[0]);
            //cout << endl;
        }
        
        // If command has arguments, go to function that handles arguments
        if(command_argument == true)
        {
            // Calls to arguments function. It will send the command over along with the argument.
            arguments(command_argument_parse[0],command_argument_parse[1]);
            //cout << endl;
        }
    }
    exit(0);
};



int main(int argc, const char * argv[]) {
    string username; // Holds the username in a string. Will use for terminal
    string parse; // Parses the command the user enters.
    string exit = "exit";
    // Will display prompt to the user and ask them for a username then it takes them into the terminal program
    cout << "This is a beta terminal program. Type 'help' to get a list of commands." << endl;
    cout << "Enter your username: ";
    getline(cin, username);
    terminal(username);
    return 0;
};
