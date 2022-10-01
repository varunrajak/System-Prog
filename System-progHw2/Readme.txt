HW2

Used header files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <conio.h>

Used different functions like getopt,optarg,etc

Used switchcases to trigger among the arguments

Used recursive function to travel through all the directories with respect to the path that is given 

Used different string method such as strcmp strcpy for different logical operations

Made a makefile to run code

Tested with differnt type of arguments 


For Compiling and executing the file use the following command

gcc -o Hw2 Hw2.c

after its compiled successfully 

./Hw2 <the arguments>


for doing the same with makefile

make 

gcc -o Hw2.o -c Hw2.c

./Hw2 <arguments>