/* 
Name: Varun Rajak 
BlazerId: vrajak
Project #: 2
*/ 

// reference
// https://lloydrochester.com/post/c/list-directory/
// https://pubs.opengroup.org/onlinepubs/000095399/functions/stat.html
// https://www.cs.cmu.edu/~guna/15-123S11/Lectures/Lecture24.pdf
// https://profile.iiita.ac.in/bibhas.ghoshal/lab_files/System%20calls%20for%20files%20and%20directories%20in%20Linux.html



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

typedef int HwFunc(char *file);
// int pfunc(char *file, HwFunc *func);



//Taken Reference from lab5 readdir

char *filetype(unsigned char type)
{

    char *str;
    switch (type)
    {
        case DT_BLK:
        str = "block device";
        break;
        case DT_CHR:
        str = "character device";
        break;
        case DT_DIR:
        str = "directory";
        break;
        case DT_FIFO:
        str = " pipe (FIFO)";
        break;
        case DT_LNK:
        str = "symbolic link";
        break;
        case DT_REG:
        str = "regular file";
        break;
        case DT_SOCK:
        str = "UNIX domain socket";
        break;
        case DT_UNKNOWN:
        str = "unknown file type";
        break;
        default:
        str = "UNKNOWN";
    }
    return str;
}


int pfunc(char *file, HwFunc *func){
    return func(file);
}

int fsize(char *file)
{
    struct stat buffsize;
    if (stat(file, &buffsize) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    return buffsize.st_size;
}

int display(char * file)
{
    printf("%s\n", file);
    return 0;
}

void args(char *arg, struct dirent *dirent, char *path, int disp){

    if (strcmp(arg, "d") == 0 && strcmp (filetype(dirent->d_type), "directory") == 0)
    {
        if (disp == 1){
            printf("%s\t %d\n", dirent->d_name, pfunc(path, fsize));
        }
        else{
            printf("%s\t\n", dirent->d_name);
        }
    }

    if (strcmp(arg, "f") == 0 && strcmp(filetype(dirent->d_type), "directory") != 0)
    {
        if (disp == 1){
            printf("%s %d\n", dirent->d_name, pfunc(path, fsize));
        }
        else
        {
            printf("%s\n", dirent->d_name);
        }
    }
}

void printFile(char *path, struct dirent *dirent, int count, int Sflag, int sflag, int fflag, int tflag, int sarg, char *farg, char *arg)
{
    int value = pfunc(path, fsize);

    if (sflag == 1 && fflag == 1 && Sflag == 1 && tflag == 1) 
    {
        if (sarg <= value)
        {
            if (strstr(dirent->d_name, farg))
            {
                args(arg, dirent, path, 1);
            }
        }
    }
    else if (sflag == 1 && fflag == 1 && Sflag == 1)    
    {
        if (sarg <= value)
        {
            if (strstr(dirent->d_name, farg))
            {
                printf("%s\t %d\n", dirent->d_name, pfunc(path, fsize));
            }
        }
    }
    // For arg t, S,f
    else if (tflag == 1 && fflag == 1 && Sflag == 1)  
    {
        if (strstr(dirent->d_name, farg))
        {
            args(arg, dirent, path, 1);
        }
    }

 //for arg s,t,f 
    else if (sflag == 1 && tflag == 1 && tflag == 1)
    {
        if (sarg <= value)
        {
            if (strstr(dirent->d_name, farg))
            {
                args(arg, dirent, path, 0);
            }
        }
    }

    // for arg s,S,t
    else if (sflag == 1 && fflag == 1 && Sflag == 1)  
    {
        if (sarg <= value)
        {
            
            printf("%s\t [%d]\n", dirent->d_name, pfunc(path, fsize));
        }
    }
     // for arg s,f
    else if (sflag == 1 && fflag == 1) 
    {
        if (sarg <= value)
        {
            if (strstr(dirent->d_name, farg))
            {
                pfunc(dirent->d_name,display);
            }
        }
    }

    //for arg s,t
    else if (sflag == 1 && tflag == 1) {
        if (sarg <= value)
        {
            args(arg, dirent, path, 0);
        }
    }

    // s,S arg
    else if (sflag == 1 && Sflag == 1) {
        if (sarg <= value)
        {
            printf("%s\t [%d]\n", dirent->d_name, pfunc(path, fsize));
        }
    }

    // S,f arguments
    else if (fflag == 1 && Sflag == 1) 
    {
        if (strstr(dirent->d_name, farg))
        {
            printf("%s\t [%d]\n", dirent->d_name, pfunc(path, fsize));
        }
    }

    // S,t arguments
    else if (tflag == 1 && Sflag == 1) 
    {
       args(arg, dirent, path, 1);
    }

    // S,f arguments
    else if (fflag == 1 && tflag == 1) 
    {
        if (strstr(dirent->d_name, farg))
        {
            args(arg, dirent, path, 0);
        }
    }
    else if (Sflag == 1)
    {
        if (count > 1)
        {
            printf("%*s", count * 2, "");
        }
        printf("%s\t [%d]\n", dirent->d_name, pfunc(path, fsize));
    }
    else if (sflag == 1)
    {
        if (sarg <= value)
        {
            pfunc(dirent->d_name, display);
        }
    }
    else if (fflag == 1)
    {
        if (strstr(dirent->d_name, farg))
        {
            pfunc(dirent->d_name,display);

        }
    }
    else if (tflag == 1)
    {
        args(arg, dirent, path, 0);
    }
    else
    {
        if (count > 1)
        {
            printf("%*s",count*3, "");
        }
        pfunc(dirent->d_name, display);
    }
}

//reference from lab4 and lab5

void rcall(char *Dir, int count, int Sflag, int sflag, int fflag, int tflag, int sarg, char *farg, char *arg)
{
    struct dirent *dirent;
    DIR *mainDirFoldr;
    char *path = malloc(100 * sizeof(char));
    mainDirFoldr = opendir(Dir);

    //Check if its open
    if (mainDirFoldr == NULL)
    {
        return;
    }
    count++;

//Directory operations 
    while ((dirent = readdir(mainDirFoldr)) != NULL) {
        if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) 
        {
            strcpy(path, Dir);
            strcat(path, "/");
            strcat(path, dirent->d_name);
            printFile(path, dirent, count, Sflag, sflag, fflag, tflag, sarg, farg, arg);

            // Checking if it's a directory
            if (strcmp(filetype(dirent->d_type), "directory") == 0) {
                rcall(path, count, Sflag, sflag, fflag, tflag, sarg, farg, arg); // Calling the recursive function 
            }
        }
    }
    closedir(mainDirFoldr);
}


void main(int argc, char **argv)
{
    int i,Sflag = 0, sflag = 0, fflag = 0, tflag = 0, sarg = 0, count=0, argval; //initializing
    char *farg, *arg, *isPath;
    struct stat directst;

    for ( i = 1; i < argc; i++){
        if (stat(argv[i], &directst) != 0){
            continue;
        }

        if (S_ISDIR(directst.st_mode))
        {
            isPath = argv[i];
        }
    }

//setting the flags depending on the arguments
// getopt() for going through each of the argumnet entered 
// reference https://www.gnu.org/software/libc/manual/html_node/Using-Getopt.html
    
    while ((argval = getopt(argc, argv, "s:Sf:t:")) != -1){
        switch (argval){
        case 'S':
            Sflag = 1;
            break;
        case 's':
            sflag = 1;
            sarg = atoi(optarg);
            break;
        case 'f':
            fflag = 1;
            farg = optarg;
            break;
        case 't':
            tflag = 1;
            arg = optarg;
            break;
        case '?':
            break;
        }
    }

    //If path is null or not null 
    if (isPath != NULL)
    {
        rcall(isPath, count, Sflag, sflag, fflag, tflag, sarg, farg, arg);
    }
    else
    {
        rcall(".", count, Sflag, sflag, fflag, tflag, sarg, farg, arg);
    }
}