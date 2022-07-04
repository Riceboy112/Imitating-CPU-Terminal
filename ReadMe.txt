Name: Nicholas Kong 
ID: 105737913
Class: CSCI 3453
Lab 2
Due Date: March 8, 2020

Structure of program:
---------------------
File organization: main.cpp
Functional organization: The c++ program mimics a terminal or shell which is functional.

Status: It works completely. All functions of a terminal/shell is functional.

Hardware & Platform I used: 2.7 GHz Intel Core i5 processor with 8GB 1867 MHz DDR3 Memory.
Version 10.12.5


*******************************************************
*  Source files
*******************************************************

Name: main.cpp
	Main holds all of my functions I used to mimic a terminal/shell OS. It is functional with all commands working as long as the command has 0 or 1 argument only. 

*******************************************************
*  Circumstances of programs
*******************************************************

   The program runs successfully.
   
   The program was developed and tested on gnu g++ 4.4.2.  It was 
   compiled, run, and tested on gcc ouray.cudenver.edu.


*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the homework.  The homework file is compressed.  
   To uncompress it use the following commands 
       % unzip [KongLab2.zip]

   Now you should see a directory named homework with the files:
        main.cpp
        makefile
        KongReadMe.txt

2. Build the program.

    Change to the directory that contains the file by:
    % cd [KongLab2] 

    Compile the program by:
    % make

3. Run the program by:
   % ./[main]

4. Delete the obj files, executables, and core dump by
   %./make clean

5. Run the program again 
   %./main

*******************************************************
*  How to build and run the program Option 2
*******************************************************

g++ main.cpp -o main.o
